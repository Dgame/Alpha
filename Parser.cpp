#include "Parser.hpp"

#include <fstream>
#include <locale>

#include "Operation.hpp"
#include "Var.hpp"

Parser::Parser(const std::string& file) : _line(0), _filename(file) {
	std::ifstream in(_filename);

	std::copy(
		std::istreambuf_iterator<char>(in.rdbuf()),
		std::istreambuf_iterator<char>(),
		std::inserter(_content, _content.begin()));

	_pos = &*_content.begin();
	_end = &*_content.end() + 1;
}

void Parser::skipSpaces() {
	while (!eof() && std::isspace(*_pos)) {
		if (*_pos == '\n')
			_line++;
		++_pos;

		skipComment();
	}
}

void Parser::skipComment() {
	if (!eof() && *_pos == '#') {
		do {
			_pos++;
		} while (!eof() && *_pos != '\n');
	}
}

bool Parser::readNumber(i32_t* num) {
	skipSpaces();
	push();

	if (!eof() && std::isdigit(*_pos)) {
		*num = 0;
		do {
			*num *= 10;
			*num += *_pos - '0';

			++_pos;
		} while (!eof() && std::isdigit(*_pos));

		return true;
	}

	return false;
}

bool Parser::readIdentifier(std::string* ident) {
	skipSpaces();
	push();

	if (!eof() && (std::isalpha(*_pos) || *_pos == '_')) {
		*ident += *_pos;
		_pos++;

		while (!eof() && (std::isalnum(*_pos) || *_pos == '_')) {
			*ident += *_pos;
			_pos++;
		}

		return true;
	}

	return false;
}

bool Parser::accept(const std::string& tok) {
	skipSpaces();
	push();

	for (u32_t i = 0; i < tok.size(); i++) {
		if (tok[i] != *_pos) {
			pop();
			return false;
		}

		_pos++;
	}

	return true;
}

bool Parser::expect(const std::string& tok) {
	skipSpaces();
	push();

	std::string ident;
	for (u32_t i = 0; i < tok.size(); i++) {
		ident += *_pos;

		if (tok[i] != *_pos) {
			pop();
			error("Did expected '" + tok + "', not '" + ident + "'");

			return false;
		}

		_pos++;
	}

	return true;
}

void Parser::parse() {
	while (!eof() && !_error) {
		const char* const cur_pos = _pos;
		if (!parseFunc())
			error("Did expect a function");
		if (cur_pos == _pos)
			error("Could not parse anything");
	}
}

bool Parser::parseFunc() {
	std::string name;
	if (readIdentifier(&name)) {
		expect(":");
		// TODO: Return type
		parseParam();

		Scope* my_scope = nullptr;
		parseScope(&my_scope);

		functions.emplace_back(new Function(name, my_scope));

		return true;
	}

	return false;
}

void Parser::parseParam() {
	expect("(");

	// TODO: parse parameter

	expect(")");
}

void Parser::parseScope(Scope** scope) {
	expect("{");

	*scope = new Scope();

	while (!eof() && !_error) {
		const u32_t stmt_count = (*scope)->statements.size();

		parseStmt(*scope);
		parseVar(*scope);

		// No new elements?
		if (stmt_count == (*scope)->statements.size())
			break;
	}

	expect("}");
}

void Parser::parseStmt(Scope* scope) {
	if (accept("print")) {
		const Expr* exp = parseExpr(scope);
		if (exp) {
			scope->addStmt(new PrintStmt(exp));
			return;
		}

		std::string ident;
		if (readIdentifier(&ident)) {
			const Var* var = scope->getVar(ident);
			if (var) {
				scope->addStmt(new PrintStmt(var));
				return;
			}

			pop();
		}

		error("Nothing to print");
	}
}

void Parser::parseIf(Scope*) {

}

void Parser::parseElse(Scope*) {

}

void Parser::parseLoop(Scope*) {

}

void Parser::parseArray(Scope*) {

}

const Var* Parser::readVar(Scope* scope) {
	std::string ident;
	if (readIdentifier(&ident))
		return scope->getVar(ident);
	return nullptr;
}

void Parser::parseVar(Scope* scope) {
	std::string name;
	if (readIdentifier(&name)) {
		// since the 'accept's below will override '_old_pos', store it...
		char* my_old_pos = _old_pos;

		if (accept("=")) {
			// By Value
			parseVarVal(name, scope);
		} else if (accept("->")) {
			// Reference
			parseVarEnRef(name, scope);
		} else if (accept("<-")) {
			// Dereference
			parseVarDeRef(name, scope);
		} else {
			// ...and reset it correctly.
			_pos = my_old_pos;
		}
	}
}

void Parser::parseVarVal(std::string& name, Scope* scope) {
	// By Value
	const Var* var = readVar(scope);
	if (var)
		scope->makeVar(name, var, RefType::ByVal);
	else {
		pop();
		const Expr* exp = parseExpr(scope);
		if (!exp) {
			error("No assignment found for variable " + name);

			return;
		}
		scope->makeVar(name, exp);
	}
}

void Parser::parseVarEnRef(std::string& name, Scope* scope) {

}

void Parser::parseVarDeRef(std::string& name, Scope* scope) {

}


Expr* Parser::parseExpr(Scope* scope) {
    Expr* lhs = parseTerm(scope);
    if (lhs) {
        while (true) {
            if (accept("+")) {
                Expr* rhs = parseTerm(scope);
                if (!rhs) {
                    error("Expected factor after +");

					delete lhs;
					delete rhs;

                    return nullptr;
                }

                lhs = new AddOp(lhs, rhs);
            } else if (accept("-")) {
                Expr* rhs = parseTerm(scope);
                if (!rhs) {
                    error("Expected factor after -");

					delete lhs;
					delete rhs;

                    return nullptr;
                }

                lhs = new SubOp(lhs, rhs);
            } else
                break;
        }
    }

    return lhs;
}

Expr* Parser::parseTerm(Scope* scope) {
    Expr* lhs = parseFactor(scope);
    if (lhs) {
        while (true) {
            if (accept("*")) {
                Expr* rhs = parseFactor(scope);
                if (!rhs) {
                    error("Expected factor after *");

					delete lhs;
					delete rhs;

                    return nullptr;
                }

                lhs = new MulOp(lhs, rhs);
            } else if (accept("/")) {
                Expr* rhs = parseFactor(scope);
                if (!rhs) {
                    error("Expected factor after /");

					delete lhs;
					delete rhs;

                    return nullptr;
                }

                lhs = new DivOp(lhs, rhs);
            } else 
                break;
        }
    }

    return lhs;
}

Expr* Parser::parseFactor(Scope* scope) {
    const bool negate = accept("-");
  
    i32_t num;
    if (readNumber(&num)) {
        if (negate)
            num *= -1;

        return new NumExpr(num);
    } else if (accept("(")) {
        Expr* exp = parseExpr(scope);
        expect(")");

        return exp;
    } else {
    	const Var* var = readVar(scope);
    	if (var)
    		return new VarExpr(var->offset);
    	pop();
    }

    return nullptr;
}