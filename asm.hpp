#ifndef ALPHA_ASM_HPP
#define ALPHA_ASM_HPP

#include <iostream>
#include "util.hpp"

#define BIT_SIZE 32

#if BIT_SIZE == 64
	const char SUFFIX = 'q';
#elif BIT_SIZE == 32
	const char SUFFIX = 'l';
#elif BIT_SIZE == 16
	const char SUFFIX = 'w';
#elif BIT_SIZE == 8
	const char SUFFIX = 'b';
#else
	const char SUFFIX = 0;
#endif

enum Ptr {
#if BIT_SIZE == 32
	E_SP,
	E_BP,
#elif BIT_SIZE == 64
	R_SP,
	R_BP,
#endif
	P_STACK = 0,
	P_BASE = 1
};

enum Reg {
	E_AX,
	E_BX,
	E_CX,
	E_DX,
#if BIT_SIZE == 64
	R_AX,
	R_BX,
	R_CX,
	R_DX
#endif
};

enum Idx {
	E_SI,
	E_DI,
#if BIT_SIZE == 64
	R_SI,
	R_DI
#endif
};

enum JCond {
	J_Immediate,
	J_IfZero,
	J_IfEqual,
	J_IfNotEqual,
	J_IfGreater,
	J_IfGraterEqual,
	J_IfLess,
	J_IfLessEqual,
	J_IfAbove,
	J_IfBelow
};

namespace gas {
	const std::string Pointer[] = {
#if BIT_SIZE == 32
		// 32 Bit
		"%esp",
		"%ebp",
#elif BIT_SIZE == 64
		// 64 Bit
		"%rsp",
		"%rbp"
#endif
	};

	const std::string Register[] = {
		// 32 Bit
		"%eax",
		"%ebx",
		"%ecx",
		"%edx",
#if BIT_SIZE == 64
		// 64 Bit
		"%rax",
		"%rbx",
		"%rcx",
		"%rdx"
#endif
	};

	const std::string Index[] = {
		// 32 Bit
		"%esi",
		"%edi",
#if BIT_SIZE == 64
		// 64 Bit
		"%rsi",
		"%rdi"
#endif
	};

	const std::string JumpPostFix[] = {
		"mp",
		"z",
		"e",
		"ne",
		"g",
		"ge",
		"l",
		"le",
		"a",
		"b",
	};

	struct Offset {
		std::string id;

		explicit Offset(int offset, Ptr ptr);
		explicit Offset(int offset, Reg reg);
	};

	// push
	void push(std::ostream&, int num);
	void push(std::ostream&, Reg r);
	void push(std::ostream&, Offset o);
	void push(std::ostream&, Ptr p);
	void push(std::ostream&, const std::string&);

	// pop
	void pop(std::ostream&, Reg r);
	void pop(std::ostream&, Offset o);
	void pop(std::ostream&, Ptr p);

	// inc
	void inc(std::ostream&, Reg r);
	void inc(std::ostream&, Offset o);

	// dec
	void dec(std::ostream&, Reg r);
	void dec(std::ostream&, Offset o);

	// mov
	void mov(std::ostream&, int num, Reg r);
	void mov(std::ostream&, int num, Offset o);
	void mov(std::ostream&, Reg r1, Reg r2);
	void mov(std::ostream&, Reg r, Offset o);
	void mov(std::ostream&, Offset o, Reg r);
	void mov(std::ostream&, Ptr p1, Ptr p2);

	// add
	void add(std::ostream&, int num, Ptr p);
	void add(std::ostream&, int num, Reg r);
	void add(std::ostream&, int num, Offset o);
	void add(std::ostream&, Reg r1, Reg r2);
	void add(std::ostream&, Reg r, Offset o);
	void add(std::ostream&, Offset o, Reg r);

	// sub
	void sub(std::ostream&, int num, Ptr p);
	void sub(std::ostream&, int num, Reg r);
	void sub(std::ostream&, int num, Offset o);
	void sub(std::ostream&, Reg r1, Reg r2);
	void sub(std::ostream&, Reg r, Offset o);
	void sub(std::ostream&, Offset o, Reg r);

	// imul
	void imul(std::ostream&, Reg r1, Reg r2);
	void imul(std::ostream&, Offset o, Reg r);

	// idiv
	void idiv(std::ostream&, Reg r);
	void idiv(std::ostream&, Offset o);

	// lea
	void lea(std::ostream&, Offset o, Reg r);

	// ret
	void ret(std::ostream&);

	// call
	void call(std::ostream&, const std::string&);

	// jmp
	void jmp(std::ostream&, JCond jc, const std::string&);

	// cmp
	void cmp(std::ostream&, int num, Reg r);
	void cmp(std::ostream&, int num, Offset o);
	void cmp(std::ostream&, Reg r1, Reg r2);
	void cmp(std::ostream&, Offset o, Reg r);
	void cmp(std::ostream&, Reg r, Offset o);

	// neg
	void neg(std::ostream&, Reg r);
	void neg(std::ostream&, Offset o);

	// not
	void bit_not(std::ostream&, Reg r);
	void bit_not(std::ostream&, Offset o);

	// and
	void bit_and(std::ostream&, Reg r1, Reg r2);
	void bit_and(std::ostream&, Reg r, Offset o);
	void bit_and(std::ostream&, Offset o, Reg r);

	// or
	void bit_or(std::ostream&, Reg r1, Reg r2);
	void bit_or(std::ostream&, Reg r, Offset o);
	void bit_or(std::ostream&, Offset o, Reg r);

	// xor
	void bit_xor(std::ostream&, Reg r1, Reg r2);
	void bit_xor(std::ostream&, Reg r, Offset o);
	void bit_xor(std::ostream&, Offset o, Reg r);
}

#endif