#ifndef ALPHA_VAR_HPP
#define ALPHA_VAR_HPP

#include <vector>
#include <memory>

#include "types.hpp"
#include "Expr.hpp"
#include "Stmt.hpp"

struct Var : public Statement {
	u32_t offset;

	explicit Var(u32_t the_offset);
};

struct VarVal : public Var {
	std::unique_ptr<const Expr> expr;
	std::unique_ptr<const Var> var;

	explicit VarVal(u32_t the_offset, const Expr*);
	explicit VarVal(u32_t the_offset, const Var*);

	virtual void eval(std::ostream&) const override;
};

enum class RefType {
	EnRef,
	DeRef
};

struct VarRef : public Var {
	u32_t addr;
	RefType refType;

	explicit VarRef(u32_t the_offset, const Var*, RefType rt);

	virtual void eval(std::ostream&) const override;
};

struct Array : public Var {
	std::vector<std::unique_ptr<const Expr>> items;

	explicit Array(u32_t the_offset, const std::initializer_list<const Expr*>&);

	virtual void eval(std::ostream&) const override;
};

#endif