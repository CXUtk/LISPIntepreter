//
// Created by Chen Xujie on 9/18/18.
//

#ifndef LISPINTEPRETER_LISPFUNCTION_H
#define LISPINTEPRETER_LISPFUNCTION_H

#include <string>
#include "LispNode.h"


class LispFunction : public LispNode {
public:
    LispFunction() : LispNode(), argumentNumber(-1) {}

    LispFunction(int argNumber) : LispNode(), argumentNumber(argNumber) {

    }

    int eval() override;

    std::string getName() const { return funcName; }

    void setName(const char c) {
        std::string s;
        s.push_back(c);
        funcName = s;
    }

    void setName(const std::string &name) { funcName = name; }

    void setArgumentNum(int num) { argumentNumber = num; }

private:
    int argumentNumber;
    std::string funcName;
};


#endif //LISPINTEPRETER_LISPFUNCTION_H
