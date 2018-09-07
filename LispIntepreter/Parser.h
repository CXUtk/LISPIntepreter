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
	STRING,
    EMPTY
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
    enum{
        PARSE_OK
    };

private:
	const char * _code;
	size_t _pos;
    std::map<std::string, LispValue> _lookupTable;
	void parseWhiteSpace();
    int parseToken();
    void appendElements(LispValue & op);
};

#endif 


