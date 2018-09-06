#ifndef _LISP_PARSER_H_
#define _LISP_PARSER_H_
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <memory>




class Parser
{
public:
	Parser();
	~Parser();

	void Parse(const char * str);

private:

};

#endif // !_LISP_PARSER_H_


