#ifndef _LISP_PARSER_H_
#define _LISP_PARSER_H_

#include <vector>
#include <map>
#include <string>
#include <stack>
#include <memory>

#include "ParseException.h"
#include "LispNode.h"


class Parser {
public:
	Parser();

	~Parser();

	void Parse(const char *str);

	void Eval();

	bool checkSucceed(const char *code, const std::string &str) const;

	enum {
		PARSE_OK,
		PARSE_NUMBER_ERROR,
		PARSE_UNKNOWN_SYMBOL,
		PARSE_END
	};

private:
	const char *_code;
	size_t _pos;
	size_t _len;

	std::stack<LispNode *> _context;
	bool breakSign = false;
	bool argMode = false;


	void init();

	void parseWhiteSpace();

	LispNode* parseNumber();

	LispNode * parseSymbol();

	void parseNode();

	int parseKeyword(LispNode **node);

	void appendElements(LispNode *node);

	LispNode * _eval(LispNode *node);

	void clearRoot();

	void clearNode(LispNode *n);

	bool isKeyword(const std::string &str);

	void displayNode(LispNode * node, int n) const;



	// int applyToChild();

};


bool isWhiteSpace(char c);

#endif 


