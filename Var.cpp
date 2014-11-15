#include "Var.hpp"
#include "asm.hpp"

Var::Var(const Expr* exp, bool mut, u32_t size) : _byte_size(size), _mut(mut), _expr(exp) {

}

void Var::eval(std::ostream& out) const {
	out << "# Begin Var" << std::endl;

	i32_t val;
	std::string ident;

	if (_expr->cte(&val))
		gas::mov(out, val, Offset(_stack_offset, P_STACK));
	else if (_expr->cte(&ident))
		gas::mov(out, ident, Offset(_stack_offset, P_STACK));
	else {
		_expr->eval(out);
		gas::mov(out, E_AX, Offset(_stack_offset, P_STACK));
	}

	out << "# End Var" << std::endl;
}