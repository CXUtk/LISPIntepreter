#ifndef _LISP_LEXICAL_H_
#define _LISP_LEXICAL_H_

#include <vector>
#include <map>
#include <string>
#include <stack>
#include <memory>

#include "ParseException.h"
#include "LispNode.h"

class Lexical
{
public:
	Lexical();
	~Lexical();

	void Parse(const char *str);
	void Display() const;
	LispNode * GetRoot() const { return _root; }

private:
    char *_code;
	size_t _pos;
	size_t _len;
	LispNode * _root;
	std::stack<LispNode *> _context;

	char get() const { return _code[_pos]; }
	void displayNode(LispNode * node, int n) const;
	void parseNext();
	void parseWhiteSpace();
	LispNode * parseNumber();
};
#endif

