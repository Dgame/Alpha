#ifndef ALPHA_EXT_STMT_HPP
#define ALPHA_EXT_STMT_HPP

#include <string>
#include <memory>

#include "Stmt.hpp"
#include "Cond.hpp"
#include "Scope.hpp"

struct IfStmt : public Statement {
	std::string no_label;
	std::unique_ptr<Compare> cond;
	std::unique_ptr<Scope> scope;

	explicit IfStmt(const std::string&, Compare*, Scope*);

	virtual void eval(std::ostream&) const override;
};

#endif