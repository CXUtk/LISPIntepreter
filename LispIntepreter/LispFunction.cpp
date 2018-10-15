//
// Created by Chen Xujie on 9/18/18.
//

#include "LispFunction.h"
#include "ParseException.h"
#include "LispArgSlot.h"


std::map<std::string, LispFunction::funcType> LispFunction::opFuncTable;
std::map<std::string, FunctionInfo> LispFunction::customizedFuncTable;
std::vector<LispNode *> LispFunction::arg_context;

int op_add(int a, int b) { return a + b; }

int op_minus(int a, int b) { return a - b; }

int op_multip(int a, int b) { return a * b; }

int op_div(int a, int b) {
	if (b == 0)
		throw ParseException("divide by zero", "a / b");
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

ReturnValue LispFunction::eval() {
	if (opFuncTable.find(funcName) != opFuncTable.end()) {
		// 如果是已经定义的运算函数以及操作符
		if (getArgumentNum() > 0 && (getArgumentNum() != children.size() || children.size() == 0)) {
			throw ParseException("Invalid argument number", "");
		}
		ReturnValue num = children[0]->eval();
		if (getArgumentNum() == 1) {
			auto n = (*opFuncTable[funcName])(num.getInt(), 0);
			ReturnValue ret(ValueType::INTEGER);
			ret.setInt(n);
			return ret;
		}
		for (int i = 1; i < children.size(); i++) {
			auto a = num.getInt();
			auto b = children[i]->eval().getInt();
			num.setInt((*opFuncTable[funcName])(a, b));
		}
		return num;
	}
	else if (customizedFuncTable.find(funcName) != customizedFuncTable.end()) {
		// 如果是自定义的函数
		auto n = customizedFuncTable[funcName];
		if (n.argNumber > 0 && getArgumentNum() != n.argNumber) {
			throw ParseException("Invalid argument number", "");
		}
		// 导入参数列表
		if(n.argNumber > 0){
			arg_context.assign(children.begin(), children.end());
		}
		if (n.node->children[0]->Type() == "arg_slot") {
			auto slot = (LispArgSlot *)n.node->children[0];
			for (int i = 1; i < n.node->getChildrenSize(); i++) {
				arg_context[slot->getSlot()]->children.push_back(n.node->children[i]);

			}
		}
		auto ret = customizedFuncTable[funcName].node->eval();
		arg_context.clear();
		return ret;
	}
	return ReturnValue(ValueType::NONE);
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

void LispFunction::destroyTable()
{
	for (auto a : LispFunction::customizedFuncTable) {
		delete a.second.node;
	}
}
