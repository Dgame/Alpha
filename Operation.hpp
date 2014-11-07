#ifndef ALPHA_OP_HPP
#define ALPHA_OP_HPP

#include "Expr.hpp"

struct Operation : public Expr {
	const std::unique_ptr<const Expr> lhs;
	const std::unique_ptr<const Expr> rhs;

	explicit Operation(const Expr*, const Expr*);

	virtual ~Operation() { }
};

struct AddOp : public Operation {
	explicit AddOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct SubOp : public Operation {
	explicit SubOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct MulOp : public Operation {
	explicit MulOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct DivOp : public Operation {
	explicit DivOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct ModOp : public DivOp {
	explicit ModOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

#endif