#ifndef _LISP_PARSER_H_
#define _LISP_PARSER_H_

#include <vector>
#include <map>
#include <string>
#include <stack>
#include <memory>

#include "ParseException.h"
#include "LispNode.h"


class Parser {
public:
    typedef int (Parser::*m_opfunc)(int, int);

    Parser();

    ~Parser();

    std::map<int, m_opfunc> multiOPMap;

    void Parse(const char *str);

    void Eval();

    enum {
        PARSE_OK,
        PARSE_NUMBER_ERROR,
        PARSE_UNKNOWN_SYMBOL,
        PARSE_END
    };

private:
    const char *_code;
    size_t _pos;
    std::map<std::string, LispNode> _lookupTable;
    LispNode *_root;
    std::stack<LispNode *> _context;


    void init();

    void parseWhiteSpace();

    int parseNumber(LispNode *node);

    int parseSymbol(LispNode *node);

    int parseToken(LispNode *node);

    int parseKeyword(LispNode *node);

    int appendElements(LispNode *node);

    int _eval(LispNode *node);

    void clearRoot();

    void clearNode(LispNode *n);

    bool isKeyword(const std::string &str);


    int op_add(int a, int b) { return a + b; }

    int op_minus(int a, int b) { return a - b; }

    int op_multip(int a, int b) { return a * b; }

    int op_div(int a, int b) {
        if (b == 0)
            throw ParseException( "divide by zero", "a / b");
        return a / b;
    }

    int op_mod(int a, int b) {
        if (b == 0)
             throw ParseException("divide by zero", "a % b");
        return a % b;
    }

    int op_greater(int a, int b) { return a > b; }

    int op_less(int a, int b) { return a < b; }

    int op_eq(int a, int b) { return a == b; }

    int op_GE(int a, int b) { return a >= b; }

    int op_LE(int a, int b) { return a <= b; }

    int op_NE(int a, int b) { return a != b; }

    int op_AND(int a, int b) { return a & b; }

    int op_OR(int a, int b) { return a | b; }

    int op_XOR(int a, int b) { return a ^ b; }

    int op_INV(int a, int b) { return ~a; }

    int op_NOT(int a, int b) { return !a; }
};


bool isWhiteSpace(char c);

#endif 


