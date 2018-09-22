//
// Created by Chen Xujie on 9/18/18.
//

#include "LispFunction.h"
#include "ParseException.h"


std::map<std::string, LispFunction::funcType> LispFunction::opFuncTable;
std::map<std::string, LispFunction::FunctionInfo> LispFunction::customizedFuncTable;

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

int LispFunction::eval() {
    if(opFuncTable.find(funcName) != opFuncTable.end()){
        if(argumentNumber > 0 && argumentNumber != children.size()){
            throw ParseException("Invalid argument number", "");
        }
        int num = children[0]->eval();
        if(argumentNumber == 1){
            return (*opFuncTable[funcName])(num, 0);
        }
        for (int i = 1; i < children.size(); i++) {
            num = (*opFuncTable[funcName])(num, children[i]->eval());
        }
        return num;
    }
}

void LispFunction::setUpTable() {
    opFuncTable["+"] = op_add;
    opFuncTable["-"] = op_minus;
    opFuncTable["*"] = op_multip;
    opFuncTable["/"] = op_div;
    opFuncTable["%"] = op_mod;
    opFuncTable[">"] = op_greater;
    opFuncTable["<"] = op_less;
    opFuncTable["="] = op_eq;
    opFuncTable["&"] = op_AND;
    opFuncTable["|"] = op_OR;
    opFuncTable["^"] = op_XOR;
    opFuncTable["!"] = op_NOT;
    opFuncTable["~"] = op_INV;
    opFuncTable[">="] = op_GE;
    opFuncTable["<="] = op_LE;
    opFuncTable["!="] = op_NE;
}
