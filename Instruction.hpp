#ifndef ALPHA_INSTR_HPP
#define ALPHA_INSTR_HPP

#include <ostream>

class Instruction {
public:
	virtual void eval(std::ostream&) const = 0;
};

#endif