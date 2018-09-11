#ifndef _LISP_PARSER_H_
#define _LISP_PARSER_H_

#include <vector>
#include <map>
#include <string>
#include <stack>
#include <memory>


enum class ValueType {
	// Rule: (<op> <number> <number> ...)
	M_OPERATOR,
	// Rule: (<op> <number>)
	OPERATOR,
	EXPRESSION,
	// Rule: REG -> (-)?[0-9]+(.)?[0-9]+
	CONSTANT,
	STRING,
    EMPTY
};

class LispNode {
public:
	ValueType type;
	int value;
	std::vector<LispNode *> children;

	LispNode() : value(0), type(ValueType::EMPTY){}
};

class Parser
{
public:
	Parser();
	~Parser();

	void Parse(const char * str);
	void Eval();
	enum {
		PARSE_OK,
		PARSE_NUMBER_ERROR,
		PARSE_END
    };

private:
	const char * _code;
	size_t _pos;
    std::map<std::string, LispNode> _lookupTable;
	LispNode * _root;
	void parseWhiteSpace();
    int parseToken(LispNode * node);
    void appendElements(LispNode & op);
	void _eval(LispNode * node);
};

#endif 


