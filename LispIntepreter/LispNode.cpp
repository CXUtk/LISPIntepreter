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
		n = new LispNode();
	}
	else if (node->Type() == "name") {
		auto p = (LispName *)node;
		n = new LispName(p->getName());
	}
	else if (node->Type() == "keyword") {
		auto p = (LispKeyWord *)node;
		n = new LispKeyWord(*p);
	}
	else if (node->Type() == "function") {
		auto p = (LispFunction *)node;
		n = new LispFunction(*p);
	}
	else if (node->Type() == "constant") {
		auto p = (LispConstant *)node;
		n = new LispConstant(*p);
	}
	else {
		throw std::invalid_argument("Unknown Node type");
	}
	for (int i = 0; i < n->getChildrenSize(); i++) {
		n->appendChild(LispNode::copy(node->children[i]));
	}
	return n;
}
