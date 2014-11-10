#ifndef ALPHA_VAR_HPP
#define ALPHA_VAR_HPP

#include <ostream>
#include <memory>
#include "types.hpp"

struct Expr;

enum class Mode {
	Value,
	Reference,
	Dereference
};

class Var {
private:
	u32_t _offset;
	std::unique_ptr<const Expr> _expr;

	Mode _mode;
	bool _mut;

public:
	explicit Var(const Expr*, Mode mode = Mode::Value, bool mut = true);
	virtual ~Var() { }

	Mode getMode() const {
		return _mode;
	}

	bool isMutable() const {
		return _mut;
	}

	void setOffset(u32_t offset) {
		_offset = offset;
	}

	u32_t getOffset() const {
		return _offset;
	}

	const Expr* getExpr() const {
		return _expr.get();
	}

	virtual void eval(std::ostream&) const;
};

#endif