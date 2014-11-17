#include "Expr.hpp"
#include "asm.hpp"
#include "Var.hpp"

NumExpr::NumExpr(i32_t val) : _value(val) {

}

void NumExpr::eval(std::ostream& out) const {
	gas::mov(out, _value, E_AX);
}

StringExpr::StringExpr(const std::string& label) : _label(label) {

}

void StringExpr::eval(std::ostream& out) const {
	gas::mov(out, _label, E_AX);
}

VarExpr::VarExpr(const Var* var) : _var(var) {

}

void VarExpr::eval(std::ostream& out) const {
	gas::mov(out, Offset(_var->getBaseOffset(), P_BASE), E_AX);
}

PtrExpr::PtrExpr(const Var* var) : VarExpr(var) {

}

void PtrExpr::eval(std::ostream& out) const {
	if (_var)
		gas::lea(out, Offset(_var->getBaseOffset(), P_STACK), E_AX);
	else
		gas::mov(out, 0, E_AX);
}

DerefExpr::DerefExpr(const Var* var) : VarExpr(var) {

}

void DerefExpr::eval(std::ostream& out) const {
	gas::mov(out, Offset(_var->getBaseOffset(), P_STACK), E_AX);
	gas::mov(out, Offset(0, E_AX), E_AX);
}

BinaryExpr::BinaryExpr(const Expr* left, const Expr* right) : lhs(left), rhs(right) {

}

AddOp::AddOp(const Expr* left, const Expr* right) : BinaryExpr(left, right) {

}

void AddOp::eval(std::ostream& out) const {
	out << "# Begin AddOp " << std::endl;

	i32_t val;
	if (this->lhs->cte(&val))
		gas::push(out, val);
	else {
		this->lhs->eval(out);
		gas::push(out, E_AX);
	}
	this->rhs->eval(out);

	gas::add(out, Offset(0, P_STACK), E_AX);
	gas::add(out, 4, P_STACK);

	out << "# End AddOp " << std::endl;
}

SubOp::SubOp(const Expr* left, const Expr* right) : BinaryExpr(left, right) {

}

void SubOp::eval(std::ostream& out) const {
	out << "# Begin SubOp " << std::endl;

	i32_t val;
	if (this->lhs->cte(&val))
		gas::push(out, val);
	else {
		this->lhs->eval(out);
		gas::push(out, E_AX);
	}
	this->rhs->eval(out);

	gas::sub(out, Offset(0, P_STACK), E_AX);
	gas::add(out, 4, P_STACK);

	out << "# End SubOp " << std::endl;
}

MulOp::MulOp(const Expr* left, const Expr* right) : BinaryExpr(left, right) {

}

void MulOp::eval(std::ostream& out) const {
	out << "# Begin MulOp " << std::endl;

	i32_t val;
	if (this->lhs->cte(&val))
		gas::push(out, val);
	else {
		this->lhs->eval(out);
		gas::push(out, E_AX);
	}
	this->rhs->eval(out);

	gas::imul(out, Offset(0, P_STACK), E_AX);
	gas::add(out, 4, P_STACK);

	out << "# End MulOp " << std::endl;
}

DivOp::DivOp(const Expr* left, const Expr* right) : BinaryExpr(left, right) {

}

void DivOp::eval(std::ostream& out) const {
	out << "# Begin DivOp " << std::endl;

	this->lhs->eval(out);
	gas::mov(out, E_AX, E_BX);
	this->rhs->eval(out);

	gas::mov(out, 0, E_DX);
	gas::idiv(out, E_BX);

	out << "# End DivOp " << std::endl;
}

ModOp::ModOp(const Expr* left, const Expr* right) : DivOp(left, right) {

}

void ModOp::eval(std::ostream& out) const {
	out << "# Begin ModOp " << std::endl;

	DivOp::eval(out);
	gas::mov(out, E_DX, E_AX);

	out << "# End ModOp " << std::endl;
}