//
// Created by Chen Xujie on 9/18/18.
//

#include "LispNode.h"
#include "LispConstant.h"
#include "LispName.h"
#include "LispKeyWord.h"
#include "LispFunction.h"

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
		z->setArgumentNum(p->getArgumentNum());
		n = z;
	}
	else if (node->Type() == "constant") {
		auto p = (LispConstant *)node;
		n = new LispConstant(*p);
	}
	else {
		throw std::invalid_argument("Unknown Node type");
	}
	for (int i = 0; i < node->getChildrenSize(); i++) {
		n->appendChild(LispNode::copy(node->children[i]));
	}
	return n;
}
