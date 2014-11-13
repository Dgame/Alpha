#include <iostream>
#include "Scope.hpp"
#include "Var.hpp"
#include "Expr.hpp"

int main() {
	Scope* scope = new Scope(nullptr);
	scope->addVar("a", new Var(new NumExpr(42)));
	scope->addVar("b", new Var(new NumExpr(23)));
	scope->addVar("c", new Var(new AddOp(new VarExpr(scope->getVar("b")), new MulOp(new VarExpr(scope->getVar("a")), new NumExpr(3)))));
	scope->addVar("b", new Var(new NumExpr(1337)));

	scope->prepare();
	scope->eval(std::cout);

	delete scope;
}