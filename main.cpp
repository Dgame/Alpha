#define TEST 0

#if TEST
#include "Var.hpp"
#include "Func.hpp"
#include "Operation.hpp"
#include "Statement.hpp"
#else
#include "Parser.hpp"
#endif

int main() {
#if TEST
	std::cout << ".text" << std::endl;
	Function main_func("alpha_main", new Scope());

	main_func.scope->makeVar("a", new NumExpr(42));
	// main_func.scope->makeVar("b", main_func.scope->getVar("a"), RefType::ByVal);
	main_func.scope->makeVar("c", main_func.scope->getVar("b"), RefType::EnRef);
	main_func.scope->makeVar("d", main_func.scope->getVar("c"), RefType::DeRef);

	main_func.scope->addStmt(new PrintStmt(main_func.scope->getVar("a")));
	main_func.scope->addStmt(new PrintStmt(main_func.scope->getVar("b")));

	main_func.scope->addStmt(new PrintStmt(new NumExpr(23)));

	MulOp* mul1 = new MulOp(new NumExpr(2), new AddOp(new NumExpr(4), new NumExpr(8)));
	main_func.scope->addStmt(new PrintStmt(mul1));

	AddOp* add1 = new AddOp(new MulOp(new NumExpr(2), new NumExpr(4)), new NumExpr(8));
	main_func.scope->addStmt(new PrintStmt(add1));

	main_func.eval(std::cout);
#else
	std::ofstream out("test.s");

	Parser p("test.alpha");
	p.parse();

	if (!p.hasErrors()) {
		p.eval(out);
	}
#endif
}