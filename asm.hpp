#ifndef ALPHA_ASM_HPP
#define ALPHA_ASM_HPP

#include <iostream>
#include <string>
#include <sstream>

#include "types.hpp"

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

std::string Offset(u32_t offset, const std::string& ident);

namespace gas {
	namespace Register {
		// 32 Bit
		const std::string E_AX("%eax");
		const std::string E_BX("%ebx");
		const std::string E_CX("%ecx");
		const std::string E_DX("%edx");
#if BIT_SIZE == 64
		// 64 Bit
		const std::string R_AX("%rax");
		const std::string R_BX("%rbx");
		const std::string R_CX("%rcx");
		const std::string R_DX("%rdx");
		// Default
		const std::string AX = R_AX;
		const std::string BX = R_BX;
		const std::string CX = R_CX;
		const std::string DX = R_DX;
#elif BIT_SIZE == 32
		const std::string AX = E_AX;
		const std::string BX = E_BX;
		const std::string CX = E_CX;
		const std::string DX = E_DX;
#endif
	}

	namespace Pointer {
#if BIT_SIZE == 64
		const std::string Base("%rbp");
		const std::string Stack("%rsp");
#elif BIT_SIZE == 32
		const std::string Base("%ebp");
		const std::string Stack("%esp");
#endif
	}

	void mov(std::ostream& out, int num, const std::string& op);
	void mov(std::ostream& out, const std::string& op1, const std::string& op2);

	void add(std::ostream& out, int num, const std::string& op);
	void add(std::ostream& out, const std::string& op1, const std::string& op2);

	void sub(std::ostream& out, int num, const std::string& op);
	void sub(std::ostream& out, const std::string& op1, const std::string& op2);

	void mul(std::ostream& out, const std::string& op1, const std::string& op2);

	void div(std::ostream& out, const std::string& op1, const std::string& op2);

	void push(std::ostream& out, const std::string& op);
	void push(std::ostream& out, int num);

	void pop(std::ostream& out, const std::string& op);
	void pop(std::ostream& out, int num);

	void inc(std::ostream& out, const std::string& op);

	void dec(std::ostream& out, const std::string& op);

	void lea(std::ostream& out, const std::string& op1, const std::string& op2);

	void ret(std::ostream& out);

	void call(std::ostream& out, const std::string& label);
}

#endif