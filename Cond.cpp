#include "Cond.hpp"
#include "asm.hpp"

Compare::Compare(const Expr* left, const Expr* right) : Operation(left, right) {

}

void Compare::eval(std::ostream& out) const {
	this->lhs->eval(out);
	gas::mov(out, E_AX, E_BX);

	if (this->rhs)
		this->rhs->eval(out);
	else
		gas::mov(out, 1, E_AX);

	gas::cmp(out, E_AX, E_BX);
}

GreaterOp::GreaterOp(const Expr* left, const Expr* right, bool eq) : Compare(left, right), equal(eq) {

}

void GreaterOp::eval(std::ostream& out) const {
	Compare::eval(out);
	const JCond jcond = !this->equal ? JMP_IF_LOWER_OR_EQUAL : JMP_IF_LOWER;
	gas::jmp(out, jcond, this->no_label);
}

LowerOp::LowerOp(const Expr* left, const Expr* right, bool eq) : Compare(left, right), equal(eq) {

}

void LowerOp::eval(std::ostream& out) const {

}

EqualOp::EqualOp(const Expr* left, const Expr* right, bool eq) : Compare(left, right), equal(eq) {

}

void EqualOp::eval(std::ostream& out) const {

}

AndOp::AndOp(const Expr* left, const Expr* right) : Operation(left, right) {

}

void AndOp::eval(std::ostream& out) const {

}

OrOp::OrOp(const Expr* left, const Expr* right) : Operation(left, right) {

}

void OrOp::eval(std::ostream& out) const {

}
