#ifndef ALPHA_ENV_HPP
#define ALPHA_ENV_HPP

#include <ostream>
#include <vector>
#include <memory>
#include "Labels.hpp"
#include "Func.hpp"

class Env {
private:
    std::vector<std::unique_ptr<const Func>> _funcs;

public:
    Labels labels;

    void addFunc(const Func*);
    void eval(std::ostream&) const;
};

#endif