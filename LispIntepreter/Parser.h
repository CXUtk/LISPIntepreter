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
	LispNode *_root;
	std::stack<LispNode *> _context;
	bool argumentMode = false;


	void init();

	void parseWhiteSpace();

	LispNode* parseNumber();

	LispNode * parseSymbol();

	int parseNext();

	void parseNode();

	int parseKeyword(LispNode **node);

	void appendElements(LispNode *node);

	ReturnValue _eval(LispNode *node);

	void clearRoot();

	void clearNode(LispNode *n);

	bool isKeyword(const std::string &str);

	// int applyToChild();

};


bool isWhiteSpace(char c);

#endif 


