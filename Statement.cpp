#include "Statement.hpp"
#include "asm.hpp"
#include "Var.hpp"

PrintStmt::PrintStmt(const Var* the_var) : var(the_var) {

}

PrintStmt::PrintStmt(const Expr* the_expr) : expr(the_expr) {

}

void PrintStmt::eval(std::ostream& out) const {
	out << "# Begin print" << std::endl;

	if (this->var)
		gas::push(out, Offset(this->var->offset, gas::Pointer::Stack));
	else if (this->expr) {
		this->expr->eval(out);
		gas::push(out, gas::Register::AX);
	}

	gas::call(out, "_print");
	gas::add(out, 4, gas::Pointer::Stack);

	out << "# End print" << std::endl;
}