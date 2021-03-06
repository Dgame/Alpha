#include "Parser.hpp"
#include "Expr.hpp"
#include "Scope.hpp"
#include "VarDecl.hpp"

#include <string>
#include <locale>
#include <fstream>

namespace Tok {
    const std::string Print = "print";
    const std::string L_Arrow = "<-";
    const std::string R_Arrow = "->";
}

namespace Lbl {
    const std::string Str = "STR";
}

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

void Parser::skipSpaces() {
    while (!_loc.eof() && std::isspace(_loc.current())) {
        _loc.next();
    }
}

bool Parser::accept(char c) {
    skipSpaces();

    if (!_loc.eof() && c == _loc.current()) {
        _loc.next();
        return true;
    }

    return false;
}

bool Parser::accept(const std::string& tok) {
    skipSpaces();

    _loc.track();

    for (u16_t i = 0; i < tok.length(); i++) {
        if (tok[i] != _loc.current()) {
            _loc.backtrack();
            return false;
        }

        if (_loc.eof()) {
            if (i < (tok.length() - 1))
                error("Unexpected EOF: Could not detect '%s'", tok);
            _loc.backtrack();
            return false;
        }

        _loc.next();
    }

    return true;
}

bool Parser::expect(char c) {
    if (!accept(c)) {
        error("Did expected '%c'", c);
        return false;
    }

    return true;
}

bool Parser::expect(const std::string& tok) {
    if (!accept(tok)) {
        error("Did expected '%s'", tok);
        return false;
    }

    return true;
}

bool Parser::readIdentifier(std::string& ident) {
    skipSpaces();

    auto isValid = [this](bool first) -> bool {
        if (_loc.eof())
            return false;
        const char c = _loc.current();
        if (c == '_')
            return true;
        if (first)
            return std::isalpha(c);
        return std::isalnum(c);
    };

    if (!isValid(true))
        return false;

    ident.clear();
    do {
        ident += _loc.current();

        _loc.next();
    } while (isValid(false));

    return ident.length() != 0;
}

bool Parser::readNumber(i32_t& num) {
    skipSpaces();

    auto isValid = [this]() -> bool {
        if (_loc.eof())
            return false;
        const char c = _loc.current();
        return std::isdigit(c);
    };

    if (!isValid())
        return false;

    num = 0;
    do {
        num *= 10;
        num += _loc.current() - '0';

        _loc.next();
    } while (isValid());

    return true;
}

Env* Parser::parse(const std::string& filename) {
    std::ifstream stream(filename);
    if (stream.good()) {
        /*
         * Get the size of the file
         */
        stream.seekg(0, std::ios::end);
        const std::streampos len = stream.tellg();
        stream.seekg(0, std::ios::beg);
        /*
         * Read the whole file into the buffer.
         */
        std::vector<char> buffer(len);
        stream.read(&buffer[0], len);

        _loc = Loc(&buffer.front(), &buffer.back());

        // Ignore possible header
        while (!_loc.eof() && !std::isalnum(_loc.current())) {
            _loc.next();
        }

        while (!_loc.eof() && !_errors) {
            parseFunc();
            skipSpaces(); // discard any whitespaces until the next function begins
        }

        if (!_errors)
            return &_env;
    } else
        std::cerr << "Cannot use invalid file handle" << std::endl;

    return nullptr;
}

void Parser::parseFunc() {
    std::string ident;
    if (readIdentifier(ident)) {
        expect('(');
        // TODO: parameters
        expect(')');

        parseScope();

        _env.addFunc(new Func(ident, _cur_scope));
        _cur_scope = nullptr;
    } else
        error("No function found");
}

void Parser::parseScope() {
    expect('{');

    _cur_scope = new Scope(_cur_scope);
    
    while (!_errors && !_loc.eof()) {
        std::string ident;

        if (accept(Tok::Print)) {
            parsePrintDecl();
        } else if (readIdentifier(ident)) {
            const bool isVar = parseVarDecl(ident);
            if (!isVar)
                error("'%s' is not a valid variable", ident);
        } else
            break;
    }

    expect('}');
}

void Parser::parsePrintDecl() {
    std::unique_ptr<PrintDecl> pi(new PrintDecl());

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

        if (!accept(','))
            break;
    }

    _cur_scope->addDecl(pi.release());
}

bool Parser::parseVarDecl(const std::string& ident) {
    if (accept('=')) {
        Expr* exp = parseExpr();
        if (!exp) {
            error("Variable '%s' need assignment", ident);
            return false;
        }

        _cur_scope->addVarDecl(ident, new VarDecl(exp));

        return true;
    } else if (accept(Tok::R_Arrow)) {
        error("Currently, no pointers are implemented");
    } else if (accept(Tok::L_Arrow)) {
        error("Currently, no pointers are implemented");
    } else {
        error("Unexpected identifier: %s", ident);
    }

    return false;
}

StringExpr* Parser::parseStringExpr() {
    if (accept('"')) {
        std::string str;
        while (!_loc.eof() && _loc.current() != '\"') {
            str += _loc.current();
            _loc.next();
        }

        expect('"');

        const std::string label = _env.labels.addStr(str, Lbl::Str);
        return new StringExpr(label);
    }

    return nullptr;
}

Expr* Parser::parseExpr() {
    Expr* lhs = parseTerm();
    if (!lhs)
        return nullptr;

    while (!_loc.eof()) {
        if (accept('+')) {
            Expr* rhs = parseTerm();
            if (!rhs) {
                error("Expected factor after +");
                break;
            }

            lhs = new AddExpr(lhs, rhs);
        } else if (accept('-')) {
            Expr* rhs = parseTerm();
            if (!rhs) {
                error("Expected factor after -");
                break;
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
        if (accept('*')) {
            Expr* rhs = parseFactor();
            if (!rhs) {
                error("Expected factor after *");
                break;
            }
            
            lhs = new MulExpr(lhs, rhs);
        } else if (accept('/')) {
            Expr* rhs = parseFactor();
            if (!rhs) {
                error("Expected factor after /");
                break;
            }

            lhs = new DivExpr(rhs, lhs);
        } else if (accept('%')) {
            Expr* rhs = parseFactor();
            if (!rhs) {
                error("Expected factor after %");
                break;
            }

            lhs = new ModExpr(rhs, lhs);
        } else 
            break;
    }

    return lhs;
}

Expr* Parser::parseFactor() {
    const bool negate = accept('-');
  
    i32_t num;
    std::string ident;

    Expr* expr = nullptr;

    if (readNumber(num))
        expr = new NumExpr(num);
    else if (accept('(')) {
        expr = parseExpr();
        expect(')');
    } else if (readIdentifier(ident)) {
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