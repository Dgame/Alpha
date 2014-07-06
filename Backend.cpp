#include "Backend.hpp"

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
		this->visit(myIf->cond.get());
	}
}

void BackendVisitor::visit(const Expression* exp) {
	if (const Term* term = exp->isTerm()) {
		this->visit(term);
	} else if (const Array* array = exp->isArray()) {
		this->visit(array);
	} else if (const Condition* cond = exp->isCondition()) {
		this->visit(cond);
	}
}

void BackendVisitor::visit(const Term* term) {
	unsigned int pushed = 0;

	const Variable* curVar = nullptr;

	for (unsigned int i = 0; i < term->count(); i++) {
		const Literal* literal = term->at(i);
		const bool isLastRun = (i + 1) >= term->count();

		if (const Value* val = literal->isValue()) {
			const Operator* op = isLastRun ? nullptr : term->at(i + 1)->isOperator();

			if (op && (op->op == Op::Div || op->op == Op::Mod))
				as::build(as::Move, val->value, as::Reg::BX);
			else
				as::build(as::Move, val->value, as::Reg::AX);

			curVar = nullptr;
		} else if (const Var* lvar = literal->isVar()) {
			const Variable* var = lvar->variable;

			if (!var->exp)
				continue;

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
		} else {
			assert(0);
		}

		if (isLastRun 
			|| term->at(i + 1)->isOperator() 
			|| term->at(i + 1)->isVar())
		{
			continue;
		}

		// For Div/Mod correction
		const Operator* op = term->at(i + 2)->isOperator();
		if (op && (op->op == Op::Div || op->op == Op::Mod)) {
			continue;
		}

		as::build(as::Push, as::Reg::AX);
		pushed++;
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
		this->visit(array);

		// TODO: 
	} else {
		assert(0);
	}
}

void BackendVisitor::visit(const Array*) {
	// TODO: 
}

void BackendVisitor::visit(const Condition*) {
	// TODO: 
}