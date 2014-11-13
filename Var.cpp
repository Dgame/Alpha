#include "Var.hpp"
#include "asm.hpp"

Var::Var(const Expr* exp, bool mut) : _expr(exp), _mut(mut) {

}

void Var::eval(std::ostream& out) const {
	out << "# Begin Var" << std::endl;

	if (_expr->hasCTE())
		gas::mov(out, _expr->cte(), Offset(_stack_offset, P_STACK));
	else {
		_expr->eval(out);
		gas::mov(out, E_AX, Offset(_stack_offset, P_STACK));
	}

	out << "# End Var" << std::endl;
}