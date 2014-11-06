#include "Cond.hpp"
#include "asm.hpp"

CondOptions::CondOptions(const std::string& the_if_label, const std::string& the_else_label, CondType the_cond_type)
	: if_label(the_if_label), else_label(the_else_label), cond_type(the_cond_type)
{
	
}

Compare::Compare(const Expr* left, const Expr* right) : Operation(left, right) {

}

void Compare::eval(std::ostream& out) const {
	this->lhs->eval(out);
	gas::mov(out, E_AX, E_BX);
	this->rhs->eval(out);
	gas::cmp(out, E_AX, E_BX);
}

GreaterOp::GreaterOp(const Expr* left, const Expr* right) : Compare(left, right)
{

}

void GreaterOp::eval(std::ostream& out) const {
	Compare::eval(out);
	if (this->cond_options.cond_type == COND_AND)
		gas::jmp(out, JMP_IF_LOWER_OR_EQUAL, this->cond_options.else_label);
	else if (this->cond_options.cond_type == COND_OR)
		gas::jmp(out, JMP_IF_GREATER, this->cond_options.if_label);
}

GreaterEqualOp::GreaterEqualOp(const Expr* left, const Expr* right) : Compare(left, right)
{

}

void GreaterEqualOp::eval(std::ostream& out) const {
	Compare::eval(out);
	if (this->cond_options.cond_type == COND_AND)
		gas::jmp(out, JMP_IF_LOWER, this->cond_options.else_label);
	else if (this->cond_options.cond_type == COND_OR)
		gas::jmp(out, JMP_IF_GREATER_OR_EQUAL, this->cond_options.if_label);
}

LowerOp::LowerOp(const Expr* left, const Expr* right) : Compare(left, right)
{

}

void LowerOp::eval(std::ostream& out) const {
	Compare::eval(out);
	if (this->cond_options.cond_type == COND_AND)
		gas::jmp(out, JMP_IF_GREATER_OR_EQUAL, this->cond_options.else_label);
	else if (this->cond_options.cond_type == COND_OR)
		gas::jmp(out, JMP_IF_LOWER, this->cond_options.if_label);
}

LowerEqualOp::LowerEqualOp(const Expr* left, const Expr* right) : Compare(left, right)
{

}

void LowerEqualOp::eval(std::ostream& out) const {
	Compare::eval(out);
	if (this->cond_options.cond_type == COND_AND)
		gas::jmp(out, JMP_IF_GREATER, this->cond_options.else_label);
	else if (this->cond_options.cond_type == COND_OR)
		gas::jmp(out, JMP_IF_LOWER_OR_EQUAL, this->cond_options.if_label);
}

EqualOp::EqualOp(const Expr* left, const Expr* right) : Compare(left, right)
{

}

void EqualOp::eval(std::ostream& out) const {
	Compare::eval(out);
	if (this->cond_options.cond_type == COND_AND)
		gas::jmp(out, JMP_IF_NOT_EQUAL, this->cond_options.else_label);
	else if (this->cond_options.cond_type == COND_OR)
		gas::jmp(out, JMP_IF_EQUAL, this->cond_options.if_label);
}

NotEqualOp::NotEqualOp(const Expr* left, const Expr* right) : Compare(left, right)
{

}

void NotEqualOp::eval(std::ostream& out) const {
	Compare::eval(out);
	if (this->cond_options.cond_type == COND_AND)
		gas::jmp(out, JMP_IF_EQUAL, this->cond_options.else_label);
	else if (this->cond_options.cond_type == COND_OR)
		gas::jmp(out, JMP_IF_NOT_EQUAL, this->cond_options.if_label);
}

Cond::Cond(const Compare* left_cmp, const Compare* right_cmp) : Compare(left_cmp, right_cmp) {

}

void Cond::eval(std::ostream& out) const {
	this->lhs->eval(out);
	this->rhs->eval(out);
}