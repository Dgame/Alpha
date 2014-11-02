#ifndef ALPHA_SCOPE_HPP
#define ALPHA_SCOPE_HPP

#include <map>
#include <vector>
#include "Statement.hpp"
#include "types.hpp"

struct Expr;
struct Var;
enum class RefType;

struct Scope {
	u32_t stack_size = 0;

	Scope* predecessor = nullptr;

	std::map<std::string, const Var*> vars;
	std::vector<std::unique_ptr<const Statement>> statements;

	u32_t grow(u32_t size = 4);

	void makeVar(const std::string&, const Var*, RefType rt);
	void makeVar(const std::string&, const Expr*);

	const Var* getVar(const std::string&) const;

	void addStmt(const Statement*);

	void eval(std::ostream&) const;
};

#endif