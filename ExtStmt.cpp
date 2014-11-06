#include "ExtStmt.hpp"
#include "Expr.hpp"
#include "Var.hpp"

IfStmt::IfStmt(const std::string& the_if_label, const std::string& the_else_label, const Compare* the_cond, Scope* the_scope)
	: if_label(the_if_label), else_label(the_else_label), cond(the_cond), scope(the_scope)
{

}

void IfStmt::eval(std::ostream& out) const {
	out << "# Begin if" << std::endl;

	this->cond->eval(out);
	out << this->if_label << ':' << std::endl;
	this->scope->eval(out);
	out << this->else_label << ':' << std::endl;

	out << "# End if" << std::endl;
}