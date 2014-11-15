#ifndef ALPHA_SCOPE_HPP
#define ALPHA_SCOPE_HPP

#include <ostream>
#include <string>
#include <memory>
#include <map>
#include <vector>

#include "types.hpp"
#include "Instr.hpp"

class Var;

class Scope {
private:
    const u32_t _prev_used_storage;

    std::map<std::string, std::vector<Var*>> _existing_vars;
    std::vector<std::unique_ptr<const Instr>> _instructions;

public:
    Scope* predecessor;

    explicit Scope(Scope*);
    virtual ~Scope() { }

    u32_t usedStorage() const;

    void addVar(const std::string&, Var*);
    const Var* getVar(const std::string&) const;

    void addInstr(const Instr*);
    void prepare();

    virtual void eval(std::ostream&) const;
};

const Var* seekingDown(const std::string&, const Scope*);

#endif