#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Expression.hpp"

struct Print;
struct If;

struct Command {
	virtual const Print* isPrint() const {
		return nullptr;
	}

	virtual const If* isIf() const {
		return nullptr;
	}

	virtual const Variable* isVariable() const {
		return nullptr;
	}
};

struct Print : public Command {
	std::unique_ptr<Expression> exp;

	explicit Print(Expression* ep);

	const Print* isPrint() const override {
		return this;
	}
};

struct Variable : public Command {
	int offset = -1;
	unsigned int size = 0;

	std::string name;

	const std::unique_ptr<Expression> exp;

	explicit Variable(int offset, const std::string& name, Expression* ep, unsigned int size = 4);

	const Variable* isVariable() const override {
		return this;
	}
};

struct Scope;

struct If : public Command {
	std::unique_ptr<Condition> cond;

	std::unique_ptr<Scope> ifScope;
	std::unique_ptr<Scope> elseScope;

	explicit If(Condition* cp, Scope* isp, Scope* esp);

	const If* isIf() const override {
		return this;
	}
};

#endif