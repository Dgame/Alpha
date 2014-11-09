#ifndef ALPHA_EXPR_HPP
#define ALPHA_EXPR_HPP

#include <ostream>
#include "types.hpp"

struct Expr {
	virtual ~Expr() { }

	virtual bool isTmpVal() const {
		return true;
	}

	virtual bool isCTE() const {
		return false;
	}

	virtual void cte(const i32_t** ptr) const {
		*ptr = nullptr;
	}

	virtual void eval(std::ostream&) const = 0;
};

struct NumExpr : public Expr {
	i32_t value;

	explicit NumExpr(i32_t val);

	virtual void cte(const i32_t** ptr) const override {
		*ptr = &this->value;
	}

	virtual void eval(std::ostream&) const override;
};

struct Var;

struct VarExpr : public Expr {
	const Var* var;

	explicit VarExpr(const Var*);

	virtual bool isTmpVal() const override {
		return false;
	}

	virtual void eval(std::ostream&) const override;
};

#endif