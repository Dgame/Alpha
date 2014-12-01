#include "Scope.hpp"
#include "VarDecl.hpp"
#include "asm.hpp"

Scope::Scope(Scope* pred_scope) : _prev_used_storage(pred_scope ? pred_scope->usedStorage() : 0) , predecessor(pred_scope) {

}

u32_t Scope::usedStorage() const {
    u32_t size = _prev_used_storage;
   for (auto& pair : _existing_vars) {
        size += pair.second[0]->sizeInBit();
    }

    return size;
}

void Scope::addVarDecl(const std::string& name, VarDecl* var) {
    _existing_vars[name].push_back(var);
    this->addDecl(var);
}

const VarDecl* Scope::getVarDecl(const std::string& name) const {
   auto it = _existing_vars.find(name);
    if (it != _existing_vars.end())
        return it->second[0];
    return nullptr;
}

void Scope::addDecl(const Decl* instr) {
    _decls.emplace_back(instr);
}

void Scope::prepare() {
    u32_t stack_size = _prev_used_storage;
    for (auto& pair : _existing_vars) {
        for (VarDecl* var : pair.second) {
            var->setStackOffset(stack_size);
        }
        stack_size += pair.second[0]->sizeInBit();
    }

    for (auto& pair : _existing_vars) {
        for (VarDecl* var : pair.second) {
            var->setBaseOffset(stack_size * -1);
        }
        stack_size -= pair.second[0]->sizeInBit();
    }
}

void Scope::eval(std::ostream& out) const {
    out << "# Begin Scope" << std::endl;

    const u32_t storage = this->usedStorage() - _prev_used_storage;

    if (storage != 0)
        gas::sub(out, storage, P_STACK);

    for (auto& decl : _decls) {
        decl->eval(out);
    }

    if (storage != 0)
        gas::add(out, storage, P_STACK);

    out << "# End Scope" << std::endl;
}

const VarDecl* seekingDown(const std::string& name, const Scope* cur_scope) {
    const Scope* scope = cur_scope;
    while (scope) {
        const VarDecl* var = scope->getVarDecl(name);
        if (var)
            return var;
        scope = scope->predecessor;
    }
    return nullptr;
}