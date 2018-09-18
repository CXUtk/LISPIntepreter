//
// Created by Chen Xujie on 9/18/18.
//

#ifndef LISPINTEPRETER_LISPNODE_H
#define LISPINTEPRETER_LISPNODE_H


#include <vector>

enum OP_CODE {
    GREATER_EQ = 0x100,
    LESS_EQ,
    NOT_EQ,
    LOGIC_AND,
    LOGIC_OR

};

enum class ValueType {
    // Rule: word in table
            KEYWORD,
    // Rule: (<function call>/<key> [<arguments>])
            EXPRESSION,
    // Rule: REG -> (-)?[0-9]+(.)?[0-9]+
            CONSTANT,
    // Rule: \w+.*\s
            SYMBOL,
    // Rule: \".*\"
            STRING,
    // Rule: define (<symbol> [<arguments>]) (<expression>)
            FUNCTION,
    // Rule: (<function> <args...>)
            FUNCTION_CALL,
    EMPTY
};

class LispNode {
public:

    LispNode() = default;

    virtual ~LispNode() { for (auto k : children) delete k; }

    virtual void appendChild(LispNode *node) { children.push_back(node); }

    virtual int eval() { if (!children.empty()) children[0]->eval(); }

protected:
    std::vector<LispNode *> children;
};


#endif //LISPINTEPRETER_LISPNODE_H
