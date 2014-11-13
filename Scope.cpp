#include "Scope.hpp"
#include "Var.hpp"
#include "asm.hpp"

Scope::Scope(Scope* pred_scope) : predecessor(pred_scope) {

}

void Scope::addVar(const std::string& name, Var* var) {
    _existing_vars[name].push_back(var);
    this->addInstruction(var);
}

const Var* Scope::getVar(const std::string& name) const {
   auto it = _existing_vars.find(name);
    if (it != _existing_vars.end())
        return it->second[0];
    return nullptr;
}

void Scope::addInstruction(const Instruction* instr) {
    _instructions.emplace_back(instr);
}

void Scope::prepare() {
    u32_t stack_size = 0;
    for (auto& pair : _existing_vars) {
        for (auto& var : pair.second) {
            var->setStackOffset(stack_size);
        }
        stack_size += 4;
    }

    for (auto& pair : _existing_vars) {
        for (auto& var : pair.second) {
            var->setBaseOffset(stack_size * -1);
        }
        stack_size -= 4;
    }

    Scope* cur_scope = this->predecessor;
    while (cur_scope) {
        cur_scope->prepare();
    }
}

void Scope::eval(std::ostream& out) const {
    for (auto& instr : _instructions) {
        instr->eval(out);
    }
}

const Var* searchVarInAllScopes(const std::string& name, const Scope* cur_scope) {
    const Scope* scope = cur_scope;
    while (scope) {
        const Var* var = scope->getVar(name);
        if (var)
            return var;
        scope = scope->predecessor;
    }
    return nullptr;
}