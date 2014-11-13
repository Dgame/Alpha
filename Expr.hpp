#ifndef ALPHA_EXPR_HPP
#define ALPHA_EXPR_HPP

#include <ostream>
#include <memory>
#include "types.hpp"

class Expr {
public:
	virtual ~Expr() { }

	// Has Compile Time Evaluation?
	virtual bool hasCTE() const {
		return false;
	}

	// Get Compile Time Evaluation
	virtual i32_t cte() const {
		return -1;
	}

	virtual void eval(std::ostream&) const = 0;
};

class NumExpr : public Expr {
private:
	i32_t _value;

public:
	explicit NumExpr(i32_t val);

	virtual bool hasCTE() const override {
		return true;
	}

	virtual i32_t cte() const override {
		return _value;
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

struct Operation : public Expr {
	std::unique_ptr<const Expr> lhs;
	std::unique_ptr<const Expr> rhs;

	explicit Operation(const Expr*, const Expr*);

	virtual ~Operation() { }
};

struct AddOp : public Operation {
	explicit AddOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct SubOp : public Operation {
	explicit SubOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct MulOp : public Operation {
	explicit MulOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct DivOp : public Operation {
	explicit DivOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct ModOp : public DivOp {
	explicit ModOp(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

#endif