#ifndef ALPHA_EXPR_HPP
#define ALPHA_EXPR_HPP

#include <iostream>
#include <memory>

struct NumExpr;

struct Expr {
	virtual void eval(std::ostream&) const = 0;

	virtual const NumExpr* isNumExpr() const {
		return nullptr;
	}
};

struct NumExpr : public Expr {
	int value;

	explicit NumExpr(int val);

	virtual const NumExpr* isNumExpr() const override {
		return this;
	}

	virtual void eval(std::ostream&) const override;
};

#endif