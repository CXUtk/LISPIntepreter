#ifndef _LISP_LEXICAL_H_
#define _LISP_LEXICAL_H_
/*
	文法解析器，作用是把字符串组装成符号树
	以括号作为节点分割
	符号树用于接下来的语义解析->语法树
*/

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

