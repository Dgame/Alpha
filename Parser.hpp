#ifndef ALPHA_PARSER_HPP
#define ALPHA_PARSER_HPP

#include <string>
#include "types.hpp"

class Expr;

struct Loc {
    const char* pos;
    const char* end;
    u32_t lineNr = 0;

    char current() const {
        return *(this->pos);
    }

    bool eof() const {
        return this->pos == this->end;
    }
};

struct Parser {
    Loc loc;

    void error(const std::string&) {
        
    }

    void skip_spaces();

    bool accept(const std::string&);
    bool expect(const std::string&);

    bool read_identifier(std::string&);
    bool read_number(i32_t&);

    void parse(const std::string&);

    Expr* parseExpr();
    Expr* parseTerm();
    Expr* parseFactor();
};

#endif