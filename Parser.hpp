#ifndef ALPHA_PARSER_HPP
#define ALPHA_PARSER_HPP

#include <string>
#include "types.hpp"
#include "Loc.hpp"
#include "Env.hpp"

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
    void error(const std::string&);

    void skip_spaces();

    bool accept(const std::string&);
    bool expect(const std::string&);

    bool read_identifier(std::string&);
    bool read_number(i32_t&);

    Env* parse(const std::string&);
    
    void parseFunc();
    void parseScope();

    void parsePrint();
    bool parseVar(const std::string&);

    StringExpr* parseStringExpr();

    Expr* parseExpr();
    Expr* parseTerm();
    Expr* parseFactor();
};

#endif