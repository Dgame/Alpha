#ifndef ALPHA_EXPR_HPP
#define ALPHA_EXPR_HPP

#include <iostream>
#include <memory>
#include "types.hpp"

struct NumExpr;

struct Expr {
	virtual ~Expr() { }

	virtual void eval(std::ostream&) const = 0;

	virtual const NumExpr* isNumExpr() const {
		return nullptr;
	}
};

struct NumExpr : public Expr {
	i32_t value;

	explicit NumExpr(i32_t val);

	virtual const NumExpr* isNumExpr() const override {
		return this;
	}

	virtual void eval(std::ostream&) const override;
};

struct VarExpr : public Expr {
	u32_t offset;

	explicit VarExpr(u32_t the_offset);

	virtual void eval(std::ostream&) const override;
};

#endif