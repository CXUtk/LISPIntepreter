//
// Created by Chen Xujie on 9/18/18.
//

#include "LispNode.h"
#include "LispConstant.h"
#include "LispName.h"
#include "LispKeyWord.h"
#include "LispFunction.h"
#include "LispArgSlot.h"

bool LispNode::checkMatch(LispNode * node, const std::string & str)
{
	if (!node) {
		return str == "Error";
	}
	char buf[1024];
	if (!node) {
		return str == "None";
	}
	return str == node->getVal();
}

LispNode * LispNode::copy(LispNode * node)
{
	LispNode * n = nullptr;
	if (node->Type() == "node") {
		n = new LispNode;
	}
	else if (node->Type() == "name") {
		auto p = (LispName *)node;
		auto z = new LispName(p->getName());
		n = z;
	}
	else if (node->Type() == "keyword") {
		auto p = (LispKeyWord *)node;
		auto z = new LispKeyWord;
		z->setName(p->getName());
		n = z;
	}
	else if (node->Type() == "function") {
		auto p = (LispFunction *)node;
		auto z = new LispFunction;
		z->setName(p->getName());
		n = z;
	}
	else if (node->Type() == "constant") {
		auto p = (LispConstant *)node;
		n = new LispConstant(*p);
	}
	else if (node->Type() == "arg_slot") {
		auto p = (LispArgSlot *)node;
		n = LispNode::copy(LispFunction::arg_context[p->getSlot()]);
	}
	else {
		throw std::invalid_argument("Unknown Node type");
	}
	for (int i = 0; i < node->getChildrenSize(); i++) {
		n->appendChild(LispNode::copy(node->children[i]));
	}
	return n;
}

void LispNode::display(LispNode * node, int n)
{
	for (int i = 0; i < n * 4; i++) {
		printf("-");
	}
	printf("(%s) [%s]\n", node->Type().c_str(), node->Description().c_str());
	for (int i = 0; i < node->getChildrenSize(); i++) {
		display(node->children[i], n + 1);
	}
}