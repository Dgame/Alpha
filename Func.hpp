#ifndef ALPHA_FUNC_HPP
#define ALPHA_FUNC_HPP

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "Statement.hpp"

struct Expr;
struct Var;
enum class RefType;

struct Scope {
	u32_t stack_size = 0;

	std::map<std::string, const Var*> vars;
	std::vector<std::unique_ptr<const Statement>> statements;

	u32_t grow(u32_t size = 4);

	void make_var(const std::string&, const Var*, RefType rt);
	void make_var(const std::string&, const Expr*);
	void make_var(const std::string&, const Var*);

	const Var* getVar(const std::string&) const;

	void addStmt(const Statement*);

	void eval(std::ostream&) const;
};

struct Function {
	std::string name;
	// Parameter
	// Return
	Scope scope;

	explicit Function(const std::string&);

	void eval(std::ostream&) const;
};

#endif