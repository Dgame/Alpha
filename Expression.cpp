#include "Expression.hpp"
#include "Commands.hpp"

Value::Value(int val) : value(val) {

}

Operator::Operator(Op myop) : op(myop) {

}

Var::Var(const Variable* vp, unsigned int os) : variable(vp), offset(os) {

}

unsigned int Var::offsetOf() const {
	return this->variable->offset + this->offset;
}

Compare::Compare(Expression* lp, Expression* rp, Cmp mycmp) : lhs(lp), rhs(rp), cmp(mycmp) {

}