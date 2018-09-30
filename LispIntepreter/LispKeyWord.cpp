#include <cassert>
#include "LispKeyWord.h"
#include "LispName.h"
#include "LispFunction.h"
#include "LispConstant.h"
#include "LispArgSlot.h"

std::set<std::string> LispKeyWord::keywordTable;


LispKeyWord::LispKeyWord() : LispNode() {
}

ReturnValue LispKeyWord::eval() {
	if (this->_name == "define") {
		return evalDefine();
	}
	else if (this->_name == "if") {
		return evalIf();
	}
	return ReturnValue(ValueType::NONE);
}

void LispKeyWord::setUpTable() {
	keywordTable.insert("define");
	keywordTable.insert("if");
	keywordTable.insert("else");
	keywordTable.insert("let");
	keywordTable.insert("lambda");
}

LispNode * LispKeyWord::fixArgs(LispNode * node, std::vector<std::string>& argset) {
    for(int i = 0; i < node->getChildrenSize(); i++){
        node->children[i] = fixArgs(node->children[i], argset);
    }
    if(node->Type() == "name"){
        auto n = (LispName *)node;
        auto name = n->getName();
        int i = 0;
        for(; i < argset.size(); i++){
            if(argset[i] == name)
                return new LispArgSlot(i);
        }
    }
    return node;
}

ReturnValue LispKeyWord::evalDefine()
{
	LispFunction::FunctionInfo info;
	if (this->children[0]->Type() == "name") {
		auto n = (LispName *)(this->children[0]);
		info.argNumber = 0;
		info.node = LispNode::copy(this->children[1]);
		LispFunction::customizedFuncTable[n->getName()] = info;
	}
	else if (this->children[0]->Type() == "node") {
		// 第一个node子节点是函数参数
		auto n = this->children[0];
		bool first = true;
		std::string name;
		int i = 0;
		info.argNumber = 0;
		std::vector<std::string> arg_set;
		for (; i < n->children.size(); i++) {
			if (n->children[i]->Type() == "name" || n->children[i]->Type() == "arg_slot") {
				if (first) {
					auto nameNode = n->children[i];
					if (nameNode->Type() == "name") {
						name = ((LispName *)(nameNode))->getName();
					}
					else {
						auto target = (LispName *)LispFunction::arg_context[((LispArgSlot*)(nameNode))->getSlot()];
						name = target->getName();
					}
					first = false;
				}
				else {
					info.argNumber++;
					arg_set.push_back(((LispName *)(n->children[i]))->getName());
				}
			}
		}
		// 第二个子节点是函数主体
		assert(this->children[1]->Type() == "node");
		info.node = LispNode::copy(this->children[1]);
		info.node = fixArgs(info.node, arg_set);
		LispFunction::customizedFuncTable[name] = info;
	}
	else {
		throw;
	}
	return ReturnValue(ValueType::NONE);
}

ReturnValue LispKeyWord::evalIf()
{
	if (this->children.size() >= 2 && this->children[0]->Type() == "function") {
		auto ret = this->children[0]->eval();
		if (ret.getType() == ValueType::INTEGER && ret.getInt() != 0) {
			return this->children[1]->eval();
		}
		if (this->children.size() > 2) {
			return this->children[2]->eval();
		}
	}
	throw;
}

