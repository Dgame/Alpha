#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>
#include <vector>
#include <set>
#include <map>
#include "patch.hpp"

enum class Op : char {
	Plus,
	Minus,
	Mul,
	Div,
	Mod,
	Negate
};

struct Value;
struct Operator;
struct Var;

struct Literal {
	virtual const Value* isValue() const {
		return nullptr;
	}

	virtual const Operator* isOperator() const {
		return nullptr;
	}

	virtual const Var* isVar() const {
		return nullptr;
	}
};

struct Value : public Literal {
	int value;

	explicit Value(int val);

	const Value* isValue() const override {
		return this;
	}
};

struct Operator : public Literal {
	Op op;

	explicit Operator(Op myop);

	const Operator* isOperator() const override {
		return this;
	}
};

struct Variable;

struct Var : public Literal {
	const Variable* variable;

	explicit Var(const Variable* vp);

	const Var* isVar() const override {
		return this;
	}
};

struct Term;
struct Compare;
struct Condition;
struct Array;

struct Expression {
	virtual const Term* isTerm() const {
		return nullptr;
	}

	virtual const Compare* isCompare() const {
		return nullptr;
	}

	virtual const Condition* isCondition() const {
		return nullptr;
	}

	virtual const Array* isArray() const {
		return nullptr;
	}
};

struct Term : public Expression {
	std::vector<std::unique_ptr<Literal>> literals;

	const Term* isTerm() const override {
		return this;
	}

	unsigned int count() const {
		return this->literals.size();
	}

	void push(Literal* lp) {
		this->literals.emplace_back(std::unique_ptr<Literal>(lp));
	}

	void push(Op op) {
		this->literals.emplace_back(patch::make_unique<Operator>(op));
	}

	void push(int num) {
		this->literals.emplace_back(patch::make_unique<Value>(num));
	}

	void push(const Variable* var) {
		this->literals.emplace_back(patch::make_unique<Var>(var));
	}

	const Literal* front() const {
		return this->literals[0].get();
	}

	const Literal* at(unsigned int index) const {
		return this->literals[index].get();
	}
};

enum class Cmp : char {
	Equal,
	NotEqual,
	Greater,
	Less,
	GreaterEqual,
	LessEqual
};

struct Compare : public Expression {
	std::unique_ptr<Expression> lhs;
	std::unique_ptr<Expression> rhs;
	Cmp cmp;

	explicit Compare(Expression* lp, Expression* rp, Cmp mycmp);

	const Compare* isCompare() const override {
		return this;
	}
};

enum class Link : char {
	And,
	Or,
	Xor
};

struct Condition : public Expression {
	std::unique_ptr<Compare> comp;
	std::map<Link, std::unique_ptr<Compare>> comps;

	explicit Condition(Compare* cp);

	const Condition* isCondition() const override {
		return this;
	}

	void push(Link lnk, Compare* cmp) {
		this->comps[lnk] = std::unique_ptr<Compare>(cmp);
	}
};

struct Array : public Expression {
	std::vector<std::unique_ptr<Expression>> exps;

	const Array* isArray() const override {
		return this;
	}

	unsigned int count() const {
		return this->exps.size();
	}

	void push(Expression* exp) {
		this->exps.emplace_back(std::unique_ptr<Expression>(exp));
	}
};

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
	std::string labelIf;
	std::string labelElse;

	std::unique_ptr<Condition> cond;

	Scope* ifScope = nullptr;
	Scope* elseScope = nullptr;

	explicit If(const std::string& label, Condition* cp);

	const If* isIf() const override {
		return this;
	}
};

struct Scope {
	std::vector<std::unique_ptr<Command>> decls;
};

struct Scopes {
	std::vector<Scope> scopes;
	int curIndex = -1;

	Scope& operator [](unsigned int index) {
		return this->scopes[index];
	}

	void pushScope() {
		this->scopes.push_back(Scope());
		this->curIndex++;
	}

	void popScope() {
		this->curIndex--;
	}

	Scope& curScope() {
		return this->scopes[this->curIndex];
	}
};

struct VarManager {
	Scopes& scopes;
	std::set<std::string> varNames;
	
	unsigned int stackSize = 0;

	explicit VarManager(Scopes& sc);

	bool createVar(const std::string& name, Expression* exp, unsigned int size = 4);
	bool assignVar(const std::string& name, Expression* exp);
	const Variable* getVar(const std::string& name) const;
};

struct CommandManager {
	Scopes& scopes;

	explicit CommandManager(Scopes& sc);

	void push(Command* cmd) {
		this->scopes.curScope().decls.emplace_back(std::unique_ptr<Command>(cmd));
	}
};

#endif