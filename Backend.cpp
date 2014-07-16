#include "Backend.hpp"

as::Cond compareToCond(Cmp cmp) {
	if (cmp == Cmp::Equal)
		return as::Cond::Equal;
	else if (cmp == Cmp::NotEqual)
		return as::Cond::NotEqual;
	else if (cmp == Cmp::Greater)
		return as::Cond::Greater;
	else if (cmp == Cmp::Less)
		return as::Cond::Less;
	else if (cmp == Cmp::GreaterEqual)
		return as::Cond::GreaterEqual;
	else if (cmp == Cmp::LessEqual)
		return as::Cond::LessEqual;
	
	assert(0);
}

as::Cond negateCond(as::Cond cond) {
	if (cond == as::Cond::Equal)
		return as::Cond::NotEqual;
	else if (cond == as::Cond::NotEqual)
		return as::Cond::Equal;
	else if (cond == as::Cond::Greater)
		return as::Cond::NotGreater;
	else if (cond == as::Cond::Less)
		return as::Cond::NotLess;
	else if (cond == as::Cond::GreaterEqual)
		return as::Cond::Less;
	else if (cond == as::Cond::LessEqual)
		return as::Cond::Greater;

	assert(0);
}

BackendVisitor::BackendVisitor(unsigned int stackSize) {
	this->stackSize = stackSize;

	as::start(RTLabelStr.at(RTLabel::Start));
	as::build(as::Push, as::Pointer::BP);
	as::build(as::Move, as::Pointer::SP, as::Pointer::BP);

	if (stackSize != 0)
		as::build(as::Sub, stackSize, as::Pointer::SP);
}

BackendVisitor::~BackendVisitor() {
	if (this->stackSize != 0)
		as::build(as::Add, this->stackSize, as::Pointer::SP);

	as::build(as::Pop, as::Pointer::BP);
	as::build(as::Ret);
}

void BackendVisitor::visit(const Scope* scope) {
	for (const std::unique_ptr<Command>& cmd : scope->decls) {
		this->visit(cmd.get());
	}
}

void BackendVisitor::visit(const Operator* op, const Variable* var) {
	const unsigned int offset = var == nullptr ? 0 : var->offset;

	switch (op->op) {
		case Op::Plus:
			as::build(as::Add, as::Pointer::SP, offset, as::Reg::AX);
		break;

		case Op::Minus:
			if (var != nullptr)
				as::build(as::Sub, as::Pointer::SP, offset, as::Reg::AX);
			else
				as::build(as::Sub, as::Reg::AX, as::Pointer::SP, offset);
		break;

		case Op::Mul:
			as::build(as::Mul, as::Pointer::SP, offset, as::Reg::AX);
		break;
		
		case Op::Div:
			as::build(as::Move, 0, as::Reg::DX);

			if (var != nullptr)
				as::build(as::Move, as::Pointer::SP, offset, as::Reg::BX);

			as::build(as::Div, as::Reg::BX);
		break;

		case Op::Mod:
			as::build(as::Move, 0, as::Reg::DX);

			if (var != nullptr)
				as::build(as::Move, as::Pointer::SP, offset, as::Reg::BX);

			as::build(as::Div, as::Reg::BX);
			as::build(as::Move, as::Reg::DX, as::Reg::AX);
		break;

		case Op::Negate:
			as::build(as::Neg, as::Reg::AX);	
		break;
	}
}

void BackendVisitor::visit(const Command* cmd) {
	if (const Print* print = cmd->isPrint()) {
		const Term* term = print->exp->isTerm();

		if (term != nullptr && term->count() == 1) {
			if (const Var* lvar = term->front()->isVar())
				as::build(as::Push, as::Pointer::SP, lvar->variable->offset);
			else if (const Value* val = term->front()->isValue())
				as::build(as::Push, val->value);
			else
				assert(0);
		} else {
			this->visit(print->exp.get());

			as::build(as::Push, as::Reg::AX);
		}

		as::build(as::Call, RTLabelStr.at(RTLabel::PrintlnI));
		as::build(as::Add, 4, as::Pointer::SP);
	} else if (const Variable* var = cmd->isVariable()) {
		this->visit(var);
	} else if (const If* myIf = cmd->isIf()) {
		this->visit(myIf);
	}
}

void BackendVisitor::visit(const Expression* exp) {
	if (const Term* term = exp->isTerm()) {
		this->visit(term);
	} else if (/*const Array* array = */exp->isArray()) {
		// TODO:
		assert(0);
	} else if (const Condition* cond = exp->isCondition()) {
		this->visit(cond);
	}
}

void BackendVisitor::visit(const Term* term) {
	if (term->inPlace) {
		const Var* lvar = term->at(0)->isVar();
		assert(lvar);
		const Operator* op = term->at(2)->isOperator();
		assert(op);
		assert(op->isAssociative());

		if (const Value* val = term->at(1)->isValue())
			as::build(as::Move, val->value, as::Reg::AX);
		else if (const Var* lvar2 = term->at(1)->isVar())
			as::build(as::Move, as::Pointer::SP, lvar2->variable->offset, as::Reg::AX);
		else
			assert(0);

		return this->visit(op, lvar->variable);
	}

	unsigned int pushed = 0;
	const Variable* curVar = nullptr;

	for (unsigned int i = 0; i < term->count(); i++) {
		const Literal* literal = term->at(i);
		const bool isLastRun = (i + 1) >= term->count();

		if (const Value* val = literal->isValue()) {
			const Operator* op = isLastRun ? nullptr : term->at(i + 1)->isOperator();

			if (op && (op->op == Op::Div || op->op == Op::Mod))
				as::build(as::Move, val->value, as::Reg::BX);
			else {
				if (i > 0 && !term->at(i - 1)->isOperator()) {
					as::build(as::Push, as::Reg::AX);
					pushed++;
				}

				as::build(as::Move, val->value, as::Reg::AX);
			}

			curVar = nullptr;
		} else if (const Var* lvar = literal->isVar()) {
			const Variable* var = lvar->variable;

			if (isLastRun || !term->at(i + 1)->isOperator()) {
				as::build(as::Move, as::Pointer::SP, var->offset, as::Reg::AX);
			}

			curVar = var;
		} else if (const Operator* op = literal->isOperator()) {
			this->visit(op, curVar);
			curVar = nullptr;

			if (pushed > 0) {
				if (op->op == Op::Mul || op->op == Op::Plus) {
					as::build(as::Add, 4, as::Pointer::SP);
					pushed--;
				} else if (op->op == Op::Minus || op->op == Op::Div || op->op == Op::Mod) {
					as::build(as::Pop, as::Reg::AX);
					pushed--;
				}
			}

			if (!isLastRun && !term->at(i + 1)->isOperator()) {
				as::build(as::Push, as::Reg::AX);
				pushed++;
			}
		} else {
			assert(0);
		}
	}
}

void BackendVisitor::visit(const Variable* var) {
	if (var->exp == nullptr) {
		return;
	}

	if (const Term* term = var->exp->isTerm()) {
		const Value* val = term->front()->isValue();

		if (term->count() == 1 && val != nullptr) {
			as::build(as::Move, val->value, as::Pointer::SP, var->offset);
		} else {
			this->visit(term);

			as::build(as::Move, as::Reg::AX, as::Pointer::SP, var->offset);
		}
	} else if (const Array* array = var->exp->isArray()) {
		this->visit(var, array);
	} else if (/*const Empty* empty = */var->exp->isEmpty()) {
		// Do nothing
	} else {
		assert(0);
	}
}

void BackendVisitor::visit(const Variable* var, const Array* array) {
	for (unsigned int i = 0; i < array->count(); i++) {
		if (const Term* term = array->at(i)->isTerm()) {
			if (term->count() == 1) {
				const Literal* literal = term->at(0);

				if (const Value* val = literal->isValue())
					as::build(as::Move, val->value, as::Pointer::SP, var->offset + (i * 4));
				else if (const Var* lvar = literal->isVar())
					as::build(as::Move, as::Pointer::SP, lvar->variable->offset, as::Pointer::SP, var->offset + (i * 4));
				else
					assert(0);
			} else {
				this->visit(term);

				as::build(as::Move, as::Reg::AX, as::Pointer::SP, var->offset + (i * 4));
			}
		} else {
			this->visit(array->at(i));
			as::build(as::Move, as::Reg::AX, as::Pointer::SP, var->offset + (i * 4));
		}
	}
}

void BackendVisitor::visit(const If* myIf) {
	this->visit(myIf->cond->primary.get());
	// Sprung
	const std::string elabel = myIf->ifScope->label();
	const std::string hlabel = myIf->ifScope->hlabel();
	const std::string nelabel = myIf->elseScope ? myIf->elseScope->label() : hlabel;

	as::Cond cond = compareToCond(myIf->cond->primary->cmp);
	const auto& pair = myIf->cond->comps.begin();

	bool isAnd = pair != myIf->cond->comps.end() && pair->first == Link::And;

	if (isAnd) {
		as::build(as::Jump, negateCond(cond), nelabel);
	} else {
		as::build(as::Jump, cond, elabel);
	}

	for (auto& pair : myIf->cond->comps) {
		isAnd = pair.first == Link::And;

		this->visit(pair.second.get());

		cond = compareToCond(pair.second->cmp);

		switch (pair.first) {
			case Link::And:
				as::build(as::Jump, negateCond(cond), nelabel);
			break;

			case Link::Or:
				as::build(as::Jump, cond, elabel);
			break;

			default:
				assert(0);
		}
	}

	if (isAnd)
		as::build(as::Jump, cond, elabel);

	if (myIf->elseScope) {
		as::label(nelabel);
		this->visit(myIf->elseScope.get());
	}

	as::build(as::Jump, as::Cond::Always, hlabel);

	as::label(elabel);
	this->visit(myIf->ifScope.get());

	as::label(hlabel);
}

void BackendVisitor::visit(const Compare* comp) {
	const Term* term = comp->lhs->isTerm();
	if (term && term->count() == 1) {
		if (const Var* lvar = term->front()->isVar())
			as::build(as::Move, as::Pointer::SP, lvar->variable->offset, as::Reg::BX);
		else if (const Value* val = term->front()->isValue())
			as::build(as::Move, val->value, as::Reg::BX);
		else
			assert(0);
	} else {
		this->visit(comp->lhs.get());
		as::build(as::Move, as::Reg::AX, as::Reg::BX);
	}

	this->visit(comp->rhs.get());

	as::build(as::Comp, as::Reg::AX, as::Reg::BX);
}