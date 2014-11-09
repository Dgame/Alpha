#ifndef ALPHA_SCOPE_HPP
#define ALPHA_SCOPE_HPP

#include <ostream>
#include <string>
#include <memory>
#include <vector>
#include <map>

#include "types.hpp"
#include "Var.hpp"

class Scope {
private:
	std::vector<std::unique_ptr<const Var>> _tmpVars;
	std::map<std::string, std::unique_ptr<const Var>> _vars;

public:
	Scope* predecessor;

	explicit Scope(Scope*);

	void addVar(const std::string&, const Var*, bool tmp = false);
	const Var* getVar(const std::string&) const;

	virtual void eval(std::ostream&) const;
};

#endif