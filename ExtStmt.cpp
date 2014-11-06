#include "ExtStmt.hpp"
#include "Expr.hpp"
#include "Var.hpp"
#include "asm.hpp"

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

	if (this->else_stmt)
		this->else_stmt->eval(out);

	out << "# End if" << std::endl;
}

ElseStmt::ElseStmt(const std::string& the_end_label, const Compare* the_cond, Scope* the_scope)
	: end_label(the_end_label), cond(the_cond), scope(the_scope)
{

}

void ElseStmt::eval(std::ostream& out) const {
	out << "# Begin else" << std::endl;

	if (this->cond)
		this->cond->eval(out);
	this->scope->eval(out);
	out << this->end_label << ':' << std::endl;

	out << "# End else" << std::endl;
}

WhileLoopStmt::WhileLoopStmt(const std::string& label1, const std::string& label2, const std::string& label3, const Compare* the_cond, Scope* the_scope)
	: top_label(label1), start_label(label2), end_label(label3), cond(the_cond), scope(the_scope)
{

}

void WhileLoopStmt::eval(std::ostream& out) const {
	out << "# Begin while" << std::endl;

	out << this->top_label << ':' << std::endl;
	this->cond->eval(out);
	out << this->start_label << ':' << std::endl;
	out << "# Begin Loop" << std::endl;
	this->scope->eval(out);
	out << "# End Loop" << std::endl;
	gas::jmp(out, JMP_IMMEDIATE, this->top_label);
	out << this->end_label << ':' << std::endl;

	out << "# End while" << std::endl;
}