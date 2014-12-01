#ifndef ALPHA_VAR_DECL_HPP
#define ALPHA_VAR_DECL_HPP

#include <memory>
#include "Decl.hpp"
#include "types.hpp"

#include "Expr.hpp"

enum class BitSize : u16_t {
	B_8 = 8,
	B_16 = 16,
	B_32 = 32,
	B_64 = 64,
	B_128 = 128
};

class VarDecl : public Decl {
private:
	const u16_t _bit_size;

	u32_t _stack_offset;
	i32_t _base_offset;

	bool _mut;

	std::unique_ptr<const Expr> _expr;

public:
	explicit VarDecl(const Expr*, bool mut = true, BitSize size = BitSize::B_32);
	virtual ~VarDecl() { }

	bool isMutable() const {
		return _mut;
	}

	u16_t sizeInBit() const {
		return _bit_size;
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