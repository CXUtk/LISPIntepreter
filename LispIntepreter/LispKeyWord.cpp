#include <cassert>
#include "LispKeyWord.h"
#include "LispName.h"
#include "LispFunction.h"
#include "LispConstant.h"
#include "LispArgSlot.h"

std::set<std::string> LispKeyWord::keywordTable;


LispKeyWord::LispKeyWord() : LispNode() {
}

LispNode * LispKeyWord::eval() {
	if (this->_name == "define") {
		return evalDefine();
	}
	else if (this->_name == "if") {
		return evalIf();
	}
	return this;
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
                return new LispArgSlot(argset.size() - i - 1);
        }
    }
    return node;
}

LispNode * LispKeyWord::evalDefine() {
	assert(this->children[0]->Type() == "node");
	FunctionInfo info;
	// ��һ��node�ӽڵ��Ǻ�������
	auto n = this->children[0];
	std::string name;
	int i = 0;
	info.argNumber = 0;
	std::vector<std::string> arg_set;
	for (; i < n->children.size(); i++) {
		if (n->children[i]->Type() == "name" || n->children[i]->Type() == "arg_slot") {
			if (i == 0) {
				auto nameNode = n->children[i];
				if (nameNode->Type() == "name") {
					name = ((LispName *) (nameNode))->getName();
				}
			}
			else {
				arg_set.push_back(((LispName *) (n->children[i]))->getName());
			}
		}
	}
	// �ڶ����ӽڵ��Ǻ�������
	assert(this->children[1]->Type() == "node");
	info.node = LispNode::copy(this->children[1]);
	info.node = fixArgs(info.node, arg_set);
	LispFunction::customizedFuncTable[name].node = info.node;
    LispNode::display(info.node, 0);
	return this;
}

LispNode * LispKeyWord::evalIf()
{
	if (this->children.size() >= 2 && this->children[0]->Type() == "function") {
		auto ret = this->children[0]->eval();
		if (ret->Type() == "constant" && ((LispConstant *)(ret)) ->getNumber() != 0) {
			return this->children[1]->eval();
		}
		if (this->children.size() > 2) {
			return this->children[2]->eval();
		}
	}
	throw;
}

