#include "Scope.hpp"
#include "Var.hpp"
#include "Expr.hpp"

u32_t Scope::grow(u32_t size) {
	const u32_t old_size = this->stack_size;
	this->stack_size += size;
	return old_size;
}

u32_t Scope::getOffsetOf(const std::string& name, u32_t size) {
	if (const Var* var = this->getVar(name))
		return var->offset;
	return this->grow();
}

void Scope::addVar(const std::string& name, const Var* var, RefType rt) {
	const VarRef* vr = new VarRef(this->getOffsetOf(name), var, rt);

	this->vars[name] = vr;
	this->addStmt(vr);
}

void Scope::addVar(const std::string& name, const Expr* exp) {
	const VarVal* vv = new VarVal(this->getOffsetOf(name), exp);

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