#ifndef ALPHA_SCOPE_HPP
#define ALPHA_SCOPE_HPP

#include <ostream>
#include <string>
#include <memory>
#include <map>
#include <vector>

#include "types.hpp"
#include "Instruction.hpp"

class Var;

class Scope {
private:
    std::map<std::string, std::vector<Var*>> _existing_vars;
    std::vector<std::unique_ptr<const Instruction>> _instructions;

public:
    Scope* predecessor;

    explicit Scope(Scope*);
    virtual ~Scope() { }

    void addVar(const std::string&, Var*);
    const Var* getVar(const std::string&) const;

    void addInstruction(const Instruction*);
    void prepare();

    virtual void eval(std::ostream&) const;
};

const Var* searchVarInAllScopes(const std::string&, const Scope*);

#endif