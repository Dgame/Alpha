#include "Expr.hpp"
#include "asm.hpp"

NumExpr::NumExpr(int val) : value(val) {

}

void NumExpr::eval(std::ostream& out) const {
	out << "# Begin NumExpr " << std::endl;
	gas::mov(out, this->value, E_AX);
	out << "# End NumExpr " << std::endl;
}

VarExpr::VarExpr(u32_t the_offset) : offset(the_offset) {

}

void VarExpr::eval(std::ostream& out) const {
	out << "# Begin VarExpr " << std::endl;
	gas::mov(out, gas::Offset(this->offset, P_STACK), E_AX);
	out << "# End VarExpr " << std::endl;
}