#include "Parser.hpp"

Loc::Loc(const char* start, const char* theEnd) : pos(start), end(theEnd) {
	
}

Parser::Parser(Env& myenv, Loc& myloc) : env(myenv), loc(myloc) {

}

bool Parser::skipComment() {
	if (!loc.eof() && *loc.pos == '#') {
		do {
			loc.pos++;
		} while (!loc.eof() && *loc.pos != '\n');

		return true;
	}

	return false;
}

void Parser::skipSpaces() {
	while (!loc.eof() && std::isspace(*loc.pos)) {
		if (*loc.pos == '\n')
			loc.lineNr++;
		++loc.pos;
	}

	while (skipComment()) {

	}

	if (!loc.eof() && std::isspace(*loc.pos))
		return skipSpaces();
}

bool Parser::read(const std::string& what) {
	skipSpaces();

	for (char c : what) {
		if (!loc.eof() && *loc.pos == c)
			++loc.pos;
		else
			return false;
	}

	if (!loc.eof() && !std::isspace(*loc.pos)) {
		loc.error("Unknown command.");

		return false;
	}

	return true;
}

bool Parser::read(char what) {
	skipSpaces();

	if (!loc.eof() && *loc.pos == what) {
		++loc.pos;

		return true;
	}

	return false;
}

bool Parser::read(Tok tok) {
	return read(TokStr.at(tok));
}

bool Parser::peek(char what) {
	skipSpaces();

	return *loc.pos == what;
}

void Parser::expect(char what) {
	if (!read(what))
		loc.error("Expected " + what);
}

void Parser::expect(Tok tok) {
	if (!read(tok))
		loc.error("Expected " + TokStr.at(tok));
}

void Parser::next() {
	loc.pos++;
}

bool Parser::readNumber(int* n) {
	skipSpaces();

	if (!loc.eof() && std::isdigit(*loc.pos)) {
		*n = 0;
		do {
			*n *= 10;
			*n += *loc.pos - '0';

			++loc.pos;
		} while (!loc.eof() && std::isdigit(*loc.pos));

		return true;
	}

	return false;
}

bool Parser::readIdentifier(std::string* identifier) {
	skipSpaces();

	if (!loc.eof() && (std::isalpha(*loc.pos) || *loc.pos == '_')) {
		identifier->clear();

		do {
			*identifier += *loc.pos;

			++loc.pos;
		} while (!loc.eof() && (std::isalnum(*loc.pos) || *loc.pos == '_'));

		return true;
	}

	return false;
}

bool Parser::parse() {
	return parsePrint() || parseVar() || parseVarAssign();
}

bool Parser::parsePrint() {
	if (read(Tok::Print)) {
		Expression* exp = nullptr;

		TermParser tp(this);
		if (tp.parse(&exp)) {
			env.cm->push(new Print(exp));
		}

		return true;
	}

	return false;
}

bool Parser::parseVar() {
	if (read(Tok::Var)) {
		std::string identifier;
		if (readIdentifier(&identifier)) {
			Expression* exp = nullptr;

			if (peek('=')) {
				next();

				TermParser tp(this);
				if (!tp.parse(&exp)) {
					loc.error("Invalid expression for variable assign");

					return false;
				}
			}

			env.vm->createVar(identifier, exp);

			return true;
		} else
			loc.error("Expected identifier after 'var'");
	}

	return false;
}

bool Parser::parseVarAssign() {
	std::string identifier;
	if (readIdentifier(&identifier)) {
		expect('=');

		Expression* exp = nullptr;

		TermParser tp(this);
		if (!tp.parse(&exp)) {
			loc.error("Invalid expression for variable assignment");

			return false;
		}

		if (!env.vm->assignVar(identifier, exp)) {
			loc.error("Invalid expression or unknown variable");

			return false;
		}

		return true;
	}

	return false;
}

TermParser::TermParser(Parser* p) : _p(*p) {
	_term = patch::make_unique<Term>();
}

bool TermParser::parse(Expression** exp) {
	if (_parseNumExp()) {
		*exp = _term.release();

		return true;
	}

	return false;
}

bool TermParser::_parseNumExp() {
	if (_parseTerm()) {
		while (true) {
			if (_p.read('+')) {
				if (!_parseTerm()) {
					_p.loc.error("Expected Term after +");

					return false;
				}

				_term->push(Op::Plus);
			} else if (_p.read('-')) {
				if (!_parseTerm()) {
					_p.loc.error("Expected Term after -");

					return false;
				}

				_term->push(Op::Minus);
			} else
				break;
		}

		return true;
	}

	return false;
}

bool TermParser::_parseTerm() {
	if (_parseFactor()) {
		while (true) {
			if (_p.read('*')) {
				if (!_parseFactor()) {
					_p.loc.error("Expected factor after *");

					return false;
				}

				_term->push(Op::Mul);
			} else if (_p.read('/')) {
				if (!_parseFactor()) {
					_p.loc.error("Expected factor after /");

					return false;
				}

				_term->push(Op::Div);
			} else if (_p.read('%')) {
				if (!_parseFactor()) {
					_p.loc.error("Expected factor after %");

					return false;
				}

				_term->push(Op::Mod);
			} else
				break;
		}

		return true;
	}

	return false;
}

bool TermParser::_parseFactor() {
	bool negate = false;
	if (_p.read('-')) {
		negate = true;
	}

	if (_parseLiteral()) {
		// nothing to do
	} else if (_p.read('(')) {
		if (!_parseNumExp()) {
			_p.loc.error("Expected expression after '('.");

			return false;
		} else if (!_p.read(')')) {
			_p.loc.error("Missing ')'.");

			return false;
		}
	} else
		return false;

	if (negate) {
		_term->push(Op::Negate);
	}

	return true;
}

bool TermParser::_parseLiteral() {
	int num;
	if (_p.readNumber(&num)) {
		_term->push(num);

		return true;
	}

	std::string identifier;
	if (_p.readIdentifier(&identifier)) {
		const Variable* var = _p.env.vm->getVar(identifier);

		if (var == nullptr)
			_p.loc.error("Unknown variable " + identifier);
		else
			_term->push(var);

		return true;
	}

	return false;
}