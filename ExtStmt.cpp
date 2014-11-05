#include "ExtStmt.hpp"
#include "Expr.hpp"
#include "Var.hpp"

IfStmt::IfStmt(const std::string& label, Compare* the_cond, Scope* the_scope) : no_label(label), cond(the_cond), scope(the_scope) {
	this->cond->no_label = this->no_label;
}

void IfStmt::eval(std::ostream& out) const {
	this->cond->eval(out);
	this->scope->eval(out);
	out << this->no_label << ':' << std::endl;
}