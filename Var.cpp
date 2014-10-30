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
		gas::mov(out, num_expr->value, Offset(this->offset, gas::Pointer::Stack));
	else {
		this->expr->eval(out);
		gas::mov(out, gas::Register::AX, Offset(this->offset, gas::Pointer::Stack));
	}

	out << "# End Var " << std::endl;
}

VarRef::VarRef(u32_t the_offset, const Var* var, RefType rt) : Var(the_offset), addr(var->offset), refType(rt) {

}

void VarRef::eval(std::ostream& out) const {
	out << "# Begin Ref " << std::endl;

	switch (this->refType) {
		case RefType::ByVal:
			gas::mov(out, Offset(this->addr, gas::Pointer::Stack), gas::Register::AX);
			gas::mov(out, gas::Register::AX, Offset(this->offset, gas::Pointer::Stack));
		break;

		case RefType::DeRef:
			gas::mov(out, Offset(this->addr, gas::Pointer::Stack), gas::Register::AX);
			gas::mov(out, Offset(0, gas::Register::AX), gas::Register::AX);
			gas::mov(out, gas::Register::AX, Offset(this->offset, gas::Pointer::Stack));
		break;

		case RefType::EnRef:
			if (this->addr != 0) {
				gas::lea(out, Offset(this->addr, gas::Pointer::Stack), gas::Register::AX);
				gas::mov(out, gas::Register::AX, Offset(this->offset, gas::Pointer::Stack));
			} else {
				gas::mov(out, 0, Offset(this->offset, gas::Pointer::Stack));
			}
		break;
	}

	out << "# End Ref " << std::endl;
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
			gas::mov(out, num_expr->value, Offset(this->offset + (i * 4), gas::Pointer::Stack));
		else {
			this->items[i]->eval(out);
			gas::mov(out, gas::Register::AX, Offset(this->offset + (i * 4), gas::Pointer::Stack));
		}
	}

	out << "# End Array " << std::endl;
}