#ifndef ALPHA_STATEMENT_HPP
#define ALPHA_STATEMENT_HPP

#include <memory>
#include "Stmt.hpp"
#include "Expr.hpp"

struct Var;

struct PrintStmt : public Statement {
	std::unique_ptr<const Expr> expr;
	std::string label;

	explicit PrintStmt(const Expr*);
	explicit PrintStmt(const std::string&);

	virtual void eval(std::ostream&) const override;
};

#endif