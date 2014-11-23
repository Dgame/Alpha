#ifndef ALPHA_EXPR_HPP
#define ALPHA_EXPR_HPP

#include <ostream>
#include <string>
#include <memory>
#include "types.hpp"

struct Expr {
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

class VarDecl;

class VarExpr : public Expr {
protected:
	const VarDecl* _var;

public:
	explicit VarExpr(const VarDecl*);

	virtual void eval(std::ostream&) const override;
};

struct PtrExpr : public VarExpr {
	explicit PtrExpr(const VarDecl*);

	virtual void eval(std::ostream&) const override;
};

struct DerefExpr : public VarExpr {
	explicit DerefExpr(const VarDecl*);

	virtual void eval(std::ostream&) const override;
};

struct BinaryExpr : public Expr {
	std::unique_ptr<const Expr> lhs;
	std::unique_ptr<const Expr> rhs;

	explicit BinaryExpr(const Expr*, const Expr*);

	virtual ~BinaryExpr() { }
};

struct AddExpr : public BinaryExpr {
	explicit AddExpr(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct SubExpr : public BinaryExpr {
	explicit SubExpr(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct MulExpr : public BinaryExpr {
	explicit MulExpr(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct DivExpr : public BinaryExpr {
	explicit DivExpr(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

struct ModExpr : public DivExpr {
	explicit ModExpr(const Expr*, const Expr*);

	virtual void eval(std::ostream&) const override;
};

#endif