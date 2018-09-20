//
// Created by Chen Xujie on 9/18/18.
//

#ifndef LISPINTEPRETER_LISPFUNCTION_H
#define LISPINTEPRETER_LISPFUNCTION_H

#include <string>
#include <map>
#include "LispNode.h"


class LispFunction : public LispNode {
public:
    LispFunction() : LispNode(), argumentNumber(-1) {}

    explicit LispFunction(int argNumber) : LispNode(), argumentNumber(argNumber) {

    }

    int eval() override;

    std::string getName() const { return funcName; }

    typedef int (*funcType)(int, int);

    static std::map<std::string, funcType> opFuncTable;
    static void setUpTable();

    void setName(const char c) {
        std::string s;
        s.push_back(c);
        funcName = s;
    }

    void setName(const std::string &name) { funcName = name; }

    void setArgumentNum(int num) { argumentNumber = num; }

    std::string Type() const override { return "function"; }

private:
    int argumentNumber;
    std::string funcName;
};


#endif //LISPINTEPRETER_LISPFUNCTION_H
