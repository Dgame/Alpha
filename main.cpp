#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Parser.hpp"
#include "Backend.hpp"

void loadContent(const std::string& filename, std::vector<char>& content) {
	std::ifstream in(filename);

	std::copy(
		std::istreambuf_iterator<char>(in.rdbuf()),
		std::istreambuf_iterator<char>(),
		std::inserter(content, content.begin()));
}

int main(/*int argc, char const* argv[]*/) {
	for (unsigned int nr = 0; nr < 27; nr++) {
		std::ostringstream in;
		in << "Input/in" << nr << ".txt";

		std::vector<char> content;
		loadContent(in.str(), content);

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

		std::ostringstream out;
		out << "Output/out" << nr << ".s";

		freopen(out.str().c_str(), "w", stdout);

		BackendVisitor backend(vm.stackSize);

		for (Scope& scope : scopes.scopes) {
			for (std::unique_ptr<Command>& cmd : scope.decls) {
				backend.visit(cmd.get());
			}
		}
	}

	return 0;
}