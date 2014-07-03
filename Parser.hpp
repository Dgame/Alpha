#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <iostream>
#include <string>
#include <map>
#include "Expression.hpp"
#include "patch.hpp"
#include "Env.hpp"

enum class Tok {
	Print,
	Var,
	Exit,
	If,
	Else,
	While,

	True,
	False,

	Equal,
	NotEqual,
	LessOrEqual,
	Less,
	GreaterOrEqual,
	Greater,

	And,
	Or,
	Xor,
	Not,
};

const std::map<Tok, const std::string> TokStr = {
	{Tok::Print, "print"},
	{Tok::Var, "var"},
	{Tok::Exit, "exit"},
	{Tok::If, "if"},
	{Tok::Else, "else"},
	{Tok::While, "while"},

	{Tok::True, "true"},
	{Tok::False, "false"},

	{Tok::Equal, "=="},
	{Tok::NotEqual, "!="},
	{Tok::LessOrEqual, "<="},
	{Tok::Less, "<"},
	{Tok::GreaterOrEqual, ">="},
	{Tok::Greater, ">"},

	{Tok::And, "and"},
	{Tok::Or, "or"},
	{Tok::Xor, "xor"},
	{Tok::Not, "not"},
};

struct Loc {
	const char* pos = nullptr;
	const char* const end = nullptr;
	unsigned int lineNr = 1;

	explicit Loc(const char* start, const char* theEnd);

	bool eof() const {
		return this->pos == this->end;
	}

	void error(const std::string& msg) const {
		std::cerr << "Error: " << msg << " at line " << this->lineNr << std::endl;
	}
};

struct Parser {
	Env& env;
	Loc& loc;

	explicit Parser(Env& myenv, Loc& myloc);

	bool skipComment();
	void skipSpaces();

	bool read(const std::string& what);
	bool read(Tok tok);
	bool read(char ch);

	void expect(char what);
	void expect(Tok tok);
	void next();

	bool peek(char what);

	bool readNumber(int* num);
	bool readIdentifier(std::string* identifier);

	bool parse();

	bool parsePrint();
	bool parseVar();
	bool parseVarAssign();
};

class TermParser {
private:
	std::unique_ptr<Term> _term;
	Parser& _p;

public:
	explicit TermParser(Parser* p);

	bool parse(Expression** exp);

private:
	bool _parseNumExp();
	bool _parseTerm();
	bool _parseFactor();
	bool _parseLiteral();
};

#endif