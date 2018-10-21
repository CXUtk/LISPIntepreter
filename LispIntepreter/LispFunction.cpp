//
// Created by Chen Xujie on 9/18/18.
//

#include "LispFunction.h"
#include "ParseException.h"
#include "LispArgSlot.h"
#include "LispConstant.h"
#include "Deleter.h"


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

LispNode * LispFunction::eval() {
	if (opFuncTable.find(funcName) != opFuncTable.end()) {
		// ������Ѿ���������㺯���Լ�������
		if (getArgumentNum() > 0 && (getArgumentNum() != children.size() || children.size() == 0)) {
			throw ParseException("Invalid argument number", "");
		}
		LispNode * n = children[0]->eval();
		if (n->Type() != "constant") {
			throw ParseException("Invalid operation", "Eval: cannot use math operations with non-constant node");
		}
		LispConstant * num = (LispConstant *)n;
		if (getArgumentNum() == 1) {
			auto n = (*opFuncTable[funcName])(num->getNumber(), 0);
			LispConstant * res = (LispConstant *)Deleter::getCopy(this);
			res->setNumber(n);
			return res;
		}
		for (int i = 1; i < children.size(); i++) {
			auto a = num->getNumber();
			auto b = (LispConstant *)children[i]->eval();
			num->setNumber((*opFuncTable[funcName])(a, b->getNumber()));
		}
		return num;
	}
	else if (customizedFuncTable.find(funcName) != customizedFuncTable.end()) {
		// ������Զ���ĺ���
		auto n = customizedFuncTable[funcName];
		if (n.argNumber > 0 && getArgumentNum() != n.argNumber) {
			throw ParseException("Invalid argument number", "");
		}
		// ��������б�
		if(n.argNumber > 0){
			for (auto c : children) {
				if (c->Type() == "function") {
					auto ret = c->eval();
					if (ret->Type() == "constant") {
						c = new LispConstant(*(LispConstant *)ret);
					}
				}
				arg_context.push_back(c);
			}
		}
		auto ret = customizedFuncTable[funcName].node->eval();
		for (int i = 0; i < getChildrenSize(); i++)
			arg_context.pop_back();
		return ret;
	}
	return this;
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
