#include "Expr.hpp"
#include "asm.hpp"
#include "VarDecl.hpp"

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

VarExpr::VarExpr(const VarDecl* var) : _var(var) {

}

void VarExpr::eval(std::ostream& out) const {
	gas::mov(out, Offset(_var->getBaseOffset(), P_BASE), E_AX);
}

PtrExpr::PtrExpr(const VarDecl* var) : VarExpr(var) {

}

void PtrExpr::eval(std::ostream& out) const {
	if (_var)
		gas::lea(out, Offset(_var->getBaseOffset(), P_STACK), E_AX);
	else
		gas::mov(out, 0, E_AX);
}

DerefExpr::DerefExpr(const VarDecl* var) : VarExpr(var) {

}

void DerefExpr::eval(std::ostream& out) const {
	gas::mov(out, Offset(_var->getBaseOffset(), P_STACK), E_AX);
	gas::mov(out, Offset(0, E_AX), E_AX);
}

BinaryExpr::BinaryExpr(const Expr* left, const Expr* right) : lhs(left), rhs(right) {

}

AddExpr::AddExpr(const Expr* left, const Expr* right) : BinaryExpr(left, right) {

}

void AddExpr::eval(std::ostream& out) const {
	out << "# Begin AddExpr " << std::endl;

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

	out << "# End AddExpr " << std::endl;
}

SubExpr::SubExpr(const Expr* left, const Expr* right) : BinaryExpr(left, right) {

}

void SubExpr::eval(std::ostream& out) const {
	out << "# Begin SubExpr " << std::endl;

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

	out << "# End SubExpr " << std::endl;
}

MulExpr::MulExpr(const Expr* left, const Expr* right) : BinaryExpr(left, right) {

}

void MulExpr::eval(std::ostream& out) const {
	out << "# Begin MulExpr " << std::endl;

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

	out << "# End MulExpr " << std::endl;
}

DivExpr::DivExpr(const Expr* left, const Expr* right) : BinaryExpr(left, right) {

}

void DivExpr::eval(std::ostream& out) const {
	out << "# Begin DivExpr " << std::endl;

	this->lhs->eval(out);
	gas::mov(out, E_AX, E_BX);
	this->rhs->eval(out);

	gas::mov(out, 0, E_DX);
	gas::idiv(out, E_BX);

	out << "# End DivExpr " << std::endl;
}

ModExpr::ModExpr(const Expr* left, const Expr* right) : DivExpr(left, right) {

}

void ModExpr::eval(std::ostream& out) const {
	out << "# Begin ModExpr " << std::endl;

	DivExpr::eval(out);
	gas::mov(out, E_DX, E_AX);

	out << "# End ModExpr " << std::endl;
}