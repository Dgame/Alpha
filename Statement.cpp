#include "Statement.hpp"
#include "asm.hpp"
#include "Var.hpp"


PrintStmt::PrintStmt(const Expr* the_expr) : expr(the_expr) {

}

PrintStmt::PrintStmt(const std::string& the_label) : label(the_label) {

}

void PrintStmt::eval(std::ostream& out) const {
	out << "# Begin print" << std::endl;

	const std::string func_label_prefix = this->insertNewLine ? "_println" : "_print";

	if (this->expr) {
		const i32_t* value = nullptr;
		this->expr->cte(&value);

		if (value)
			gas::push(out, *value);
		else {
			this->expr->eval(out);
			gas::push(out, E_AX);
		}
		
		gas::call(out, func_label_prefix + "_int");
	} else if (this->label.size()) {
		gas::push(out, this->label);
		gas::call(out, func_label_prefix + "_string");
	}

	gas::add(out, 4, P_STACK);

	out << "# End print" << std::endl;
}

void MultiplePrintStmt::append(PrintStmt* print) {
	this->prints.emplace_back(print);
}

void MultiplePrintStmt::adjust() {
	if (this->prints.size() > 1) {
		// The last one has still a newline at the end
		for (u32_t i = 0; i < this->prints.size() - 1; i++) {
			this->prints[i]->insertNewLine = false;
		}
	}
}

void MultiplePrintStmt::eval(std::ostream& out) const {
	for (auto& print : this->prints) {
		print->eval(out);
	}
}


IncStmt::IncStmt(u32_t the_offset) : offset(the_offset) {

}

void IncStmt::eval(std::ostream& out) const {
	gas::inc(out, gas::Offset(this->offset, P_STACK));
}

DecStmt::DecStmt(u32_t the_offset) : offset(the_offset) {

}

void DecStmt::eval(std::ostream& out) const {
	gas::dec(out, gas::Offset(this->offset, P_STACK));
}