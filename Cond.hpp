#ifndef ALPHA_CONDITION_HPP
#define ALPHA_CONDITION_HPP

#include <iostream>
#include "Operation.hpp"

enum CondType {
	COND_NONE,
	COND_AND,
	COND_OR,
	COND_XOR
};

struct CondOptions {
	std::string if_label;
	std::string else_label;

	CondType cond_type = COND_AND;

	CondOptions() = default;
	explicit CondOptions(const std::string&, const std::string&, CondType the_cond_type);
};

struct Compare : public Operation {
	CondOptions cond_options;

	explicit Compare(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct GreaterOp : public Compare {
	explicit GreaterOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct GreaterEqualOp : public Compare {
	explicit GreaterEqualOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct LowerOp : public Compare {
	explicit LowerOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct LowerEqualOp : public Compare {
	explicit LowerEqualOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct EqualOp : public Compare {
	explicit EqualOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct NotEqualOp : public Compare {
	explicit NotEqualOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct Cond : public Compare {
	explicit Cond(const Compare*, const Compare*);

	virtual void eval(std::ostream&) const override;
};

#endif