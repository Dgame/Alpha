// #include "asm.hpp"
#include "Var.hpp"
#include "Func.hpp"
#include "Operation.hpp"
#include "Statement.hpp"

int main() {
	std::cout << ".text" << std::endl;

	Function main_func("alpha_main");
	main_func.scope.make_var("a", new NumExpr(42));
	main_func.scope.make_var("b", main_func.scope.getVar("a"), RefType::ByVal);
	main_func.scope.make_var("c", main_func.scope.getVar("b"), RefType::EnRef);
	main_func.scope.make_var("d", main_func.scope.getVar("c"), RefType::DeRef);

	main_func.scope.addStmt(new PrintStmt(main_func.scope.getVar("a")));
	main_func.scope.addStmt(new PrintStmt(main_func.scope.getVar("b")));

	MulOp* mul1 = new MulOp(new NumExpr(2), new AddOp(new NumExpr(4), new NumExpr(8)));
	main_func.scope.addStmt(new PrintStmt(mul1));

	AddOp* add1 = new AddOp(new MulOp(new NumExpr(2), new NumExpr(4)), new NumExpr(8));
	main_func.scope.addStmt(new PrintStmt(add1));

	main_func.eval(std::cout);
}