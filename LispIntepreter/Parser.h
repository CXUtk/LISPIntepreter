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
	// Rule: \w+.*\s
	SYMBOL,
	// Rule: \".*\"
	STRING,
	// Rule: define (<symbol> [<expression>]) (<expression>)\n <expression>
	FUNCTION,
    EMPTY
};

class LispNode {
public:
	ValueType type;
	union vl {
		int value;
		char * content;
		vl() {
			value = 0;
			content = 0;
		}
	} v;
	std::vector<LispNode *> children;

	LispNode() : type(ValueType::EMPTY){}
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
		PARSE_UNKNOWN_SYMBOL,
		PARSE_END
    };

private:
	const char * _code;
	size_t _pos;
    std::map<std::string, LispNode> _lookupTable;
	LispNode * _root;
	void parseWhiteSpace();
	int parseNumber(LispNode * node);
	int parseSymbol(LispNode * node);
    int parseToken(LispNode * node);
	int _eval(LispNode * node);
};

bool isWhiteSpace(char c);

#endif 


