#ifndef ALPHA_EXPR_HPP
#define ALPHA_EXPR_HPP

#include <iostream>
#include <memory>
#include "types.hpp"

struct Expr {
	virtual ~Expr() { }

	// offset (default 0) used for operations
	virtual u32_t getOffset() const {
		return 0;
	}

	// compile time eval. if not possible, ptr is null
	virtual void cte(const i32_t** ptr) const {
		*ptr = nullptr;
	}

	// Requires storage?
	virtual bool requireStoring() const {
		return true;
	}

	virtual void eval(std::ostream&) const = 0;
};

struct NumExpr : public Expr {
	i32_t value;

	explicit NumExpr(i32_t val);

	virtual void cte(const i32_t** ptr) const {
		*ptr = &this->value;
	}

	virtual void eval(std::ostream&) const override;
};

struct VarExpr : public Expr {
	u32_t offset;

	explicit VarExpr(u32_t the_offset);

	virtual u32_t getOffset() const override {
		return this->offset;
	}

	virtual bool requireStoring() const {
		return false;
	}

	virtual void eval(std::ostream&) const override;
};

#endif