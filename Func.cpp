#include "asm.hpp"
#include "Func.hpp"

Function::Function(const std::string& the_name, Scope* the_scope) : name(the_name), scope(the_scope) {
	if (this->name == "main")
		this->name = "alpha_main"; // Hack
}

void Function::eval(std::ostream& out) const {
	out << ".globl\t_" << this->name << "\n.def\t_" << this->name << "\n" << std::endl;
	out << '_' << this->name << ':' << std::endl;

	gas::push(out, P_BASE);
	gas::mov(out, P_STACK, P_BASE);
	gas::sub(out, this->scope->stack_size, P_STACK);

	this->scope->eval(out);

	gas::add(out, this->scope->stack_size, P_STACK);
	gas::pop(out, P_BASE);
	gas::ret(out);
}