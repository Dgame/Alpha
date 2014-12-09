#include "Parser.hpp"
#include "Expr.hpp"
#include "Scope.hpp"
#include "VarDecl.hpp"

#include <string>
#include <locale>
#include <vector>
#include <fstream>
#include <sstream>

void Parser::error(const char* s) {
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%')
                ++s;
            else {
                std::cerr << "invalid format string: missing arguments" << std::endl;
                break;
            }
        }
        std::cerr << *s++;
    }

    _errors = true;
}

template <typename T, typename... Args>
void Parser::error(const char* s, const T& value, Args&& ...args) {
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%')
                ++s;
            else {
                std::cerr << value;
                s += 2;
                return error(s, args...); // call even when *s == 0 to detect extra arguments
            }
        }
        std::cerr << *s++;
    }    
}

void Parser::skip_spaces() {
    while (!_loc.eof() && std::isspace(_loc.current())) {
        if (_loc.current() == '\n')
            _loc.lineNr++;
        ++_loc.pos;
    }
}

bool Parser::accept(const std::string& tok) {
    skip_spaces();

    const Loc old_loc = _loc;
    for (u16_t i = 0; i < tok.length(); i++) {
        if (tok[i] != _loc.current()) {
            _loc = old_loc;
            return false;
        }

        if (_loc.eof()) {
            _loc = old_loc;
            return false;
        }

        _loc.pos++;
    }

    return true;
}

bool Parser::expect(const std::string& tok) {
    skip_spaces();

    std::string ident;

    const Loc old_loc = _loc;
    for (u16_t i = 0; i < tok.length(); i++) {
        ident += _loc.current();

        if (tok[i] != _loc.current()) {
            error("Did expected '%s' not '%s'", tok, ident);
            _loc = old_loc;
            return false;
        }

        if (_loc.eof()) {
            if (i < (tok.length() - 1))
                error("Unexpected EOF: Could not detect '%s', but found '%s'", tok, ident);
            _loc = old_loc;
            return false;
        }

        _loc.pos++;
    }

    return true;
}

bool Parser::read_identifier(std::string& ident) {
    skip_spaces();

    if (!_loc.eof() && (std::isalpha(_loc.current()) || _loc.current() == '_')) {
        while (!_loc.eof() && std::isalnum(_loc.current())) {
            ident += _loc.current();
            ++_loc.pos;
        }

        return true;
    }

    return false;
}

bool Parser::read_number(i32_t& num) {
    skip_spaces();

    if (!_loc.eof() && std::isdigit(_loc.current())) {
        num = 0;
        do {
            num *= 10;
            num += _loc.current() - '0';

            _loc.pos++;
        } while (!_loc.eof() && std::isdigit(_loc.current()));

        return true;
    }

    return false;
}

Env* Parser::parse(const std::string& filename) {
    std::ifstream in_file(filename);
    std::stringstream buf;
    buf << in_file.rdbuf();
    std::string source_code = buf.str();
    
    _loc.pos = &source_code.front();
    _loc.end = &source_code.back();
    
    while (!_loc.eof() && !_errors) {
       parseFunc();
    }

    if (!_errors)
        return &_env;

    return nullptr;
}

void Parser::parseFunc() {
    std::string ident;
    if (read_identifier(ident)) {
        expect("(");
        // TODO: parameters
        expect(")");

        parseScope();

        _env.addFunc(new Func(ident, _cur_scope));
        _cur_scope = nullptr;
    } else {
        error("No function found");
    }
}

void Parser::parseScope() {
    expect("{");

    _cur_scope = new Scope(_cur_scope);
    
    while (!_errors && !_loc.eof()) {
        std::string ident;

        if (accept("print")) {
            parsePrintDecl();
        } else if (read_identifier(ident)) {
            const bool isVar = parseVarDecl(ident);
            if (!isVar)
                error("'%s' is not a valid variable", ident);
        } else {
            error("Cannot parse: '%c'", _loc.current());
        }
    }

    expect("}");
}

void Parser::parsePrintDecl() {
    PrintDecl* pi = new PrintDecl();
    while (!_loc.eof()) {
        const Expr* exp = parseExpr();
        if (exp)
            pi->addExpr(exp);
        else {
            const StringExpr* sexp = parseStringExpr();
            if (sexp)
                pi->addExpr(sexp);
            else {
                error("Nothing to print");
                return;
            }
        }

        if (!accept(","))
            break;
    }

    _cur_scope->addDecl(pi);
}

bool Parser::parseVarDecl(const std::string& ident) {
    if (accept("=")) {
        Expr* exp = parseExpr();
        if (!exp) {
            error("Variable '%s' need assignment", ident);
            return false;
        }

        _cur_scope->addVarDecl(ident, new VarDecl(exp));

        return true;
    } else if (accept("->")) {
        error("Currently, no pointers are implemented");
    } else if (accept("<-")) {
        error("Currently, no pointers are implemented");
    } else {
        error("Unexpected identifier: %s", ident);
    }

    return false;
}

StringExpr* Parser::parseStringExpr() {
    if (accept("\"")) {
        std::string str;
        while (!_loc.eof() && _loc.current() != '\"') {
            str += *_loc.pos;
            _loc.pos++;
        }

        expect("\"");

        const std::string label = _env.labels.addStr(str, "STR");

        return new StringExpr(label);
    }

    return nullptr;
}

Expr* Parser::parseExpr() {
    Expr* lhs = parseTerm();
    if (!lhs)
        return nullptr;

    while (!_loc.eof()) {
        if (accept("+")) {
            Expr* rhs = parseTerm();
            if (!rhs) {
                error("Expected factor after +");

                delete lhs;

                return nullptr;
            }
            lhs = new AddExpr(lhs, rhs);
        } else if (accept("-")) {
            Expr* rhs = parseTerm();
            if (!rhs) {
                error("Expected factor after -");

                delete lhs;

                return nullptr;
            }
            lhs = new SubExpr(rhs, lhs);
        } else
            break;
    }

    return lhs;
}

Expr* Parser::parseTerm() {
    Expr* lhs = parseFactor();
    if (!lhs)
        return nullptr;

    while (!_loc.eof()) {
        if (accept("*")) {
            Expr* rhs = parseFactor();
            if (!rhs) {
                error("Expected factor after *");

                delete lhs;

                return nullptr;
            }
            lhs = new MulExpr(lhs, rhs);
        } else if (accept("/")) {
            Expr* rhs = parseFactor();
            if (!rhs) {
                error("Expected factor after /");

                delete lhs;

                return nullptr;
            }
            lhs = new DivExpr(rhs, lhs);
        } else if (accept("%")) {
            Expr* rhs = parseFactor();
            if (!rhs) {
                error("Expected factor after %");

                delete lhs;

                return nullptr;
            }
            lhs = new ModExpr(rhs, lhs);
        } else 
            break;
    }

    return lhs;
}

Expr* Parser::parseFactor() {
    const bool negate = accept("-");
  
    i32_t num;
    std::string ident;

    Expr* expr = nullptr;

    if (read_number(num))
        expr = new NumExpr(num);
    else if (accept("(")) {
        expr = parseExpr();
        expect(")");
    } else if (read_identifier(ident)) {
        const VarDecl* var = seekingDown(ident, _cur_scope);
        if (var)
            expr = new VarExpr(var);
        else
            error("No such variable: '%s'", ident);
    }

    if (negate) {
        if (!expr)
            error("Nothing that can be negated");
        else
            return new NegExpr(expr);
    }

    return expr;
}