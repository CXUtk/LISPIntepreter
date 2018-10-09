#ifndef _LISP_SEMANTIC_H_
#define _LISP_SEMANTIC_H_

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
	Semantic(const Lexical& lex);
	~Semantic();

	void Analyze();
	void Display() const;

private:
	LispNode * _root;
	LispNode * _analyzedRoot;

};
#endif

