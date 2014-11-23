#ifndef ALPHA_VAR_HPP
#define ALPHA_VAR_HPP

#include <memory>
#include "Decl.hpp"
#include "types.hpp"

#include "Expr.hpp"

class VarDecl : public Decl {
private:
	const u32_t _byte_size;

	u32_t _stack_offset;
	i32_t _base_offset;

	bool _mut;

	std::unique_ptr<const Expr> _expr;

public:
	explicit VarDecl(const Expr*, bool mut = true, u32_t size = 4);
	virtual ~VarDecl() { }

	bool isMutable() const {
		return _mut;
	}

	u32_t sizeOf() const {
		return _byte_size;
	}

	void setStackOffset(u32_t offset) {
		_stack_offset = offset;
	}

	void setBaseOffset(u32_t offset) {
		_base_offset = offset;
	}

	u32_t getStackOffset() const {
		return _stack_offset;
	}

	u32_t getBaseOffset() const {
		return _base_offset;
	}

	virtual void eval(std::ostream&) const override;
};

#endif