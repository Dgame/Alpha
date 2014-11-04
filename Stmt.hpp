#ifndef ALPHA_STMT_HPP
#define ALPHA_STMT_HPP

#include <iostream>

struct Statement {
	virtual void eval(std::ostream&) const = 0;
};

#endif