#ifndef ALPHA_PARSER_HPP
#define ALPHA_PARSER_HPP

#include <iostream>

#include "types.hpp"
#include "Loc.hpp"
#include "Env.hpp"
#include "util.hpp"

class Expr;
class StringExpr;
class Scope;

class Parser {
private:
    Loc _loc;
    Scope* _cur_scope = nullptr;
    bool _errors = false;

    Env _env;

public:
    template <typename... Args>
    void error(Args&& ...args);

    void skip_spaces();

    bool accept(const std::string&);
    bool expect(const std::string&);

    bool read_identifier(std::string&);
    bool read_number(i32_t&);

    Env* parse(const std::string&);
    
    void parseFunc();
    void parseScope();

    void parsePrintDecl();
    bool parseVarDecl(const std::string&);

    StringExpr* parseStringExpr();

    Expr* parseExpr();
    Expr* parseTerm();
    Expr* parseFactor();
};
 
template <typename... Args>
void Parser::error(Args&& ...args) {
    _errors = true;
    out::print(std::cerr, "Error: ", args..., " in line ", _loc.lineNr);
}

#endif