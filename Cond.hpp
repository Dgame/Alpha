#ifndef ALPHA_CONDITION_HPP
#define ALPHA_CONDITION_HPP

#include <iostream>
#include "Operation.hpp"

struct Compare : public Operation {
	std::string no_label;

	explicit Compare(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct GreaterOp : public Compare {
	bool equal;

	explicit GreaterOp(const Expr*, const Expr*, bool eq = false);

	virtual void eval(std::ostream&) const override;
};

struct LowerOp : public Compare {
	bool equal;

	explicit LowerOp(const Expr*, const Expr*, bool eq = false);

	virtual void eval(std::ostream&) const override;
};

struct EqualOp : public Compare {
	bool equal;

	explicit EqualOp(const Expr*, const Expr*, bool eq = true);

	virtual void eval(std::ostream&) const override;
};

struct AndOp : public Operation {
	explicit AndOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct OrOp : public Operation {
	explicit OrOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

#endif