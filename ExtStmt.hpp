#ifndef ALPHA_EXT_STMT_HPP
#define ALPHA_EXT_STMT_HPP

#include <string>
#include <memory>

#include "Stmt.hpp"
#include "Cond.hpp"
#include "Scope.hpp"

struct ElseStmt;

struct IfStmt : public Statement {
	std::string if_label;
	std::string else_label;

	std::unique_ptr<const Compare> cond;
	std::unique_ptr<Scope> scope;
	std::unique_ptr<const ElseStmt> else_stmt;

	explicit IfStmt(const std::string&, const std::string&, const Compare*, Scope*);

	virtual void eval(std::ostream&) const override;
};

struct ElseStmt : public Statement {
	std::string end_label;

	std::unique_ptr<const Compare> cond;
	std::unique_ptr<Scope> scope;

	explicit ElseStmt(const std::string&, const Compare*, Scope*);

	virtual void eval(std::ostream&) const override;
};

struct WhileLoopStmt : public Statement {
	std::string top_label;
	std::string start_label;
	std::string end_label;

	std::unique_ptr<const Compare> cond;
	std::unique_ptr<Scope> scope;

	explicit WhileLoopStmt(const std::string&, const std::string&, const std::string&, const Compare*, Scope*);

	virtual void eval(std::ostream&) const override;
};

struct FuncCallStmt : public Statement {
	std::string label;
	std::vector<std::unique_ptr<const Expr>> params;

	explicit FuncCallStmt(const std::string&);
	virtual void eval(std::ostream&) const override;
};

#endif