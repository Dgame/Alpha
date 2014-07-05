#include "Expression.hpp"

Value::Value(int val) : value(val) {

}

Operator::Operator(Op myop) : op(myop) {

}

Var::Var(const Variable* vp) : variable(vp) {

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

If::If(const std::string& label, Condition* cp) : labelIf(label), cond(cp) {

}

VarManager::VarManager(Scopes& sc) : scopes(sc) {

}

bool VarManager::createVar(const std::string& name, Expression* exp, unsigned int size) {
	if (this->varNames.find(name) != this->varNames.end())
		return false;

	this->scopes.curScope().decls.emplace_back(patch::make_unique<Variable>(this->stackSize, name, exp, size));
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

	this->scopes.curScope().decls.emplace_back(patch::make_unique<Variable>(var->offset, name, exp, var->size));

	return true;
}

const Variable* VarManager::getVar(const std::string& name) const {
	for (std::unique_ptr<Command>& cmd : this->scopes.curScope().decls) {
		const Variable* var = cmd->isVariable();
		if (var != nullptr && var->name == name)
			return var;
	}

	return nullptr;
}

CommandManager::CommandManager(Scopes& sc) : scopes(sc) {

}