#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>
#include <vector>
#include <set>
#include <list>
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
struct VarElement;

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

	virtual const VarElement* isVarElement() const {
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

	bool isAssociative() const {
		return this->op != Op::Div && this->op != Op::Mod && this->op != Op::Minus;
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

struct VarElement : public Literal {
	const Variable* variable;
	const unsigned int offset;

	explicit VarElement(const Variable* vp, unsigned int os);

	const VarElement* isVarElement() const override {
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
	bool inPlace = false;

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
	std::unique_ptr<Compare> primary;
	std::map<Link, std::unique_ptr<Compare>> comps;

	const Condition* isCondition() const override {
		return this;
	}

	void setPrimary(Compare* cp) {
		this->primary = std::unique_ptr<Compare>(cp);
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

#endif