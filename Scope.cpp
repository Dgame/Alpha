#include "Scope.hpp"
#include "Var.hpp"
#include "asm.hpp"

Scope::Scope(Scope* pred_scope) : _prev_used_storage(pred_scope ? pred_scope->usedStorage() : 0) , predecessor(pred_scope) {

}

u32_t Scope::usedStorage() const {
    u32_t size = _prev_used_storage;
   for (auto& pair : _existing_vars) {
        size += pair.second[0]->sizeOf();
    }

    return size;
}

void Scope::addVar(const std::string& name, Var* var) {
    _existing_vars[name].push_back(var);
    this->addInstr(var);
}

const Var* Scope::getVar(const std::string& name) const {
   auto it = _existing_vars.find(name);
    if (it != _existing_vars.end())
        return it->second[0];
    return nullptr;
}

void Scope::addInstr(const Instr* instr) {
    _instructions.emplace_back(instr);
}

void Scope::prepare() {
    u32_t stack_size = _prev_used_storage;
    for (auto& pair : _existing_vars) {
        for (Var* var : pair.second) {
            var->setStackOffset(stack_size);
        }
        stack_size += pair.second[0]->sizeOf();
    }

    for (auto& pair : _existing_vars) {
        for (Var* var : pair.second) {
            var->setBaseOffset(stack_size * -1);
        }
        stack_size -= pair.second[0]->sizeOf();
    }
}

void Scope::eval(std::ostream& out) const {
    out << "# Begin Scope" << std::endl;

    const u32_t storage = this->usedStorage() - _prev_used_storage;

    if (storage != 0)
        gas::sub(out, storage, P_STACK);

    for (auto& instr : _instructions) {
        instr->eval(out);
    }

    if (storage != 0)
        gas::add(out, storage, P_STACK);

    out << "# End Scope" << std::endl;
}

const Var* seekingDown(const std::string& name, const Scope* cur_scope) {
    const Scope* scope = cur_scope;
    while (scope) {
        const Var* var = scope->getVar(name);
        if (var)
            return var;
        scope = scope->predecessor;
    }
    return nullptr;
}