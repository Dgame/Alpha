#ifndef ALPHA_PARSER_HPP
#define ALPHA_PARSER_HPP

#include <fstream>
#include "Func.hpp"
#include "DataSection.hpp"
#include "Cond.hpp"

struct ElseStmt;

struct Parser {
	char* _pos;
	const char* _end;

	u32_t _line;

	bool _error = false;

	std::string _filename;
	std::vector<char> _content;
	char* _old_pos;

	Scope* _cur_scope = nullptr;

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

	void parseStmt();
	void parsePrintStmt();
	void parseIfStmt();

	ElseStmt* parseElseStmt(const std::string&);

	void parseLoopStmt();

	Compare* parseCondExpr(const std::string&, const std::string&);
	Compare* parseCompExpr();

	void parseArray();

	const Var* readVar();
	const Var* getVar(std::string&);

	void parseVar();
	void parseVarVal(std::string&);
	void parseVarEnRef(std::string&);
	void parseVarDeRef(std::string&);

	void parseVarInc(std::string&);
	void parseVarDec(std::string&);

	Expr* parseExpr();
	Expr* parseTerm();
	Expr* parseFactor();
};

#endif