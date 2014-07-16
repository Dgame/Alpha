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
	for (unsigned int nr = 0; nr < 41; nr++) {
		std::ostringstream in;
		in << "Input/in" << nr << ".txt";

		const std::string filename = in.str();

		std::cerr << filename << std::endl;

		std::vector<char> content;
		loadContent(filename, content);

		ScopeManager sm;
		sm.pushScope();

		VarManager vm(sm);
		CommandManager cm(sm);

		Env env;
		env.vm = &vm;
		env.cm = &cm;
		env.sm = &sm;

		Loc loc(filename, &*content.begin(), &*content.end() + 1);

		Parser p(env, loc);

		while (p.parse()) {

		}

		if (!loc.eof()) 
			break;

		std::ostringstream out;
		out << "Output/out" << nr << ".s";

		freopen(out.str().c_str(), "w", stdout);

		BackendVisitor backend(vm.stackSize);

		while (sm.scopes.size() != 0) {
			std::unique_ptr<Scope> scope = std::move(sm.scopes.front());
			sm.scopes.pop_front();

			backend.visit(scope.get());
		}
	}

	return 0;
}