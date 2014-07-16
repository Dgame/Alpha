#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include "Expression.hpp"

struct Command;

struct Scope {
	unsigned int nr;
	std::vector<std::unique_ptr<Command>> decls;

	explicit Scope(unsigned int mynr);

	std::string label() const {
		return "L" + patch::to_string(this->nr);
	}

	std::string hlabel() const {
		return this->label() + "H";
	}
};

struct ScopeManager {
	std::list<std::unique_ptr<Scope>> scopes;
	unsigned int count = 0;

	void pushScope() {
		this->scopes.emplace_front(patch::make_unique<Scope>(this->count++));
	}

	std::unique_ptr<Scope> popScope() {
		std::unique_ptr<Scope> sc = std::move(this->scopes.front());
		this->scopes.pop_front();

		return std::move(sc);
	}

	Scope* curScope() {
		return this->scopes.front().get();
	}
};

struct VarManager {
	ScopeManager& sm;
	std::set<std::string> varNames;
	
	unsigned int stackSize = 0;

	explicit VarManager(ScopeManager& sr);

	bool createVar(const std::string& name, Expression* exp, unsigned int size = 4);
	bool assignVar(const std::string& name, Expression* exp);
	bool assignVarAt(unsigned int index, const std::string& name, Expression* exp, unsigned int size = 4);
	const Variable* getVar(const std::string& name) const;
};

struct CommandManager {
	ScopeManager& sm;

	explicit CommandManager(ScopeManager& sr);

	void push(Command* cmd) {
		this->sm.curScope()->decls.emplace_back(std::unique_ptr<Command>(cmd));
	}
};

#endif