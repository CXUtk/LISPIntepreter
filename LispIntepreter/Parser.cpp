#include "Parser.h"


Parser::Parser() : _pos(0), _code(nullptr)
{
    init();
	_root = new LispNode;
}


Parser::~Parser()
{
	clearRoot();
}

void Parser::Parse(const char * str)
{
	clearRoot();
	_root = new LispNode;
	_code = str;
	_pos = 0;
	parseWhiteSpace();
    try {
        if (parseToken(_root) == PARSE_OK) {
            Eval();
        }
    }
    catch (ParseException& ex){
        fprintf(stderr, "%s\n", ex.what());
    }

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
		int num = std::stoi(str, nullptr, 10);
		node->type = ValueType::CONSTANT;
		node->v.value = num;
	}
	catch (std::invalid_argument& a) {
        throw ParseException("Invalid Number", a.what());
		// fprintf(stderr, "[Invalid number] \n%s: %s\n", a.what(), str.c_str());
		// return PARSE_NUMBER_ERROR;
	}
	return PARSE_OK;
}

int Parser::parseSymbol(LispNode * node)
{
	int ret;
	size_t start = _pos;
	while (!isWhiteSpace(_code[_pos]) && _code[_pos] != '\0' && _code[_pos] != ')') {
		_pos++;
	}
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
			parseWhiteSpace();
			LispNode tmp;
			if ((ret = parseToken(&tmp)) != PARSE_OK) {
				return ret;
			}
			if (_lookupTable.find(str) == _lookupTable.end())
				_lookupTable[str] = tmp;

		}
		return PARSE_OK;
	}
	else {
		if (isKeyword(str)) {
			return parseKeyword(node);
		}
		else {

			if (_lookupTable.find(str) != _lookupTable.end()) {
				node->type = ValueType::SYMBOL;
				node->v.content = new char[str.size() + 1];
				memcpy(node->v.content, str.c_str(), str.size() + 1);
				return PARSE_OK;
			}
			else {
                throw ParseException("Unknown Symbol", strcat(const_cast<char *>(str.c_str()), " is not defined"));
				//fprintf(stderr, "[Unknown symbol] %s is not defined\n", str.c_str());
				//return PARSE_UNKNOWN_SYMBOL;
			}

		}
	}
	return PARSE_UNKNOWN_SYMBOL;
}

int Parser::parseToken(LispNode * node) {
	int ret;
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
		case '%':
		case '=':
		case '^':
        {
			node->type = ValueType ::M_OPERATOR;
			node->v.value = _code[_pos];
			_pos++;
			parseWhiteSpace();
			if((ret = appendElements(node)) != PARSE_OK) return ret;
            break;
        }
		case '>':
		case '<':
		case '!':
		{
			node->type = ValueType::M_OPERATOR;
			if (_code[_pos + 1] == '=') {
				switch (_code[_pos])
				{
				case '>':
					node->v.value = OP_CODE::GREATER_EQ;
					break;
				case '<':
					node->v.value = OP_CODE::LESS_EQ;
					break;
				case '!':
					node->v.value = OP_CODE::NOT_EQ;
					break;
				default:
					break;
				}
				_pos++;
			}
			else {
				node->v.value = _code[_pos];
				switch (_code[_pos])
				{
				case '!':
					node->type = ValueType::OPERATOR;
					break;
				default:
					break;
				}
			}
			_pos++;
			parseWhiteSpace();
			if ((ret = appendElements(node)) != PARSE_OK) return ret;
			break;
		}
		case '&':
		case '|': {
			node->type = ValueType::M_OPERATOR;
			if (_code[_pos + 1] == _code[_pos]) {
				if (_code[_pos] == '&')
					node->v.value = OP_CODE::LOGIC_AND;
				else 
					node->v.value = OP_CODE::LOGIC_OR;
				_pos++;
			}
			else {
				node->v.value = _code[_pos];
			}
			_pos++;
			parseWhiteSpace();
			if ((ret = appendElements(node)) != PARSE_OK) return ret;
			break;
		}
		case '~':
		{
			node->type = ValueType::OPERATOR;
			node->v.value = _code[_pos];
			_pos++;
			parseWhiteSpace();
			if ((ret = appendElements(node)) != PARSE_OK) return ret;
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
			//if (!_context.empty()) {
			//	auto top = _context.top();

			//}
			_pos++;
			return PARSE_OK;
		}
		default:
			return parseSymbol(node);
    }

	if (_code[_pos] == '\0') 
		return PARSE_OK;
	_pos++;
	parseWhiteSpace();
    return PARSE_OK;
}

int Parser::parseKeyword(LispNode * node)
{
	return 0;
}

int Parser::appendElements(LispNode * node)
{
	while (_code[_pos] != '\0' && _code[_pos] != ')') {
		int ret;
		auto element = new LispNode;
		if ((ret = parseToken(element)) != PARSE_OK) return ret;
		parseWhiteSpace();
		node->children.push_back(element);
	}
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
	case ValueType::OPERATOR: {
		if (multiOPMap.find(node->v.value) == multiOPMap.end()) {
			fprintf(stderr, "%s\n", "Invalid Operator!");
			return 0;
		}
		int num = _eval(node->children[0]);
		return (this->*multiOPMap[node->v.value])(num, 0);
	}
	case ValueType::M_OPERATOR: {
		if (multiOPMap.find(node->v.value) == multiOPMap.end()) {
			fprintf(stderr, "%s\n", "Invalid Operator!");
			return 0;
		}
        int num = _eval(node->children[0]);
        for (int i = 1; i < node->children.size(); i++) {
            num = (this->*multiOPMap[node->v.value])(num, _eval(node->children[i]));
        }
        return num;
	}
	case ValueType::SYMBOL: {
		return _eval(&_lookupTable[std::string(node->v.content)]);
	}
	default:
		return 0;
		break;
	}
}

void Parser::clearRoot()
{
	clearNode(_root);
}

void Parser::clearNode(LispNode * n)
{
	if (n->type == ValueType::EMPTY || n->children.empty()) {
		if (n->type == ValueType::SYMBOL) {
			delete[] n->v.content;
		}
		delete n;
		return;
	}
	while (!n->children.empty()) {
		for (auto c : n->children) {
			clearNode(c);
            n->children.pop_back();
		}
	}
}

bool Parser::isKeyword(const std::string & str)
{
	return false;
}

void Parser::init() {
    multiOPMap['+'] = &Parser::op_add;
    multiOPMap['-'] = &Parser::op_minus;
    multiOPMap['*'] = &Parser::op_multip;
    multiOPMap['/'] = &Parser::op_div;
    multiOPMap['%'] = &Parser::op_mod; 
	multiOPMap['>'] = &Parser::op_greater;
	multiOPMap['<'] = &Parser::op_less;
	multiOPMap['='] = &Parser::op_eq;
	multiOPMap['&'] = &Parser::op_AND;
	multiOPMap['|'] = &Parser::op_OR;
	multiOPMap['^'] = &Parser::op_XOR;
	multiOPMap['!'] = &Parser::op_NOT;
	multiOPMap['~'] = &Parser::op_INV;
	multiOPMap[OP_CODE::GREATER_EQ] = &Parser::op_GE;
	multiOPMap[OP_CODE::LESS_EQ] = &Parser::op_LE;
	multiOPMap[OP_CODE::NOT_EQ] = &Parser::op_NE;
}

bool isWhiteSpace(char c)
{
	return c == ' ' || c == '\t' || c == '\n'
		|| c == '\r';
}
