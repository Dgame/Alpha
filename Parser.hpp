#ifndef ALPHA_PARSER_HPP
#define ALPHA_PARSER_HPP

#include <fstream>
#include "Func.hpp"
#include "DataSection.hpp"

struct Parser {
	char* _pos;
	const char* _end;

	u32_t _line;

	bool _error = false;

	std::string _filename;
	std::vector<char> _content;
	char* _old_pos;

	std::vector<std::unique_ptr<Function>> functions;

	DataSection data_section;

	explicit Parser(const std::string&);

	const std::string addDataSection(const std::string&);
	void eval(std::ostream&) const;

	void push() {
		_old_pos = _pos;
	}

	void pop() {
		_pos = _old_pos;
	}

	bool hasErrors() const {
		return _error;
	}

	bool eof() const {
		return _pos >= (_end - 1);
	}

	void error(const std::string& msg) {
		_error = true;
		std::cerr << "Error: " << msg << " at line " << _line << " in " << _filename << std::endl;
	}

	void skipSpaces();
	void skipComment();

	bool readNumber(i32_t*);
	bool readIdentifier(std::string*);
	bool readString(std::string*);

	bool accept(const std::string&);
	bool expect(const std::string&);

	void parse();

	bool parseFunc();
	void parseParam();

	void parseScope(Scope**);

	void parseStmt(Scope*);
	void parsePrint(Scope*);
	void parseIf(Scope*);
	void parseElse(Scope*);
	void parseLoop(Scope*);

	void parseCompExpr();
	void parseBoolExpr();

	void parseArray(Scope*);

	const Var* readVar(Scope*);
	void parseVar(Scope*);
	void parseVarVal(std::string& name, Scope*);
	void parseVarEnRef(std::string& name, Scope*);
	void parseVarDeRef(std::string& name, Scope*);

	Expr* parseExpr(Scope*);
	Expr* parseTerm(Scope*);
	Expr* parseFactor(Scope*);
};

#endif