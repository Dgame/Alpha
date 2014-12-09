#ifndef ALPHA_DECL_HPP
#define ALPHA_DECL_HPP

#include <ostream>
#include <vector>
#include <memory>

#include "Expr.hpp"

class Decl {
public:
    virtual ~Decl() { }

    virtual void eval(std::ostream&) const = 0;
};

class PrintDecl : public Decl {
private:
    std::vector<std::unique_ptr<const Expr>> _exprs;

public:
    PrintDecl() = default;
    explicit PrintDecl(const Expr*);
    void addExpr(const Expr*);

    virtual void eval(std::ostream&) const override;
};

#endif