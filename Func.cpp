#include "asm.hpp"
#include "Func.hpp"
#include "Var.hpp"
#include "Expr.hpp"

u32_t Scope::grow(u32_t size) {
	const u32_t old_size = this->stack_size;
	this->stack_size += size;

	return old_size;
}

void Scope::makeVar(const std::string& name, const Var* var, RefType rt) {
	const VarRef* vr = new VarRef(this->grow(), var, rt);

	this->vars[name] = vr;
	this->addStmt(vr);
}

void Scope::makeVar(const std::string& name, const Expr* exp) {
	const VarVal* vv = new VarVal(this->grow(), exp);

	this->vars[name] = vv;
	this->addStmt(vv);
}

const Var* Scope::getVar(const std::string& name) const {
	auto it = this->vars.find(name);
	if (it != this->vars.end())
		return it->second;
	return nullptr;
}

void Scope::addStmt(const Statement* stmt) {
	this->statements.push_back(std::unique_ptr<const Statement>(stmt));
}

void Scope::eval(std::ostream& out) const {
	for (auto& stmt : this->statements) {
		stmt->eval(out);
	}
}

Function::Function(const std::string& the_name, Scope* the_scope) : name(the_name), scope(the_scope) {
	if (this->name == "main")
		this->name = "alpha_main"; // Hack
}

void Function::eval(std::ostream& out) const {
	out << ".globl\t_" << this->name << "\n.def\t_" << this->name << "\n" << std::endl;
	out << '_' << this->name << ':' << std::endl;

	gas::push(out, P_BASE);
	gas::mov(out, P_STACK, P_BASE);
	gas::sub(out, this->scope->stack_size, P_STACK);

	this->scope->eval(out);

	gas::add(out, this->scope->stack_size, P_STACK);
	gas::pop(out, P_BASE);
	gas::ret(out);
}