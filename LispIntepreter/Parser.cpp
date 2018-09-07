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
    while(parseToken() == PARSE_OK){

    }

}

void Parser::parseWhiteSpace()
{
	while (_code[_pos] == ' ' || _code[_pos] == '\t' || _code[_pos] == '\n' || _code[_pos] == '\r')
		_pos++;
}

int Parser::parseToken() {
    LispValue value;
    value.type = ValueType::EMPTY;
    switch (_code[_pos]){
        case '+':
        {
            value.type = ValueType ::OPERATOR;
            value.value = '+';
            break;
        }
    }
    if(value.type == ValueType::OPERATOR){

    }
    return PARSE_OK;
}
