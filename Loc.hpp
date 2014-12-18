#ifndef ALPHA_LOC_HPP
#define ALPHA_LOC_HPP

#include "types.hpp"
#include <fstream>

struct Loc {
    u32_t lineNr = 1;
    std::ifstream* input_file = nullptr;
    
    Loc() = default;
    explicit Loc(std::ifstream&);

    char current() const {
        return input_file->peek();
    }

    void next() {
        input_file->ignore();
    }

    bool eof() const {
        return input_file->eof();
    }
};

#endif