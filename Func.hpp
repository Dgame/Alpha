#ifndef ALPHA_FUNC_HPP
#define ALPHA_FUNC_HPP

#include <ostream>
#include <string>
#include <memory>
#include "Scope.hpp"

class Func {
private:
    std::string _name;
    std::unique_ptr<Scope> _scope;

public:
    explicit Func(const std::string&, Scope*);
    virtual ~Func() { }

    const std::string& getName() const {
        return _name;
    }

    Scope* getScope() {
        return _scope.get();
    }

    virtual void eval(std::ostream&) const;
};

#endif