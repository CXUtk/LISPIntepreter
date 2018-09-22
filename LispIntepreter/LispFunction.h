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

    typedef int (*funcType)(int, int);
	typedef int(*customFuncType)(LispFunction *);
	typedef struct FunctionInfo {
		int argNumber;
		customFuncType func;
	};

    static std::map<std::string, funcType> opFuncTable;
	static std::map<std::string, FunctionInfo> customizedFuncTable;
    static void setUpTable();

    void setName(const char c) {
        std::string s;
        s.push_back(c);
        funcName = s;
    }

	std::string getName() const { return funcName; }
    void setName(const std::string &name) { funcName = name; }

	int getArgumentNum() { return argumentNumber; }
    void setArgumentNum(int num) { argumentNumber = num; }

    std::string Type() const override { return "function"; }

private:
    int argumentNumber;
    std::string funcName;
};


#endif //LISPINTEPRETER_LISPFUNCTION_H
