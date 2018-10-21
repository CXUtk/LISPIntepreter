//
// Created by Chen Xujie on 9/18/18.
//

#ifndef LISPINTEPRETER_LISPNODE_H
#define LISPINTEPRETER_LISPNODE_H


#include <vector>
#include <string>
#include "ParseException.h"

class LispConstant;

class LispNode {
public:

    LispNode() = default;

    virtual ~LispNode() { for (auto k : children) delete k; }

    virtual void appendChild(LispNode *node) { children.push_back(node); }

    virtual LispNode * eval() { if (!children.empty()) return children[0]->eval(); else throw ParseException("Invalid Node", "Node");}

    virtual std::string Type() const { return "node"; }

	virtual std::string Description() const {
		return "NODE";
	}

	virtual std::string getVal() const { return "None"; }

	void Print() const { printf("%s\n", getVal().c_str()); }

	size_t getChildrenSize() { return children.size(); }


	static bool checkMatch(LispNode * node, const std::string& str);

	static LispNode * copy(LispNode * node);

	static void display(LispNode * node, int n);




    std::vector<LispNode *> children;
};


#endif //LISPINTEPRETER_LISPNODE_H
