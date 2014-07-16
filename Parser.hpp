#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <iostream>
#include <string>
#include <map>
#include "Expression.hpp"
#include "Commands.hpp"
#include "Manager.hpp"
#include "patch.hpp"
#include "Env.hpp"

enum class Tok {
	Print,
	Var,
	Exit,
	If,
	Else,
	For,

	True,
	False,

	Equal,
	NotEqual,

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
	{Tok::For, "for"},

	{Tok::True, "true"},
	{Tok::False, "false"},

	{Tok::Equal, "=="},
	{Tok::NotEqual, "!="},

	{Tok::And, "and"},
	{Tok::Or, "or"},
	{Tok::Xor, "xor"},
	{Tok::Not, "not"},
};

struct Loc {
	const std::string& filename;
	const char* pos = nullptr;
	const char* const end = nullptr;
	unsigned int lineNr = 1;

	explicit Loc(const std::string& file, const char* start, const char* theEnd);

	bool eof() const {
		return this->pos >= (this->end - 1);
	}

	void error(const std::string& msg) const {
		std::cerr << "Error: " << msg << " at line " << this->lineNr << " in " << this->filename << std::endl;
	}
};

void checkInPlace(Expression*, const std::string&);

struct Parser {
	Env& env;
	Loc& loc;

	explicit Parser(Env&, Loc&);

	bool skipComment();
	void skipSpaces();

	bool read(const std::string&);
	bool read(Tok tok);
	bool read(char ch);

	bool peek(char what);

	bool readNumber(unsigned int*);
	bool readIdentifier(std::string*);

	bool parse();

	bool parsePrint();
	bool parseVar();
	bool parseVarAssign();
	bool parseExit();
	bool parseIf();
};

class AssignParser {
private:
	Parser& _p;

public:
	explicit AssignParser(Parser*);

	bool parse(Expression**);
};

class TermParser {
private:
	std::unique_ptr<Term> _term;
	Parser& _p;

public:
	explicit TermParser(Parser*);

	bool parse(Expression**);

private:
	bool _parseNumExp();
	bool _parseTerm();
	bool _parseFactor();
	bool _parseLiteral();
};

class BooleanParser {
private:
	std::unique_ptr<Condition> _cond;
	Parser& _p;

public:
	explicit BooleanParser(Parser*);

	bool parse(Condition**);

private:
	bool _parseLinkage(Link*) const;
	Compare* _parseCompare() const;
};

class ScopeParser {
private:
	Parser& _p;

public:
	explicit ScopeParser(Parser*);
	bool parseScope(Scope**);
};

class ArrayParser {
private:
	Parser& _p;

public:
	explicit ArrayParser(Parser*);

	bool parseArray(Array**);
};

#endif