#include "Parser.hpp"
#include "Expr.hpp"
#include "Scope.hpp"
#include "Var.hpp"

#include <locale>
#include <vector>
#include <fstream>
#include <iostream>

void Parser::error(const std::string& msg) {
    _errors = true;
    std::cerr << "Error: " << msg << " in line " << _loc.lineNr << std::endl;
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

    const Loc my_loc = _loc;
    for (char c : tok) {
        if (_loc.eof() || c != _loc.current()) {
            _loc = my_loc;
            return false;
        }
        _loc.pos++;
    }

    return true;
}

bool Parser::expect(const std::string& tok) {
    skip_spaces();

    const Loc my_loc = _loc;
    for (char c : tok) {
        if (c != _loc.current()) {
            _loc = my_loc;
            error("Did expected '" + tok + "', not: " + _loc.current());
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

    std::vector<char> source_code;
    std::copy(
        std::istreambuf_iterator<char>(in_file.rdbuf()),
        std::istreambuf_iterator<char>(),
        std::back_inserter(source_code));

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
            parsePrint();
        } else if (read_identifier(ident)) {
            if (parseVar(ident)) {
                // pass
            }
        } else {
            error("Cannot parse: " + _loc.current());
        }
    }

    expect("}");
}

void Parser::parsePrint() {
    PrintInstr* pi = new PrintInstr();
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

    _cur_scope->addInstr(pi);
}

bool Parser::parseVar(const std::string& ident) {
    if (accept("=")) {
        Expr* exp = parseExpr();
        if (!exp) {
            error("Variable '" + ident + "'' need assignment");
            return false;
        }

        _cur_scope->addVar(ident, new Var(exp));

        return true;
    } else if (accept("->")) {
        error("Currently, no pointers are implemented");
    } else if (accept("<-")) {
        error("Currently, no pointers are implemented");
    } else {
        error("Unexpected identifier: " + ident);
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

        const std::string label = _env.labels.addStr(str, "C");

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
            lhs = new AddOp(lhs, rhs);
        } else if (accept("-")) {
            Expr* rhs = parseTerm();
            if (!rhs) {
                error("Expected factor after -");

                delete lhs;

                return nullptr;
            }
            lhs = new SubOp(rhs, lhs);
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
            lhs = new MulOp(lhs, rhs);
        } else if (accept("/")) {
            Expr* rhs = parseFactor();
            if (!rhs) {
                error("Expected factor after /");

                delete lhs;

                return nullptr;
            }
            lhs = new DivOp(rhs, lhs);
        } else if (accept("%")) {
            Expr* rhs = parseFactor();
            if (!rhs) {
                error("Expected factor after %");

                delete lhs;

                return nullptr;
            }
            lhs = new ModOp(rhs, lhs);
        } else 
            break;
    }

    return lhs;
}

Expr* Parser::parseFactor() {
    const bool negate = accept("-");
  
    i32_t num;
    std::string ident;

    if (read_number(num))
        return new NumExpr(negate ? (num * -1) : num);
    else if (read_identifier(ident)) {
        const Var* var = seekingDown(ident, _cur_scope);
        if (var)
            return new VarExpr(var);
    }

    return nullptr;
}