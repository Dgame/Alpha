#include "Func.hpp"
#include "asm.hpp"

Function::Function(const std::string& the_name, const std::vector<std::string>& the_args, Scope* the_scope) : name(the_name), args(the_args), scope(the_scope) {
	for (const std::string& arg : this->args) {
		const u32_t offset = this->scope->grow(4);

		Var* var = new VarVal(offset, nullptr); // since we can't use Var, use a fake/empty VarVal
		this->params.emplace_back(var);
		this->scope->vars[arg] = var;
	}
}

void Function::eval(std::ostream& out) const {
	const std::string& my_name = (this->name == "main") ? "alpha_main" : this->name;

	out << ".globl\t_" << my_name << std::endl;
	out << '_' << my_name << ':' << std::endl;

	gas::push(out, P_BASE);
	gas::mov(out, P_STACK, P_BASE);

	if (this->scope->stack_size != 0)
		gas::sub(out, this->scope->stack_size, P_STACK);

	if (this->args.size() != 0) {
		out << "# Begin Parameters" << std::endl;

		u32_t offset = 8 + (this->args.size() * 4);
		u32_t stack = 0;
		while (offset > 8) {
			offset -= 4;
			gas::mov(out, gas::Offset(offset, P_BASE), E_AX);
			gas::mov(out, E_AX, gas::Offset(stack, P_STACK));
			stack += 4;
		}

		out << "# End Parameters" << std::endl;
	}

	this->scope->eval(out);

	if (this->scope->stack_size != 0)
		gas::add(out, this->scope->stack_size, P_STACK);
	
	gas::pop(out, P_BASE);
	gas::ret(out);

	out << std::endl;
}