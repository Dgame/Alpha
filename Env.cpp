#include "Env.hpp"
#include <iostream>

void Env::addFunc(const Func* func) {
	_funcs.emplace_back(func);
}

void Env::eval(std::ostream& out) const {
	bool has_main = false;
	for (auto& func : _funcs) {
		if (func->getName() == "main") {
			has_main = true;
			break;
		}
	}

	if (!has_main) {
		std::cerr << "No main function" << std::endl;
		return;
	}

	out << ".text" << std::endl;

	for (auto& func : _funcs) {
		func->eval(out);
	}

	this->labels.eval(out);
}
