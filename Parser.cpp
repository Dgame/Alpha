#include "Parser.hpp"
#include "Expr.hpp"

#include <locale>
#include <fstream>
#include <iostream>

void Parser::skip_spaces() {
    while (!this->loc.eof() && std::isspace(this->loc.current())) {
        ++this->loc.pos;
    }
}

bool Parser::accept(const std::string& tok) {
    skip_spaces();
    const Loc my_loc = this->loc;

    for (char c : tok) {
        if (this->loc.eof() || c != this->loc.current()) {
            this->loc = my_loc;
            return false;
        }
        this->loc.pos++;
    }

    return true;
}

bool Parser::expect(const std::string& tok) {
    skip_spaces();
    const Loc my_loc = this->loc;

    for (char c : tok) {
        if (c != this->loc.current()) {
            this->loc = my_loc;
            error("Did expected '" + tok);
            return false;
        }

        this->loc.pos++;
    }

    return true;
}

bool Parser::read_identifier(std::string& ident) {
    skip_spaces();

    if (!this->loc.eof() && (std::isalpha(this->loc.current()) || this->loc.current() == '_')) {
        ident += this->loc.current();
        while (std::isalnum(this->loc.current())) {
            ident += this->loc.current();
        }

        return true;
    }

    return false;
}

bool Parser::read_number(i32_t& num) {
    skip_spaces();

    if (!this->loc.eof() && std::isdigit(this->loc.current())) {
        num = 0;
        do {
            num *= 10;
            num += this->loc.current() - '0';

            this->loc.pos++;
        } while (!this->loc.eof() && std::isdigit(this->loc.current()));

        return true;
    }

    return false;
}

void Parser::parse(const std::string& filename) {
    std::ifstream in_file(filename);

    std::string line;
    std::string ident;
    
    while (std::getline(in_file, line)) {
       this->loc.pos = &line[0];
       this->loc.end = (&*line.end()) - 1;
       this->loc.lineNr++;

        if (accept("print")) {
            Expr* exp = parseExpr();
            std::cout << "print something" << std::endl;
        } else if (read_identifier(ident)) {
            if (accept("=")) {
                Expr* exp = parseExpr();
            }
        }
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
    if (read_number(num)) {
        if (negate)
            num *= -1;
        return new NumExpr(num);
    }

    return nullptr;
}