#ifndef ALPHA_PARSER_HPP
#define ALPHA_PARSER_HPP

#include <iostream>

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
    void error(const char*);
 
    template <typename T, typename... Args>
    void error(const char*, const T&, Args&& ...args);

    void skipSpaces();

    bool accept(char);
    bool accept(const std::string&);
    bool expect(char);
    bool expect(const std::string&);

    bool readIdentifier(std::string&);
    bool readNumber(i32_t&);

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

#endif