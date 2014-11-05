#ifndef ALPHA_STATEMENT_HPP
#define ALPHA_STATEMENT_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Expr.hpp"
#include "Stmt.hpp"

struct Var;

struct PrintStmt : public Statement {
	bool insertNewLine = true;

	std::unique_ptr<const Expr> expr;
	std::string label;

	explicit PrintStmt(const Expr*);
	explicit PrintStmt(const std::string&);

	virtual void eval(std::ostream&) const override;
};

struct MultiplePrintStmt : public Statement {
	std::vector<std::unique_ptr<PrintStmt>> prints;

	void append(PrintStmt*);
	// adjust for newlines at the end
	void adjust();

	virtual void eval(std::ostream&) const override;
};

#endif