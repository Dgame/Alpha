#ifndef ALPHA_FUNC_HPP
#define ALPHA_FUNC_HPP

#include <string>
#include <vector>
#include <memory>

#include "Scope.hpp"

struct Function {
	std::string name;
	std::vector<std::string> args;
	// TODO: Return
	std::unique_ptr<Scope> scope;

	explicit Function(const std::string&, const std::vector<std::string>&, Scope*);

	void eval(std::ostream&) const;
};

#endif