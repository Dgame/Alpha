#ifndef ALPHA_INSTR_HPP
#define ALPHA_INSTR_HPP

#include <ostream>
#include <vector>
#include <memory>

#include "Expr.hpp"

class Instr {
public:
	virtual ~Instr() { }

	virtual void eval(std::ostream&) const = 0;
};

class PrintInstr : public Instr {
private:
	std::vector<std::unique_ptr<const Expr>> _exprs;

public:
	PrintInstr() = default;
	explicit PrintInstr(const Expr*);
	void addExpr(const Expr*);

	virtual void eval(std::ostream&) const override;
};

#endif