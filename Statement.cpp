#include "Statement.hpp"
#include "asm.hpp"
#include "Var.hpp"

PrintStmt::PrintStmt(const Expr* the_expr) : expr(the_expr) {

}

PrintStmt::PrintStmt(const std::string& the_label) : label(the_label) {

}

void PrintStmt::eval(std::ostream& out) const {
	out << "# Begin print" << std::endl;

	if (this->expr) {
		if (const NumExpr* num_expr = this->expr->isNumExpr())
			gas::push(out, num_expr->value);
		else {
			this->expr->eval(out);
			gas::push(out, E_AX);
		}
		
		gas::call(out, "_print_int");
	} else if (this->label.size()) {
		gas::push(out, this->label);
		gas::call(out, "_print_string");
	}

	gas::add(out, 4, P_STACK);

	out << "# End print" << std::endl;
}