#include "Parser.h"



Parser::Parser() : _pos(0), _code(nullptr)
{
}


Parser::~Parser()
{
}

void Parser::Parse(const char * str)
{
	_code = str;
	_pos = 0;
	parseWhiteSpace();
}

void Parser::parseWhiteSpace()
{
	while (_code[_pos] == ' ' || _code[_pos] == '\t' || _code[_pos] == '\n' || _code[_pos] == '\r')
		_pos++;
}
