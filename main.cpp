#define TEST 0
#define CMD_COMPILER 1

#include <iostream>
#include <fstream>
#if TEST
#include "Scope.hpp"
#include "Var.hpp"
#include "Expr.hpp"
#include "Instr.hpp"
#include "Func.hpp"
#else
#if CMD_COMPILER
#include <sstream>
#endif
#include "Parser.hpp"
#endif

int main(int argc, const char* argv[]) {
#if TEST
    Func* func = new Func("_alpha_main", new Scope(nullptr));

    func->getScope()->addVar("a", new Var(new NumExpr(42)));
    func->getScope()->addVar("b", new Var(new NumExpr(23)));

    // Scope* nested = new Scope(func->getScope());
    // nested->addVar("foo", new Var(new NumExpr(128)));

    // nested->prepare();
    // nested->eval(std::cout);

    // delete nested;
    // std::cout << "----" << std::endl;

    func->getScope()->addVar("c", new Var(new AddOp(new VarExpr(func->getScope()->getVar("b")), new MulOp(new VarExpr(func->getScope()->getVar("a")), new NumExpr(3)))));
    func->getScope()->addVar("b", new Var(new NumExpr(1337)));

    std::string label = "LC0";
    std::string str   = "b + (a * 3) = ";

    auto pr1 = new PrintInstr(new VarExpr(func->getScope()->getVar("b")));

    func->getScope()->addInstr(pr1);

    auto pr2 = new PrintInstr(new StringExpr(label));
    pr2->addExpr(new VarExpr(func->getScope()->getVar("c")));

    func->getScope()->addInstr(pr2);

    func->eval(std::cout);

    std::cout << label << ':' << std::endl;
    std::cout << "\t.ascii\t\"" << str << "\\0\"" << std::endl;

    delete func;
#elif CMD_COMPILER
    if (argc >= 2) {
        std::string filename(argv[1]);
        if (filename.length() > 5) {
            std::stringstream buf(filename);
            std::string basename;
            std::getline(buf, basename, '.');

            std::ofstream output(basename + ".s");

            Parser p;
            Env* env = p.parse(filename);
            if (env)
                env->eval(output);
        } else {
            std::cerr << "Invalid input file" << std::endl;
        }
    } else {
        std::cerr << "No input file" << std::endl;
    }
#else
    std::ofstream output("test.s");

    Parser p;
    Env* env = p.parse("test.alpha");
    if (env)
        env->eval(output);
#endif
}