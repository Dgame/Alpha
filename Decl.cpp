#include "Decl.hpp"
#include "asm.hpp"

PrintDecl::PrintDecl(const Expr* exp) {
    this->addExpr(exp);
}

void PrintDecl::addExpr(const Expr* exp) {
    _exprs.emplace_back(exp);
}

void PrintDecl::eval(std::ostream& out) const {
    out << "# Begin print" << std::endl;

    i32_t val;
    std::string ident;

    for (auto& exp : _exprs) {
        if (exp->cte(&val)) {
            gas::push(out, val);
            gas::call(out, "_print_int");
        } else if (exp->cte(&ident)) {
            gas::push(out, ident);
            gas::call(out, "_print_str");
        } else {
            exp->eval(out);
            gas::push(out, E_AX);
            gas::call(out, "_print_int");
        }
        gas::add(out, 4, P_STACK);
    }
    gas::call(out, "_print_ln");

    out << "# End print" << std::endl;
}