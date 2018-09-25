//
// Created by Chen Xujie on 9/18/18.
//

#ifndef LISPINTEPRETER_LISPNODE_H
#define LISPINTEPRETER_LISPNODE_H


#include <vector>
#include <string>
#include "ReturnValue.h"
#include "ParseException.h"


class LispNode {
public:

    LispNode() = default;

    virtual ~LispNode() { for (auto k : children) delete k; }

    virtual void appendChild(LispNode *node) { children.push_back(node); }

    virtual ReturnValue eval() { if (!children.empty()) return children[0]->eval(); else throw ParseException("Invalid Node", "Node");}

    virtual std::string Type() const { return "node"; }

	size_t getChildrenSize() { return children.size(); }

	static LispNode * copy(LispNode * node);

protected:
    std::vector<LispNode *> children;
};


#endif //LISPINTEPRETER_LISPNODE_H
