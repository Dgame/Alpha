#include "Var.hpp"
#include "Expr.hpp"
#include "asm.hpp"

Var::Var(u32_t the_offset) : offset(the_offset) {

}

VarVal::VarVal(u32_t the_offset, const Expr* the_exp) : Var(the_offset), expr(the_exp) {

}

void VarVal::eval(std::ostream& out) const {
	out << "# Begin Var " << std::endl;

	if (const NumExpr* num_expr = this->expr->isNumExpr())
		gas::mov(out, num_expr->value, gas::Offset(this->offset, P_STACK));
	else {
		this->expr->eval(out);
		gas::mov(out, E_AX, gas::Offset(this->offset, P_STACK));
	}

	out << "# End Var " << std::endl;
}

VarRef::VarRef(u32_t the_offset, const Var* var, RefType rt) : Var(the_offset), addr(var->offset), refType(rt) {

}

void VarRef::eval(std::ostream& out) const {
	switch (this->refType) {
		case RefType::ByVal:
			out << "# Begin ByVal " << std::endl;

			gas::mov(out, gas::Offset(this->addr, P_STACK), E_AX);
			gas::mov(out, E_AX, gas::Offset(this->offset, P_STACK));

			out << "# End ByVal " << std::endl;
		break;

		case RefType::DeRef:
			out << "# Begin DeRef " << std::endl;

			gas::mov(out, gas::Offset(this->addr, P_STACK), E_AX);
			gas::mov(out, gas::Offset(0, E_AX), E_AX);
			gas::mov(out, E_AX, gas::Offset(this->offset, P_STACK));

			out << "# End DeRef " << std::endl;
		break;

		case RefType::EnRef:
			out << "# Begin EnRef " << std::endl;

			if (this->addr != 0) {
				gas::lea(out, gas::Offset(this->addr, P_STACK), E_AX);
				gas::mov(out, E_AX, gas::Offset(this->offset, P_STACK));
			} else {
				gas::mov(out, 0, gas::Offset(this->offset, P_STACK));
			}

			out << "# End EnRef " << std::endl;
		break;
	}
}

Array::Array(u32_t the_offset, const std::initializer_list<const Expr*>& elems) : Var(the_offset) {
	this->items.reserve(elems.size());
	for (const Expr* elem : elems) {
		this->items.push_back(std::unique_ptr<const Expr>(elem));
	}
}

void Array::eval(std::ostream& out) const {
	out << "# Begin Array " << std::endl;

	for (u32_t i = 0; i < this->items.size(); i++) {
		if (const NumExpr* num_expr = this->items[i]->isNumExpr())
			gas::mov(out, num_expr->value, gas::Offset(this->offset + (i * 4), P_STACK));
		else {
			this->items[i]->eval(out);
			gas::mov(out, E_AX, gas::Offset(this->offset + (i * 4), P_STACK));
		}
	}

	out << "# End Array " << std::endl;
}