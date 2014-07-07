#include "Expression.hpp"

Value::Value(int val) : value(val) {

}

Operator::Operator(Op myop) : op(myop) {

}

Var::Var(const Variable* vp) : variable(vp) {

}

VarElement::VarElement(const Variable* vp, unsigned int os) : variable(vp), offset(os) {

}

Compare::Compare(Expression* lp, Expression* rp, Cmp mycmp) : lhs(lp), rhs(rp), cmp(mycmp) {

}

Variable::Variable(int offset, const std::string& name, Expression* ep, unsigned int size) : exp(ep) {
	this->offset = offset;
	this->name = name;
	this->size = size;
}

Print::Print(Expression* ep) : exp(ep) {

}

If::If(Condition* cp, Scope* isp, Scope* esp) : cond(cp), ifScope(isp), elseScope(esp) {

}

Scope::Scope(unsigned int mynr) : nr(mynr) {

}

VarManager::VarManager(ScopeManager& sr) : sm(sr) {

}

bool VarManager::createVar(const std::string& name, Expression* exp, unsigned int size) {
	if (this->varNames.find(name) != this->varNames.end())
		return false;

	this->sm.curScope()->decls.emplace_back(patch::make_unique<Variable>(this->stackSize, name, exp, size));
	this->stackSize += size;
	this->varNames.emplace(name);

	return true;
}

bool VarManager::assignVar(const std::string& name, Expression* exp) {
	const Variable* var = this->getVar(name);
	if (var == nullptr)
		return false;

	if (exp == nullptr)
		return false;

	this->sm.curScope()->decls.emplace_back(patch::make_unique<Variable>(var->offset, name, exp, var->size));

	return true;
}

const Variable* VarManager::getVar(const std::string& name) const {
	for (std::unique_ptr<Command>& cmd : this->sm.curScope()->decls) {
		const Variable* var = cmd->isVariable();
		if (var != nullptr && var->name == name)
			return var;
	}

	auto it = this->sm.scopes.end();
	do {
		it--;
		
		for (std::unique_ptr<Command>& cmd : (*it)->decls) {
			const Variable* var = cmd->isVariable();
			if (var != nullptr && var->name == name)
				return var;
		}
	} while (it != this->sm.scopes.begin());

	return nullptr;
}

CommandManager::CommandManager(ScopeManager& sr) : sm(sr) {

}