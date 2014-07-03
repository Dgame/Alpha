#include <cstdio>
#include <iostream>
#include "Parser.hpp"
#include "Backend.hpp"

int main(/*int argc, char const* argv[]*/) {
	const std::string Test[] = {
		/*  0 */ "print 42", // 42
		/*  1 */ "print 2 + 4", // 6
		/*  2 */ "print 2 - 4", // -2
		/*  3 */ "print 2 * 4", // 8
		/*  4 */ "print 4 / 2", //
		/*  5 */ "print 6 % 4", // 
		/*  6 */ "print 1 + 2 * 3", // 7
		/*  7 */ "print (1 + 2) * 3", // 9
		/*  8 */ "print 2 * 3 - 4 + 6 * 2", // 14
		/*  9 */ "var a = 23\nprint a", // 23
		/* 10 */ "var a = 23\nvar b = a\nprint b", // 23
		/* 11 */ "var a = 2\nprint a + 4", // 6
		/* 12 */ "var a = 2\nprint a - 4", // -2
		/* 13 */ "var a = 2\nprint a * 4", // 8
		/* 14 */ "var a = 2\nprint 4 / a", // 
		/* 15 */ "var a = 2\nprint a % 4", // 
		/* 16 */ "var a = 2\nprint 2 + a", // 4
		/* 17 */ "var a = 2\nprint 2 - a", // 0
		/* 18 */ "var a = 2\nprint 2 * a", // 4
		/* 19 */ "var a = 2\nprint 2 / a", // 
		/* 20 */ "var a = 2\nprint 2 % a", // 
		/* 21 */ "var a = 2\nvar b = 42\nprint a + b", // 44
		/* 22 */ "var a = 2\nvar b = 42\nprint a - b", // -40
		/* 23 */ "var a = 2\nvar b = 42\nprint a * b", // 84
		/* 24 */ "var a = 2\nvar b = 42\nprint a / b", //
		/* 25 */ "var a = 2\nvar b = 42\nprint a % b" // 
	};

	unsigned int nr = 0;
	for (const std::string& content : Test) {
		Scopes scopes;
		scopes.pushScope();

		VarManager vm(scopes);
		CommandManager cm(scopes);

		Env env;
		env.vm = &vm;
		env.cm = &cm;

		Loc loc(&*content.begin(), &*content.end() + 1);

		Parser p(env, loc);

		while (p.parse()) {

		}

		std::ostringstream stm;
		stm << "Output/out" << nr++ << ".s";

		freopen(stm.str().c_str(), "w", stdout);

		BackendVisitor backend(vm.stackSize);

		for (Scope& scope : scopes.scopes) {
			for (std::unique_ptr<Command>& cmd : scope.decls) {
				backend.visit(cmd.get());
			}
		}
	}

	return 0;
}