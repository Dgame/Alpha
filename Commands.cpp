#include "Commands.hpp"
#include "Manager.hpp"

Variable::Variable(int offset, const std::string& name, Expression* ep, unsigned int size) : exp(ep) {
	this->offset = offset;
	this->name = name;
	this->size = size;
}

Print::Print(Expression* ep) : exp(ep) {

}

If::If(Condition* cp, Scope* isp, Scope* esp) : cond(cp), ifScope(isp), elseScope(esp) {

}