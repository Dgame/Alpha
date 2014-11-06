#include "asm.hpp"
#include "Func.hpp"

Function::Function(const std::string& the_name, Scope* the_scope) : name(the_name), scope(the_scope) {

}

void Function::eval(std::ostream& out) const {
	const std::string& my_name = (this->name == "main") ? "alpha_main" : this->name;

	out << ".globl\t_" << my_name << "\n.def\t_" << my_name << "\n" << std::endl;
	out << '_' << my_name << ':' << std::endl;

	gas::push(out, P_BASE);
	gas::mov(out, P_STACK, P_BASE);

	if (this->scope->stack_size != 0)
		gas::sub(out, this->scope->stack_size, P_STACK);

	this->scope->eval(out);

	if (this->scope->stack_size != 0)
		gas::add(out, this->scope->stack_size, P_STACK);
	
	gas::pop(out, P_BASE);
	gas::ret(out);
}