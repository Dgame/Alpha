#include "Parser.hpp"

#include <locale>

#include "Operation.hpp"
#include "ExtStmt.hpp"
#include "Var.hpp"
#include "util.hpp"

Parser::Parser(const std::string& file) : _line(1), _filename(file) {
    std::ifstream in(_filename);

    std::copy(
        std::istreambuf_iterator<char>(in.rdbuf()),
        std::istreambuf_iterator<char>(),
        std::inserter(_content, _content.begin()));

    _pos = &*_content.begin();
    _end = &*_content.end() + 1;
}

void Parser::eval(std::ostream& out) const {
    // check for main
    bool found_main = false;
    for (auto& func : this->functions) {
        if (func->name == "main") {
            found_main = true;
            break;
        }
    }

    if (!found_main) {
        std::cerr << "Error: No main function was found." << std::endl;
        return;
    }

    out << ".text" << std::endl;
    
    for (auto& func : this->functions) {
        func->eval(out);
    }

    this->data_section.writeDataSections(out);
}

void Parser::skipSpaces() {
    while (!eof() && std::isspace(*_pos)) {
        if (*_pos == '\n')
            _line++;
        ++_pos;

        skipComment();
    }
}

void Parser::skipComment() {
    if (!eof() && *_pos == '#') {
        do {
            _pos++;
        } while (!eof() && *_pos != '\n');
    }
}

bool Parser::readNumber(i32_t* num) {
    skipSpaces();
    push();

    if (!eof() && std::isdigit(*_pos)) {
        *num = 0;
        do {
            *num *= 10;
            *num += *_pos - '0';

            ++_pos;
        } while (!eof() && std::isdigit(*_pos));

        return true;
    }

    return false;
}

bool Parser::readIdentifier(std::string* ident) {
    skipSpaces();
    push();

    if (!eof() && (std::isalpha(*_pos) || *_pos == '_')) {
        *ident = "";
        *ident += *_pos;
        _pos++;

        while (!eof() && (std::isalnum(*_pos) || *_pos == '_')) {
            *ident += *_pos;
            _pos++;
        }

        return true;
    }

    return false;
}
  
bool Parser::readString(std::string* ident) { 
    skipSpaces();

    if (!eof() && *_pos == '"') {
        ++_pos; 
        *ident = "";

        do {
            if (*_pos == '\\') {
                ++_pos;
                if (eof()) {
                    error("EOF in string literal");

                    return false;
                }

                *ident += unescape_char(*_pos);
            } else
                *ident += *_pos;

            ++_pos;
        } while (!eof() && *_pos != '\"');

        expect("\"");

        return true;
    }
    
    return false;
}

bool Parser::accept(const std::string& tok) {
    skipSpaces();
    push();

    for (u32_t i = 0; i < tok.size(); i++) {
        if (tok[i] != *_pos) {
            pop();
            return false;
        }

        _pos++;
    }

    return true;
}

bool Parser::expect(const std::string& tok) {
    skipSpaces();
    push();

    std::string ident;
    for (u32_t i = 0; i < tok.size(); i++) {
        ident += *_pos;

        if (tok[i] != *_pos) {
            pop();
            error("Did expected '" + tok + "', not '" + ident + "'");

            return false;
        }

        _pos++;
    }

    return true;
}

void Parser::parse() {
    while (!eof() && !_error) {
        const char* const cur_pos = _pos;
        if (!parseFunc())
            error("Did expect a function");
        if (cur_pos == _pos)
            error("Could not parse anything");
    }
}

bool Parser::parseFunc() {
    std::string name;
    if (readIdentifier(&name)) {
        parseParam();

        Scope* scope = nullptr;
        parseScope(&scope);

        functions.emplace_back(new Function(name, scope));
        _cur_scope = nullptr;

        return true;
    }

    return false;
}

void Parser::parseParam() {
    expect("(");

    // TODO: parse parameter

    expect(")");
}

void Parser::parseScope(Scope** scope) {
    expect("{");

    *scope = new Scope(_cur_scope);
    _cur_scope = *scope;

    while (!eof() && !_error) {
        const u32_t stmt_count = (*scope)->statements.size();

        parseStmt();
        parseVar();

        // No new elements?
        if (stmt_count == (*scope)->statements.size())
            break;
    }

    expect("}");
}

void Parser::parseStmt() {
    parsePrintStmt();
    parseIfStmt();
    parseLoopStmt();
}

void Parser::parsePrintStmt() {
    if (accept("print")) {
        MultiplePrintStmt* multi_print = new MultiplePrintStmt();
        while (!eof() && !_error) {
            const u32_t print_size = multi_print->prints.size();
            
            if (const Expr* exp = parseExpr())
                multi_print->append(new PrintStmt(exp));
            else {
                std::string ident;
                if (readString(&ident)) {
                    const std::string label = make_unique_label("S");
                    this->data_section.addDataSection(label, ident);

                    multi_print->append(new PrintStmt(label));
                }
            }

            if (multi_print->prints.size() == print_size)
                error("Nothing to print");

            if (!accept(","))
                break;
        }
        // adjust, so that the first (N - 1) prints does not have a new line
        multi_print->adjust();
        _cur_scope->addStmt(multi_print);
    }
}

void Parser::parseIfStmt() {
    if (accept("if")) {
        accept("("); // not expect

        const std::string if_label = make_unique_label("I");
        const std::string else_label = make_unique_label("E");

        Compare* cmp = parseCondExpr(if_label, else_label);
        if (!cmp) {
            error("No if expression was found");
            return;
        }

        accept(")"); // not expect

        Scope* scope = nullptr;
        parseScope(&scope);

        _cur_scope = scope->predecessor;
        
        IfStmt* if_stmt = new IfStmt(if_label, else_label, cmp, scope);
        ElseStmt* else_stmt = parseElseStmt(else_label);
        if (else_stmt)
            if_stmt->else_stmt.reset(else_stmt);

        _cur_scope->addStmt(if_stmt);
    }
}

ElseStmt* Parser::parseElseStmt(const std::string& else_label) {
    if (accept("else")) {
        Compare* cmp = nullptr;
        const std::string end_label = make_unique_label("END");

        if (accept("if")) {
            accept("("); // not expect

            cmp = parseCondExpr(else_label, end_label);
            if (!cmp) {
                error("No if expression was found");
                return nullptr;
            }

            accept(")"); // not expect
        }

        Scope* scope = nullptr;
        parseScope(&scope);

        _cur_scope = scope->predecessor;

        return new ElseStmt(end_label, cmp, scope);
    }

    return nullptr;
}

void Parser::parseLoopStmt() {
    if (accept("while")) {
        accept("(");

        const std::string top_label = make_unique_label("WL");
        const std::string start_label = make_unique_label("LB");
        const std::string end_label = make_unique_label("LE");

        Compare* cmp = parseCondExpr(start_label, end_label);
        if (!cmp) {
            error("No while expression was found");
            return;
        }

        accept(")");

        Scope* scope = nullptr;
        parseScope(&scope);

        _cur_scope = scope->predecessor;
        _cur_scope->addStmt(new WhileLoopStmt(top_label, start_label, end_label, cmp, scope));
    }
}

Compare* Parser::parseCondExpr(const std::string& if_label, const std::string& else_label) {
    Compare* cmp = nullptr;
    while (!eof() && !_error) {
        Compare* left_cmp = parseCompExpr();
        if (!left_cmp)
            break;

        if (accept("&&") || accept("||")) {
            error("Use 'and' instead of '&&' and 'or' instead of '||'");
            return nullptr;
        }

        CondType cond_type = COND_NONE;
        if (accept("and"))
            cond_type = COND_AND;
        else if (accept("or"))
            cond_type = COND_OR;

        if (cond_type != COND_NONE) {
            Compare* right_cmp = parseCompExpr();
            if (!right_cmp) {
                error("'and', 'or' and 'xor' expect two expressions");
                return nullptr;
            }

            left_cmp->cond_options = right_cmp->cond_options = CondOptions(if_label, else_label, cond_type);

            if (cmp)
                cmp = new Cond(cmp, new Cond(left_cmp, right_cmp));
            else
                cmp = new Cond(left_cmp, right_cmp);

            continue;
        }

        // No CondType? Assume COND_AND
        left_cmp->cond_options = CondOptions(if_label, else_label, COND_AND);
        if (!cmp)
            cmp = left_cmp;
        else {
            error("Need either 'and' or 'or' to concat conditions");
            return nullptr;
        }

        break;
    }

    return cmp;
}

Compare* Parser::parseCompExpr() {
    const Expr* exp = parseExpr();
    if (!exp)
        return nullptr;

    if (accept(">=")) {
        const Expr* right_exp = parseExpr();
        if (!right_exp) {
            error("Expected right hand side expression for compare.");
            return nullptr;
        }

        return new GreaterEqualOp(exp, right_exp);
    }

    if (accept("<=")) {
        const Expr* right_exp = parseExpr();
        if (!right_exp) {
            error("Expected right hand side expression for compare.");
            return nullptr;
        }

        return new LowerEqualOp(exp, right_exp);
    }

    if (accept("==")) {
        const Expr* right_exp = parseExpr();
        if (!right_exp) {
            error("Expected right hand side expression for compare.");
            return nullptr;
        }

        return new EqualOp(exp, right_exp);
    }

    if (accept("!=")) {
        const Expr* right_exp = parseExpr();
        if (!right_exp) {
            error("Expected right hand side expression for compare.");
            return nullptr;
        }

        return new NotEqualOp(exp, right_exp);
    }

    if (accept(">")) {
        const Expr* right_exp = parseExpr();
        if (!right_exp) {
            error("Expected right hand side expression for compare.");
            return nullptr;
        }

        return new GreaterOp(exp, right_exp);
    }

    if (accept("<")) {
        const Expr* right_exp = parseExpr();
        if (!right_exp) {
            error("Expected right hand side expression for compare.");
            return nullptr;
        }

        return new LowerOp(exp, right_exp);
    }
    
    return new NotEqualOp(exp, new NumExpr(0));
}

void Parser::parseArray() {

}

const Var* Parser::readVar() {
    std::string ident;
    if (readIdentifier(&ident))
        return _cur_scope->getVar(ident);

    return nullptr;
}

void Parser::parseVar() {
    std::string ident;
    if (readIdentifier(&ident)) {
        // since the 'accept's below will override '_old_pos', store it...
        char* my_old_pos = _old_pos;
        if (accept("=")) {
            // By Value
            parseVarVal(ident);
        } else if (accept("->")) {
            // Reference
            parseVarEnRef(ident);
        } else if (accept("<-")) {
            // Dereference
            parseVarDeRef(ident);
        } else if (accept("++")) {
            parseVarInc(ident);
        } else if (accept("--")) {
            parseVarDec(ident);
        } else {
            // ...and reset it correctly.
            _pos = my_old_pos;
        }
    }
}

void Parser::parseVarVal(std::string& ident) {
    // By Value
    const Expr* exp = parseExpr();
    if (!exp) {
        error("No assignment found for variable " + ident);
        return;
    }
    _cur_scope->addVar(ident, exp);
}

void Parser::parseVarEnRef(std::string& ident) {
    // Reference
    const Var* var = readVar();
    if (var)
        _cur_scope->addVar(ident, var, RefType::EnRef);
    else {
        error("Need valid variable for reference");
        pop();
    }
}

void Parser::parseVarDeRef(std::string& ident) {
    // Dereference
    const Var* var = readVar();
    if (var)
        _cur_scope->addVar(ident, var, RefType::DeRef);
    else {
        error("Need valid variable for dereference");
        pop();
    }
}

void Parser::parseVarInc(std::string& name) {
    const Var* var = _cur_scope->getVar(name);
    if (var)
        _cur_scope->addStmt(new IncStmt(var->offset));
    else {
        error("Need existing variable for increase");
        pop();
    }
}

void Parser::parseVarDec(std::string& ident) {
    const Var* var = _cur_scope->getVar(ident);
    if (var)
        _cur_scope->addStmt(new DecStmt(var->offset));
    else {
        error("Need existing variable for decrease");
        pop();
    }
}

Expr* Parser::parseExpr() {
    Expr* lhs = parseTerm();
    if (lhs) {
        while (true) {
            if (accept("+")) {
                Expr* rhs = parseTerm();
                if (!rhs) {
                    error("Expected factor after +");

                    delete lhs;
                    delete rhs;

                    return nullptr;
                }

                lhs = new AddOp(lhs, rhs);
            } else if (accept("-")) {
                Expr* rhs = parseTerm();
                if (!rhs) {
                    error("Expected factor after -");

                    delete lhs;
                    delete rhs;

                    return nullptr;
                }

                lhs = new SubOp(rhs, lhs);
            } else
                break;
        }
    }

    return lhs;
}

Expr* Parser::parseTerm() {
    Expr* lhs = parseFactor();
    if (lhs) {
        while (true) {
            if (accept("*")) {
                Expr* rhs = parseFactor();
                if (!rhs) {
                    error("Expected factor after *");

                    delete lhs;
                    delete rhs;

                    return nullptr;
                }

                lhs = new MulOp(lhs, rhs);
            } else if (accept("/")) {
                Expr* rhs = parseFactor();
                if (!rhs) {
                    error("Expected factor after /");

                    delete lhs;
                    delete rhs;

                    return nullptr;
                }

                lhs = new DivOp(rhs, lhs);
            } else if (accept("%")) {
                Expr* rhs = parseFactor();
                if (!rhs) {
                    error("Expected factor after %");

                    delete lhs;
                    delete rhs;

                    return nullptr;
                }

                lhs = new ModOp(rhs, lhs);
            } else 
                break;
        }
    }

    return lhs;
}

Expr* Parser::parseFactor() {
    const bool negate = accept("-");
  
    i32_t num;
    if (readNumber(&num)) {
        if (negate)
            num *= -1;

        return new NumExpr(num);
    } else if (accept("(")) {
        Expr* exp = parseExpr();
        expect(")");

        return exp;
    } else {
        const Var* var = readVar();
        if (var)
            return new VarExpr(var->offset);
        pop();
    }

    return nullptr;
}