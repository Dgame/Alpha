#include "Func.hpp"
#include "asm.hpp"

Func::Func(const std::string& name, Scope* scope) : _name(name), _scope(scope) {

}

void Func::eval(std::ostream& out) const {
    const std::string my_name = _name == "main" ? "alpha_main" : _name;

    out << ".globl\t_" << my_name << std::endl;
    out << '_' << my_name << ':' << std::endl;

    gas::push(out, P_BASE);
    gas::mov(out, P_STACK, P_BASE);

    _scope->prepare();
    _scope->eval(out);

    gas::pop(out, P_BASE);

    out << "ret" << std::endl;
}