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

struct Operation : public Expr {
	const std::unique_ptr<const Expr> lhs;
	const std::unique_ptr<const Expr> rhs;

	explicit Operation(const Expr* left, const Expr* right);
};

struct AddOp : public Operation {
	explicit AddOp(const Expr* left, const Expr* right);

	virtual void eval(std::ostream&) const override;
};

struct SubOp : public Operation {
	explicit SubOp(const Expr* left, const Expr* right);

	virtual void eval(std::ostream&) const override;
};

struct MulOp : public Operation {
	explicit MulOp(const Expr* left, const Expr* right);

	virtual void eval(std::ostream&) const override;
};

struct DivOp : public Operation {
	explicit DivOp(const Expr* left, const Expr* right);

	virtual void eval(std::ostream&) const override;
};

#endif