#include "Expression.hpp"

Value::Value(int val) : value(val) {

}

Operator::Operator(Op myop) : op(myop) {

}

Var::Var(const Variable* vp) : variable(vp) {

}

Item::Item(const Variable* vp, unsigned int os) : variable(vp), offset(os) {

}

Compare::Compare(Expression* lp, Expression* rp, Cmp mycmp) : lhs(lp), rhs(rp), cmp(mycmp) {

}