#ifndef BACKEND_HPP
#define BACKEND_HPP

// #include <iostream>
#include <cassert>
#include "Assembler.hpp"
#include "Expression.hpp"

enum class RTLabel {
	Start,
	PrintI,
	PrintlnI,
	PrintS,
	PrintlnS
};

const std::map<RTLabel, const std::string> RTLabelStr = {
	{RTLabel::Start, "_prog"},
	{RTLabel::PrintI, "_print_int"},
	{RTLabel::PrintlnI, "_println_int"},
	{RTLabel::PrintS, "_print_string"},
	{RTLabel::PrintlnS, "_println_string"}
};

struct BackendVisitor {
	unsigned int stackSize = 0;

	explicit BackendVisitor(unsigned int stackSize);
	virtual ~BackendVisitor();

	void visit(const Scope* scope);

	void visit(const Operator*, const Variable*);

	void visit(const Command*);
	void visit(const Expression*);
	void visit(const Term*);
	void visit(const Variable*);
	void visit(const Array*);
	void visit(const Condition*);
};

#endif