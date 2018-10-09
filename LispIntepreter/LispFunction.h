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
    LispFunction() : LispNode() {}

    explicit LispFunction(int argNumber) : LispNode() {

    }

	ReturnValue eval() override;

    typedef int (*funcType)(int, int);
	typedef struct {
		int argNumber;
		LispNode * node;
	} FunctionInfo;

    static std::map<std::string, funcType> opFuncTable;
	static std::map<std::string, FunctionInfo> customizedFuncTable;
	static std::vector<LispNode *> arg_context;
    static void setUpTable();
	static void destroyTable();

    void setName(const char c) {
        std::string s;
        s.push_back(c);
        funcName = s;
    }

	std::string getName() const { return funcName; }
    void setName(const std::string &name) { funcName = name; }

	int getArgumentNum() { return children.size(); }

    std::string Type() const override { return "function"; }

	std::string Description() const override {
		static char buf[256];
		sprintf(buf, "Function: %s", funcName.c_str());
		return std::string(buf);
	}

private:
    std::string funcName;
};


#endif //LISPINTEPRETER_LISPFUNCTION_H
