#include "Parser.hpp"

Loc::Loc(const std::string& file, const char* start, const char* theEnd) : filename(file), pos(start), end(theEnd) {
	
}

void checkInPlace(Expression* exp, const std::string& identifier) {
	if (exp->isTerm()) {
		Term* term = dynamic_cast<Term*>(exp);

		if (term->count() == 3) {
			if (const Var* lvar = term->at(0)->isVar()) {
				if (const Operator* op = term->at(2)->isOperator()) {
					if (lvar->variable->name == identifier && op->isAssociative()) {
						term->inPlace = true;
					}
				}
			}
		}
	}
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

	while (this->skipComment()) {
		// Wait...
	}

	if (!loc.eof() && std::isspace(*loc.pos)) {
		return this->skipSpaces();
	}
}

bool Parser::read(const std::string& what) {
	this->skipSpaces();

	const char* prevPos = loc.pos;

	for (char c : what) {
		if (!loc.eof() && *loc.pos == c)
			++loc.pos;
		else {
			loc.pos = prevPos;

			return false;
		}
	}

	if (!loc.eof() && !std::isspace(*loc.pos)) {
		loc.error("Unknown command.");

		return false;
	}

	return true;
}

bool Parser::read(char what) {
	this->skipSpaces();

	if (!loc.eof() && *loc.pos == what) {
		++loc.pos;

		return true;
	}

	return false;
}

bool Parser::read(Tok tok) {
	return this->read(TokStr.at(tok));
}

bool Parser::peek(char what) {
	this->skipSpaces();

	return *loc.pos == what;
}

bool Parser::readNumber(unsigned int* n) {
	this->skipSpaces();

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
	this->skipSpaces();

	if (!loc.eof() && (std::isalpha(*loc.pos) || *loc.pos == '_')) {
		*identifier += *loc.pos;
		loc.pos++;

		while (!loc.eof() && (std::isalnum(*loc.pos) || *loc.pos == '_')) {
			*identifier += *loc.pos;
			loc.pos++;
		}

		return true;
	}

	return false;
}

bool Parser::parse() {
	if (this->parseExit())
		return false;
	if (this->parsePrint())
		return true;
	if (this->parseIf())
		return true;
	if (this->parseVar())
		return true;
	if (this->parseVarAssign())
		return true;

	if (!loc.eof()
		&& !std::isspace(*loc.pos)
		&& *loc.pos != '}')
	{
		loc.error("Unexpected chars");
	}

	return false;
}

bool Parser::parsePrint() {
	if (this->read(Tok::Print)) {
		Expression* exp = nullptr;

		TermParser tp(this);
		if (tp.parse(&exp)) {
			env.cm->push(new Print(exp));
		} else {
	 		loc.error("No expression to print.");

	 		return false;
	 	}

		return true;
	}

	return false;
}

bool Parser::parseVar() {
	if (this->read(Tok::Var)) {
		std::string identifier;
		if (this->readIdentifier(&identifier)) {
			unsigned int size = 1;

			if (this->read('[')) {
				if (!this->readNumber(&size))
					size = 0;

				if (!this->read(']')) {
					loc.error("Expected ']'");

					return false;
				}
			}

			if (size > 16384) {
				loc.error("Stack overflow");

				return false;
			}

			Expression* exp = nullptr;

			AssignParser ap(this);
			if (!ap.parse(&exp)) {
				if (size > 1) 
					exp = new Empty();
				else {
					loc.error("Cannot assign empty expression");

					return false;
				}
			}

			if (const Array* array = exp->isArray()) {
				if (size == 0)
					size = array->count();
				else if (array->count() != size) {
					loc.error("Incomaptible array size");
					std::cerr << size << " <-> " << array->count() << std::endl;

					return false;
				}
			}

			if (size == 0) {
				loc.error("Expected array assign to determine array size");

				return false;
			}

			env.vm->createVar(identifier, exp, size * 4);

			if (size == 1)
				checkInPlace(exp, identifier);

			return true;
		} else
			loc.error("Expected identifier after 'var'");
	}

	return false;
}

bool Parser::parseVarAssign() {
	std::string identifier;
	if (this->readIdentifier(&identifier)) {
		unsigned int index = 0;
		bool hasIndex = false;

		if (this->read('[')) {
			hasIndex = true;

			if (!this->readNumber(&index)) {
				loc.error("Expected index for array access");

				return false;
			}

			if (!this->read(']')) {
				loc.error("Expected ']'");

				return false;
			}
		}

		Expression* exp = nullptr;

		AssignParser ap(this);
		if (!ap.parse(&exp)) {
			loc.error("Cannot assign empty expression.");

			return false;
		}

		if (hasIndex) {
			if (!env.vm->assignVarAt(index, identifier, exp)) {
				loc.error("Error by array access assign");

				return false;
			}
		} else if (!env.vm->assignVar(identifier, exp)) {
			loc.error("Error by variable assign");

			return false;
		}

		if (!hasIndex)
			checkInPlace(exp, identifier);

		return true;
	}

	return false;
}

bool Parser::parseExit() {
	return this->read(Tok::Exit);
}

bool Parser::parseIf() {
	if (this->read(Tok::If)) {
		Condition* cond = nullptr;
		Scope* isp = nullptr;
		Scope* esp = nullptr;

		BooleanParser bp(this);
		if (bp.parse(&cond)) {
			ScopeParser sp(this);

			if (sp.parseScope(&isp)) {
				if (this->read(Tok::Else)) {
					if (!sp.parseScope(&esp)) {
						loc.error("Expected Scope for 'else'");

						return false;
					}
				}

				env.cm->push(new If(cond, isp, esp));
			} else {
				loc.error("Expected Scope for 'if'");

				return false;
			}
		} else {
			loc.error("Expected boolean expression for if");

			return false;
		}

		return true;
	}

	return false;
}

AssignParser::AssignParser(Parser* p) : _p(*p) {

}

bool AssignParser::parse(Expression** exp) {
	if (_p.peek('=')) {
		_p.loc.pos++;

		if (_p.peek('[')) {
			Array* array = nullptr;

			ArrayParser ap(&_p);
			if (!ap.parseArray(&array)) {
				_p.loc.error("Expected array expression");

				return false;
			}

			*exp = array;
		} else {
			TermParser tp(&_p);
			if (!tp.parse(exp)) {
				_p.loc.error("Invalid expression for variable assign");

				return false;
			}
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
	unsigned int num;
	if (_p.readNumber(&num)) {
		_term->push(num);

		return true;
	}

	std::string identifier;
	if (_p.readIdentifier(&identifier)) {
		const Variable* var = _p.env.vm->getVar(identifier);
		
		unsigned int index = 0;
		if (_p.read('[')) {
			if (!_p.readNumber(&index)) {
				_p.loc.error("Expected array index");

				return false;
			}

			if (!_p.read(']')) {
				_p.loc.error("Expected ']'");

				return false;
			}
		}

		if (var == nullptr) {
			_p.loc.error("Unknown variable '" + identifier + "'");

			return false;
		} else {
			_term->push(var, index * 4);
		}

		return true;
	}

	return false;
}

BooleanParser::BooleanParser(Parser* p) : _p(*p) {
	_cond = patch::make_unique<Condition>();
}

bool BooleanParser::parse(Condition** cond) {
	Compare* cmp = _parseCompare();

	if (!cmp)
		return false;

	_cond->setPrimary(cmp);

	Link link;
	while (_parseLinkage(&link)) {
		cmp = _parseCompare();
		_cond->push(link, cmp);
	}

	*cond = _cond.release();

	return true;
}

bool BooleanParser::_parseLinkage(Link* link) const {
	if (_p.read(Tok::And))
		*link = Link::And;
	else if (_p.read(Tok::Or))
		*link = Link::Or;
	else if (_p.read(Tok::Xor))
		*link = Link::Xor;
	else
		return false;

	return true;
}

Compare* BooleanParser::_parseCompare() const {
	Expression* lhs = nullptr;
	Expression* rhs = nullptr;

	TermParser tpl(&_p);
	if (tpl.parse(&lhs)) {
		Cmp cmp;
		if (_p.read(Tok::Equal))
			cmp = Cmp::Equal;
		else if (_p.read(Tok::NotEqual))
			cmp = Cmp::NotEqual;
		else if (_p.read('>')) {
			if (_p.read('='))
				cmp = Cmp::GreaterEqual;
			else
				cmp = Cmp::Greater;
		} else if (_p.read('<')) {
			if (_p.read('='))
				cmp = Cmp::LessEqual;
			else
				cmp = Cmp::Less;
		} else {
			_p.loc.error("Unexpected compare operation in if");

			return nullptr;
		}

		TermParser tpr(&_p);
		if (tpr.parse(&rhs)) {
			return new Compare(lhs, rhs, cmp);
		}

		_p.loc.error("Expected right hand side expression for if");

		return nullptr;
	}

	_p.loc.error("Expected left hand side expression for if");

	return nullptr;
}

ScopeParser::ScopeParser(Parser* p) : _p(*p) {

}

bool ScopeParser::parseScope(Scope** scope) {
	if (_p.read('{')) {
		_p.env.sm->pushScope();

		while (_p.parse()) {
			// Wait...
		}

		if (_p.read('}'))
			*scope = _p.env.sm->popScope().release();
		else {
			_p.loc.error("Missing '}'.");

			return false;
		}

		return true;
	}

	return false;
}

ArrayParser::ArrayParser(Parser* p) : _p(*p) {

}

bool ArrayParser::parseArray(Array** arr) {
	if (!_p.read('[')) {
		_p.loc.error("Expected '[' for array start");

		return false;
	}

	std::unique_ptr<Array> array = patch::make_unique<Array>();

	Expression* exp = nullptr;
	while (!_p.loc.eof()) {
		TermParser tp(&_p);
		if (!tp.parse(&exp)) {
			_p.loc.error("Invalid expression for array");

			return false;
		}

		array->push(exp);
		exp = nullptr;

		if (!_p.read(','))
			break;
	}

	if (!_p.read(']')) {
		_p.loc.error("Expected ']' for array end");

		return false;
	}

	*arr = array.release();

	return true;
}