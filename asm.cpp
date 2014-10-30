#include "asm.hpp"

std::string Offset(u32_t offset, const std::string& ident) {
	std::stringstream buf;
	buf << offset;
	buf << '(';
	buf << ident;
	buf << ')';

	return buf.str();
}

namespace gas {
	void mov(std::ostream& out, int num, const std::string& op) {
		out << "\tmov" << SUFFIX << "\t$" << num << ", " << op << std::endl;
	}

	void mov(std::ostream& out, const std::string& op1, const std::string& op2) {
		out << "\tmov" << SUFFIX << "\t" << op1 << ", " << op2 << std::endl;
	}

	void add(std::ostream& out, int num, const std::string& op) {
		out << "\tadd" << SUFFIX << "\t$" << num << ", " << op << std::endl;
	}

	void add(std::ostream& out, const std::string& op1, const std::string& op2) {
		out << "\tadd" << SUFFIX << "\t" << op1 << ", " << op2 << std::endl;
	}

	void sub(std::ostream& out, int num, const std::string& op) {
		out << "\tsub" << SUFFIX << "\t$" << num << ", " << op << std::endl;
	}

	void sub(std::ostream& out, const std::string& op1, const std::string& op2) {
		out << "\tsub" << SUFFIX << "\t" << op1 << ", " << op2 << std::endl;
	}

	void mul(std::ostream& out, const std::string& op1, const std::string& op2) {
		out << "\timul" << SUFFIX << "\t" << op1 << ", " << op2 << std::endl;
	}

	void div(std::ostream& out, const std::string& op1, const std::string& op2) {
		out << "\tidiv" << SUFFIX << "\t" << op1 << ", " << op2 << std::endl;
	}

	void push(std::ostream& out, const std::string& op) {
		out << "\tpush" << SUFFIX << "\t" << op << std::endl;
	}

	void push(std::ostream& out, int num) {
		out << "\tpush" << SUFFIX << "\t$" << num << std::endl;
	}

	void pop(std::ostream& out, const std::string& op) {
		out << "\tpop" << SUFFIX << "\t" << op << std::endl;
	}

	void pop(std::ostream& out, int num) {
		out << "\tpop" << SUFFIX << "\t$" << num << std::endl;
	}

	void inc(std::ostream& out, const std::string& op) {
		out << "\tinc" << SUFFIX << "\t" << op << std::endl;
	}

	void dec(std::ostream& out, const std::string& op) {
		out << "\tdec" << SUFFIX << "\t" << op << std::endl;
	}

	void lea(std::ostream& out, const std::string& op1, const std::string& op2) {
		out << "\tlea" << SUFFIX << "\t" << op1 << ", " << op2 << std::endl;
	}

	void ret(std::ostream& out) {
		out << "\tret" << std::endl;
	}

	void call(std::ostream& out, const std::string& label) {
		out << "\tcall\t" << label << std::endl;
	}
}