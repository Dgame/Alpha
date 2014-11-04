#ifndef ALPHA_FUNC_HPP
#define ALPHA_FUNC_HPP

#include <string>
#include <memory>

#include "Scope.hpp"

struct Function {
	std::string name;
	// Parameter
	// Return
	std::unique_ptr<Scope> scope;

	explicit Function(const std::string&, Scope*);

	void eval(std::ostream&) const;
};

#endif