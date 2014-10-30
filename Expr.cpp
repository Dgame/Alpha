#include "Expr.hpp"
#include "asm.hpp"

NumExpr::NumExpr(int val) : value(val) {

}

void NumExpr::eval(std::ostream& out) const {
	out << "# Begin NumExpr " << std::endl;

	gas::mov(out, this->value, gas::Register::AX);

	out << "# End NumExpr " << std::endl;
}

Operation::Operation(const Expr* left, const Expr* right) : lhs(left), rhs(right) {

}

AddOp::AddOp(const Expr* left, const Expr* right) : Operation(left, right) {

}

void AddOp::eval(std::ostream& out) const {
	out << "# Begin AddOp " << std::endl;

	this->lhs->eval(out);
	gas::push(out, gas::Register::AX);
	this->rhs->eval(out);
	gas::add(out, Offset(0, gas::Pointer::Stack), gas::Register::AX);
	gas::add(out, 4, gas::Pointer::Stack);

	out << "# End AddOp " << std::endl;
}

SubOp::SubOp(const Expr* left, const Expr* right) : Operation(left, right) {

}

void SubOp::eval(std::ostream& out) const {
	out << "# Begin SubOp " << std::endl;

	this->lhs->eval(out);
	gas::push(out, gas::Register::AX);
	this->rhs->eval(out);
	gas::sub(out, Offset(0, gas::Pointer::Stack), gas::Register::AX);
	gas::add(out, 4, gas::Pointer::Stack);

	out << "# End SubOp " << std::endl;
}

MulOp::MulOp(const Expr* left, const Expr* right) : Operation(left, right) {

}

void MulOp::eval(std::ostream& out) const {
	out << "# Begin MulOp " << std::endl;

	this->lhs->eval(out);
	gas::push(out, gas::Register::AX);
	this->rhs->eval(out);
	gas::mul(out, Offset(0, gas::Pointer::Stack), gas::Register::AX);
	gas::add(out, 4, gas::Pointer::Stack);

	out << "# End MulOp " << std::endl;
}

DivOp::DivOp(const Expr* left, const Expr* right) : Operation(left, right) {

}

void DivOp::eval(std::ostream& out) const {
	out << "# Begin DivOp " << std::endl;

	out << "# End DivOp " << std::endl;
}