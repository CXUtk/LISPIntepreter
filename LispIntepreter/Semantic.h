#ifndef _LISP_SEMANTIC_H_
#define _LISP_SEMANTIC_H_
/*
	语义解析，作用是把符号树解析成语法树
	比如(* 9 9)这样的表达式就需要从：
	--*
	--9
	--9
	这样的符号树解析成
	*【Function】
	--9【Constant】
	--9【Constant】
	这样的语法树，给每个节点赋予意义
*/

#include <vector>
#include <map>
#include <string>
#include <stack>
#include <memory>

#include "ParseException.h"
#include "LispNode.h"
#include "Lexical.h"
class Semantic
{
public:
	Semantic();
	~Semantic();

	void Analyze(const Lexical& lex);
	void Display() const;

	LispNode *GetRoot() const { return _analyzedRoot; }

private:
	LispNode * _root;
	LispNode * _analyzedRoot;
	std::vector<LispNode *> _context;
	std::vector<std::vector<std::string>> _localNameTable;

	LispNode * _analyze();

};
#endif

