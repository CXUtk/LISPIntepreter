#ifndef _LISP_PARSER_H_
#define _LISP_PARSER_H_

#include <vector>
#include <map>
#include <string>
#include <stack>
#include <memory>

enum OP_CODE {
    EQ = 333,
    GREATER_EQ,
    LESS_EQ,
    NOT_EQ

};

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
    typedef int (Parser::*opfunc)(int, int);
	Parser();
	~Parser();

    std::map<int, opfunc> opFuncMap;

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
    void init();
	void parseWhiteSpace();
	int parseNumber(LispNode * node);
	int parseSymbol(LispNode * node);
    int parseToken(LispNode * node);
	int _eval(LispNode * node);

    int op_add(int a, int b) {return a + b;}
    int op_minus(int a, int b) {return a - b;}
    int op_multip(int a, int b) {return a * b;}
    int op_div(int a, int b) {return a / b;}
    int op_mod(int a, int b) {return a % b;}
};



bool isWhiteSpace(char c);

#endif 


