#ifndef _LISP_PARSER_H_
#define _LISP_PARSER_H_
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <memory>


enum class ValueType {
	OPERATOR,
	EXPRESSION,
	CONSTANT,
	STRING
};

class LispValue {
public:
	ValueType type;
	int value;
	std::vector<LispValue *> children;
};

class Parser
{
public:
	Parser();
	~Parser();

	void Parse(const char * str);

private:
	const char * _code;
	size_t _pos;
	void parseWhiteSpace();
};

#endif 


