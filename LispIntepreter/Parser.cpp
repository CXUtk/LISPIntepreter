#include "Parser.h"


Parser::Parser() : _pos(0), _code(nullptr)
{
    init();
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
	int res = _eval(_root);
	printf("%d\n", res);
}

void Parser::parseWhiteSpace()
{
	while (_code[_pos] == ' ' || _code[_pos] == '\t' || _code[_pos] == '\n'
		|| _code[_pos] == '\r' )
		_pos++;
}

int Parser::parseNumber(LispNode * node)
{
	size_t start = _pos;
	while (isdigit(_code[_pos]) || _code[_pos] == '.') {
		_pos++;
	}
	std::string str(_code + start, _pos - start);
	try {
		int num = std::stoi(str, 0, 10);
		node->type = ValueType::CONSTANT;
		node->v.value = num;
	}
	catch (std::invalid_argument a) {
		fprintf(stderr, "[Invalid number] \n%s: %s\n", a.what(), str.c_str());
		return PARSE_NUMBER_ERROR;
	}
	return PARSE_OK;
}

int Parser::parseSymbol(LispNode * node)
{
	int ret;
	size_t start = _pos;
	while (isalpha(_code[_pos])) {
		_pos++;
	}
	// �������Լ��������ȫ�ַ��ű���
	std::string str(_code + start, _pos - start);
	if (str == "define") {
		parseWhiteSpace();
		start = _pos;
		if (isalpha(_code[_pos])) {
			while (!isWhiteSpace(_code[_pos])) {
				_pos++;
			}
			node->type = ValueType::EMPTY;
			str = std::string(_code + start, _pos - start);
			auto n = new LispNode;
			n->type = ValueType::SYMBOL;
			n->v.content = new char[str.size() + 1];
			memcpy(n->v.content, str.c_str(), str.size() + 1);
			LispNode tmp;
			if ((ret = parseNumber(&tmp)) != PARSE_OK) {
				return ret;
			}
			_lookupTable[str] = tmp;

		}
	}
	return PARSE_UNKNOWN_SYMBOL;
}

int Parser::parseToken(LispNode * node) {
	if (_code[_pos] == '\0') 
		return PARSE_END;

	if (isdigit(_code[_pos]) || (_code[_pos] == '-' && isdigit(_code[_pos + 1]))) {
		return parseNumber(node);
	}

    switch (_code[_pos]){
        case '+':
		case '-':
		case '*':
		case '/':
        {
			node->type = ValueType ::M_OPERATOR;
			node->v.value = _code[_pos];
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
		case '(': {
			_pos++;
			if (_code[_pos] != ')') {
				LispNode * element = new LispNode;
				node->type = ValueType::EXPRESSION;
				parseToken(element);
				node->children.push_back(element);
				return PARSE_OK;
			}
			break;
		}
		case ')': {
			_pos++;
			return PARSE_OK;
		}
		case 'd': {
			return parseSymbol(node);
		}
    }

	if (_code[_pos] == '\0') 
		return PARSE_END;
	_pos++;
	parseWhiteSpace();
    return PARSE_OK;
}

int Parser::_eval(LispNode * node)
{
	switch (node->type)
	{
	case ValueType::EXPRESSION: {
		return _eval(node->children[0]);
	}
	case ValueType::CONSTANT: {
		return node->v.value;
	}
	case ValueType::M_OPERATOR: {
        int num = _eval(node->children[0]);
        for (int i = 1; i < node->children.size(); i++) {
            num = (this->*opFuncMap[node->v.value])(num, _eval(node->children[i]));
        }
        return num;
	}
	default:
		break;
	}
}

void Parser::init() {
    opFuncMap['+'] = &Parser::op_add;
    opFuncMap['-'] = &Parser::op_minus;
    opFuncMap['*'] = &Parser::op_multip;
    opFuncMap['/'] = &Parser::op_div;
    opFuncMap['%'] = &Parser::op_mod;
}

bool isWhiteSpace(char c)
{
	return c == ' ' || c == '\t' || c == '\n'
		|| c == '\r';
}
