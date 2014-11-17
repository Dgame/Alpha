#ifndef ALPHA_EXPR_HPP
#define ALPHA_EXPR_HPP

#include <ostream>
#include <string>
#include <memory>
#include "types.hpp"

class Expr {
public:
	virtual ~Expr() { }

	// Compile Time Evaluation
	virtual bool cte(i32_t*) const {
		return false;
	}

	// Compile Time Evaluation
	virtual bool cte(std::string*) const {
		return false;
	}

	// Normal Evaluation
	virtual void eval(std::ostream&) const = 0;
};

class NumExpr : public Expr {
private:
	i32_t _value;

public:
	explicit NumExpr(i32_t val);

	// Compile Time Evaluation
	virtual bool cte(i32_t* num) const override {
		*num = _value;
		return true;
	}

	virtual void eval(std::ostream&) const override;
};

class StringExpr : public Expr {
private:
	std::string _label;

public:
	explicit StringExpr(const std::string&);

	// Compile Time Evaluation
	virtual bool cte(std::string* str) const override {
		*str = _label;
		return true;
	}

	virtual void eval(std::ostream&) const override;
};

class Var;

class VarExpr : public Expr {
protected:
	const Var* _var;

public:
	explicit VarExpr(const Var*);

	virtual void eval(std::ostream&) const override;
};

class PtrExpr : public VarExpr {
	explicit PtrExpr(const Var*);

	virtual void eval(std::ostream&) const override;
};

class DerefExpr : public VarExpr {
	explicit DerefExpr(const Var*);

	virtual void eval(std::ostream&) const override;
};

struct BinaryExpr : public Expr {
	std::unique_ptr<const Expr> lhs;
	std::unique_ptr<const Expr> rhs;

	explicit BinaryExpr(const Expr*, const Expr*);

	virtual ~BinaryExpr() { }
};

struct AddOp : public BinaryExpr {
	explicit AddOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct SubOp : public BinaryExpr {
	explicit SubOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct MulOp : public BinaryExpr {
	explicit MulOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct DivOp : public BinaryExpr {
	explicit DivOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct ModOp : public DivOp {
	explicit ModOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

#endif