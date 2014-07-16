#include "Manager.hpp"
#include "Commands.hpp"

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

	if (var == nullptr) {
		std::cerr << "Unknown variable" << std::endl;

		return false;
	}

	if (exp == nullptr) {
		std::cerr << "Invalid expression" << std::endl;

		return false;
	}

	this->sm.curScope()->decls.emplace_back(patch::make_unique<Variable>(var->offset, name, exp, var->size));

	return true;
}

bool VarManager::assignVarAt(unsigned int index, const std::string& name, Expression* exp, unsigned int size) {
	const Variable* var = this->getVar(name);

	if (var == nullptr) {
		std::cerr << "Unknown variable" << std::endl;

		return false;
	}

	if (exp == nullptr) {
		std::cerr << "Invalid expression" << std::endl;
		
		return false;
	}

	const unsigned int offset = index * 4;
	if (offset >= var->size) {
		std::cerr << "Index out of bounds" << std::endl;

		return false;
	}

	this->sm.curScope()->decls.emplace_back(patch::make_unique<Variable>(offset, name, exp, size));

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