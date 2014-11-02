#include "Expr.hpp"
#include "asm.hpp"

NumExpr::NumExpr(int val) : value(val) {

}

void NumExpr::eval(std::ostream& out) const {
	out << "# Begin NumExpr " << std::endl;

	gas::mov(out, this->value, E_AX);

	out << "# End NumExpr " << std::endl;
}