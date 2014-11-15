#ifndef ALPHA_LOC_HPP
#define ALPHA_LOC_HPP

#include "types.hpp"

struct Loc {
    const char* pos;
    const char* end;
    u32_t lineNr = 1;

    char current() const {
        return *(this->pos);
    }

    bool eof() const {
        return this->pos >= this->end;
    }
};

#endif