#include "Parser.hpp"

#include <locale>

#include "Operation.hpp"
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

        Scope* my_scope = nullptr;
        parseScope(&my_scope);

        functions.emplace_back(new Function(name, my_scope));

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

    *scope = new Scope();

    while (!eof() && !_error) {
        const u32_t stmt_count = (*scope)->statements.size();

        parseStmt(*scope);
        parseVar(*scope);

        // No new elements?
        if (stmt_count == (*scope)->statements.size())
            break;
    }

    expect("}");
}

void Parser::parseStmt(Scope* scope) {
    parsePrint(scope);
    parseIf(scope);
}

void Parser::parsePrint(Scope* scope) {
    if (accept("print")) {
        MultiplePrintStmt* multi_print = new MultiplePrintStmt();
        while (!_error) {
            const u32_t print_size = multi_print->prints.size();
            
            if (const Expr* exp = parseExpr(scope))
                multi_print->append(new PrintStmt(exp));
            else {
                std::string ident;
                if (readString(&ident)) {
                    const std::string label = make_unique_label();
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
        scope->addStmt(multi_print);
    }
}

void Parser::parseArray(Scope*) {

}

void Parser::parseCompExpr() {
    // if (accept("true")) {
    //     env.out<<"movl $1, %eax"<<endl; 
    //     return true; 
    // }else if(ignore(pos, end, "false")){ 
    //     env.out<<"movl $0, %eax"<<endl; 
    //     return true; 
    // }else if(parse_numeric_expression(env, pos, end)){ 
    //     BacktrackGuard guard(pos); 
    //     string condition_code; 
    //     if(ignore(pos, end, "=")) 
    //         condition_code = "e"; 
    //     else if(ignore(pos, end, "!=")) 
    //         condition_code = "ne"; 
    //     else if(ignore(pos, end, "<=")) 
    //         condition_code = "be"; 
    //     else if(ignore(pos, end, ">=")) 
    //         condition_code = "ae"; 
    //     else if(ignore(pos, end, "<")) 
    //         condition_code = "b"; 
    //     else if(ignore(pos, end, ">")) 
    //         condition_code = "a"; 
    //     else 
    //         cerr<<"Unknown compare operator"<<endl; 
    //     env.out<<"pushl %eax"<<endl; 
    //     if(parse_numeric_expression(env, pos, end)){ 
    //         env.out 
    //             <<"cmpl %eax, (%esp)"<<endl 
    //             <<"movl $0, %eax"<<endl 
    //             <<"set"<<condition_code<<" %al"<<endl 
    //             <<"addl $4, %esp"<<endl; 
    //         guard.no_backtrack(); 
    //         return true; 
    //     } 
    // } 
    // return false; 
} 
  
void Parser::parseBoolExpr() { 
    // BacktrackGuard guard(pos); 
    // bool not_operation = false; 
    // if(ignore(pos, end, "!")) 
    //     not_operation = true; 
    // if(parse_compare_expression(env, pos, end)){ 
    //     for(;;){ 
    //         string operation; 
    //         if(ignore(pos, end, "&")) 
    //             operation = "and"; 
    //         else if(ignore(pos, end, "|")) 
    //             operation = "or"; 
    //         else if(ignore(pos, end, "^")) 
    //             operation = "xor"; 
    //         else{ 
    //             if(not_operation) 
    //                 env.out<<"notl %eax"<<endl; 
    //             guard.no_backtrack(); 
    //             return true; 
    //         } 
    //         env.out<<"pushl %eax"<<endl; 
    //         if(!parse_compare_expression(env, pos, end)) 
    //             return false; 
    //         env.out 
    //             <<operation<<" %eax, (%esp)"<<endl 
    //             <<"addl $4, %esp"<<endl; 
    //     } 
    // } 
    // return false; 
}

void Parser::parseIf(Scope*) {

}

void Parser::parseElse(Scope*) {

}

void Parser::parseLoop(Scope*) {

}

const Var* Parser::readVar(Scope* scope) {
    std::string ident;
    if (readIdentifier(&ident))
        return scope->getVar(ident);
    return nullptr;
}

void Parser::parseVar(Scope* scope) {
    std::string name;
    if (readIdentifier(&name)) {
        // since the 'accept's below will override '_old_pos', store it...
        char* my_old_pos = _old_pos;

        if (accept("=")) {
            // By Value
            parseVarVal(name, scope);
        } else if (accept("->")) {
            // Reference
            parseVarEnRef(name, scope);
        } else if (accept("<-")) {
            // Dereference
            parseVarDeRef(name, scope);
        } else {
            // ...and reset it correctly.
            _pos = my_old_pos;
        }
    }
}

void Parser::parseVarVal(std::string& name, Scope* scope) {
    // By Value
    const Expr* exp = parseExpr(scope);
    if (!exp) {
        error("No assignment found for variable " + name);

        return;
    }
    scope->makeVar(name, exp);
}

void Parser::parseVarEnRef(std::string& name, Scope* scope) {
    // Reference
    const Var* var = readVar(scope);
    if (var)
        scope->makeVar(name, var, RefType::EnRef);
    else {
        error("Need valid variable for reference.");
        pop();
    }
}

void Parser::parseVarDeRef(std::string& name, Scope* scope) {
    // Dereference
    const Var* var = readVar(scope);
    if (var)
        scope->makeVar(name, var, RefType::DeRef);
    else {
        error("Need valid variable for dereference.");
        pop();
    }
}

Expr* Parser::parseExpr(Scope* scope) {
    Expr* lhs = parseTerm(scope);
    if (lhs) {
        while (true) {
            if (accept("+")) {
                Expr* rhs = parseTerm(scope);
                if (!rhs) {
                    error("Expected factor after +");

                    delete lhs;
                    delete rhs;

                    return nullptr;
                }

                lhs = new AddOp(lhs, rhs);
            } else if (accept("-")) {
                Expr* rhs = parseTerm(scope);
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

Expr* Parser::parseTerm(Scope* scope) {
    Expr* lhs = parseFactor(scope);
    if (lhs) {
        while (true) {
            if (accept("*")) {
                Expr* rhs = parseFactor(scope);
                if (!rhs) {
                    error("Expected factor after *");

                    delete lhs;
                    delete rhs;

                    return nullptr;
                }

                lhs = new MulOp(lhs, rhs);
            } else if (accept("/")) {
                Expr* rhs = parseFactor(scope);
                if (!rhs) {
                    error("Expected factor after /");

                    delete lhs;
                    delete rhs;

                    return nullptr;
                }

                lhs = new DivOp(rhs, lhs);
            } else 
                break;
        }
    }

    return lhs;
}

Expr* Parser::parseFactor(Scope* scope) {
    const bool negate = accept("-");
  
    i32_t num;
    if (readNumber(&num)) {
        if (negate)
            num *= -1;

        return new NumExpr(num);
    } else if (accept("(")) {
        Expr* exp = parseExpr(scope);
        expect(")");

        return exp;
    } else {
        const Var* var = readVar(scope);
        if (var)
            return new VarExpr(var->offset);
        pop();
    }

    return nullptr;
}