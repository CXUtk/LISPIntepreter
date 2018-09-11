#include "Parser.h"



Parser::Parser() : _pos(0), _code(nullptr)
{
	_root = new LispNode;
}


Parser::~Parser()
{
}

void Parser::Parse(const char * str)
{
	_code = str;
	_pos = 0;
	parseWhiteSpace();
    while(parseToken(_root) == PARSE_OK && _code[_pos] != '\0'){
    }
	Eval();

}

void Parser::Eval()
{
	_eval(_root);
}

void Parser::parseWhiteSpace()
{
	while (_code[_pos] == ' ' || _code[_pos] == '\t' || _code[_pos] == '\n'
		|| _code[_pos] == '\r' )
		_pos++;
}

int Parser::parseToken(LispNode * node) {
	if (_code[_pos] == '\0') return PARSE_END;
	if (isdigit(_code[_pos]) || (_code[_pos] == '-' && isdigit(_code[_pos + 1]))) {
		size_t start = _pos;
		while (isdigit(_code[_pos]) || _code[_pos] == '.') {
			_pos++;
		}
		std::string str(_code + start, _pos - start);
		try {
			int num = std::stoi(str, 0, 10);
			node->type = ValueType::CONSTANT;
			node->value = num;
		}
		catch (std::invalid_argument a) {
			fprintf(stderr, "[Invalid number] \n%s: %s\n", a.what(), str.c_str());
			return PARSE_NUMBER_ERROR;
		}
		return PARSE_OK;
	}

    switch (_code[_pos]){
        case '+':
		case '-':
		case '*':
		case '/':
        {
			node->type = ValueType ::M_OPERATOR;
			node->value = _code[_pos];
			_pos++;
			parseWhiteSpace();
			while (_code[_pos] != '\0' && _code[_pos] != ')') {
				LispNode * element = new LispNode;
				int ret;
				if((ret = parseToken(element)) != PARSE_OK) return ret;
				parseWhiteSpace();
				node->children.push_back(element);
			}
            break;
        }
    }
	if (_code[_pos] == '\0') return PARSE_END;
	_pos++;
	parseWhiteSpace();
    return PARSE_OK;
}

void Parser::appendElements(LispNode & op)
{
}

void Parser::_eval(LispNode * node)
{
	switch (node->type)
	{
	case ValueType::M_OPERATOR: {
		if (node->value == '+') {
			int sum = 0;
			for (int i = 0; i < node->children.size(); i++) {
				sum += node->children[i]->value;
			}
			printf("%d\n", sum);
		}
		else if (node->value == '-') {
			int num = node->children[0]->value;
			for (int i = 1; i < node->children.size(); i++) {
				num -= node->children[i]->value;
			}
			printf("%d\n", num);
		}
		else if (node->value == '*') {
			int sum = 1;
			for (int i = 0; i < node->children.size(); i++) {
				sum *= node->children[i]->value;
			}
			printf("%d\n", sum);
		}
		else if (node->value == '/') {
			int num = node->children[0]->value;
			for (int i = 1; i < node->children.size(); i++) {
				num /= node->children[i]->value;
			}
			printf("%d\n", num);
		}
		break;
	}
	default:
		break;
	}
}
