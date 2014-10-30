#ifndef ALPHA_STATEMENT_HPP
#define ALPHA_STATEMENT_HPP

#include <memory>
#include "Stmt.hpp"
#include "Expr.hpp"

struct Var;

struct PrintStmt : public Statement {
	const Var* var = nullptr;
	std::unique_ptr<const Expr> expr;

	explicit PrintStmt(const Var*);
	explicit PrintStmt(const Expr*);

	virtual void eval(std::ostream&) const override;
};

#endif