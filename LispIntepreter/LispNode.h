//
// Created by Chen Xujie on 9/18/18.
//

#ifndef LISPINTEPRETER_LISPNODE_H
#define LISPINTEPRETER_LISPNODE_H


#include <vector>
#include <string>

enum OP_CODE {
    GREATER_EQ = 0x100,
    LESS_EQ,
    NOT_EQ,
    LOGIC_AND,
    LOGIC_OR

};

enum class ValueType {
	INTEGER,
	DOUBLE,
	STRING,
	FUNCTION,
	NONE
};

class ReturnValue {
public:
	ReturnValue(ValueType type);
	~ReturnValue();

	void printValue() const;

private:
	ValueType _type;
	union Value
	{
		int i;
		double d;
		std::string str;
		void * func;
	};
	Value _value;
};

class LispNode {
public:

    LispNode() = default;

    virtual ~LispNode() { for (auto k : children) delete k; }

    virtual void appendChild(LispNode *node) { children.push_back(node); }

    virtual ReturnValue eval() { if (!children.empty()) return children[0]->eval(); }

    virtual std::string Type() const { return "node"; }

	size_t getChildrenSize() { return children.size(); }

	static LispNode * copy(LispNode * node);

protected:
    std::vector<LispNode *> children;
};


#endif //LISPINTEPRETER_LISPNODE_H
