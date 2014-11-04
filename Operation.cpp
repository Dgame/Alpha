#include "Operation.hpp"
#include "asm.hpp"

Operation::Operation(const Expr* left, const Expr* right) : lhs(left), rhs(right) {

}

AddOp::AddOp(const Expr* left, const Expr* right) : Operation(left, right) {

}

void AddOp::eval(std::ostream& out) const {
	out << "# Begin AddOp " << std::endl;

	if (this->lhs->needEval()) {
		this->lhs->eval(out);
		gas::push(out, E_AX);
	}

	this->rhs->eval(out);
	gas::add(out, gas::Offset(this->lhs->getOffset(), P_STACK), E_AX);

	if (this->lhs->needEval())
		gas::add(out, 4, P_STACK);

	out << "# End AddOp " << std::endl;
}

SubOp::SubOp(const Expr* left, const Expr* right) : Operation(left, right) {

}

void SubOp::eval(std::ostream& out) const {
	out << "# Begin SubOp " << std::endl;

	if (this->lhs->needEval()) {
		this->lhs->eval(out);
		gas::push(out, E_AX);
	}

	this->rhs->eval(out);
	gas::sub(out, gas::Offset(this->lhs->getOffset(), P_STACK), E_AX);

	if (this->lhs->needEval())
		gas::add(out, 4, P_STACK);

	out << "# End SubOp " << std::endl;
}

MulOp::MulOp(const Expr* left, const Expr* right) : Operation(left, right) {

}

void MulOp::eval(std::ostream& out) const {
	out << "# Begin MulOp " << std::endl;

	if (this->lhs->needEval()) {
		this->lhs->eval(out);
		gas::push(out, E_AX);
	}

	this->rhs->eval(out);
	gas::imul(out, gas::Offset(this->lhs->getOffset(), P_STACK), E_AX);

	if (this->lhs->needEval())
		gas::add(out, 4, P_STACK);

	out << "# End MulOp " << std::endl;
}

DivOp::DivOp(const Expr* left, const Expr* right) : Operation(left, right) {

}

void DivOp::eval(std::ostream& out) const {
	out << "# Begin DivOp " << std::endl;

	out << "# End DivOp " << std::endl;
}