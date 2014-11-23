#ifndef ALPHA_SCOPE_HPP
#define ALPHA_SCOPE_HPP

#include <ostream>
#include <string>
#include <memory>
#include <map>
#include <vector>

#include "types.hpp"
#include "Decl.hpp"

class VarDecl;

class Scope {
private:
    const u32_t _prev_used_storage;

    std::map<std::string, std::vector<VarDecl*>> _existing_vars;
    std::vector<std::unique_ptr<const Decl>> _decls;

public:
    Scope* predecessor;

    explicit Scope(Scope*);
    virtual ~Scope() { }

    u32_t usedStorage() const;

    void addVarDecl(const std::string&, VarDecl*);
    const VarDecl* getVarDecl(const std::string&) const;

    void addDecl(const Decl*);
    void prepare();

    virtual void eval(std::ostream&) const;
};

const VarDecl* seekingDown(const std::string&, const Scope*);

#endif