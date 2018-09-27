#include "Parser.h"
#include "LispFunction.h"
#include "LispConstant.h"
#include "LispKeyWord.h"
#include "LispName.h"


Parser::Parser() : _pos(0), _code(nullptr) {
	init();
	_root = new LispNode;
}


Parser::~Parser() {
	clearRoot();
}

void Parser::Parse(const char *str) {
	clearRoot();
	_root = nullptr;
	_code = str;
	_pos = 0;
	_len = strlen(_code);
	parseWhiteSpace();
	try {
		_context.push(new LispNode);
		parseNode();
		if (_context.size() == 1) {
			_root = _context.top();
			_context.pop();
		}
		else {
			throw ParseException("Context stack not match", "stack");
		}
		Eval();
	}
	catch (ParseException &ex) {
		fprintf(stderr, "%s\n", ex.what());
	}

}

void Parser::Eval() {
	auto ret = _root->eval();
	ret.printValue();
}

void Parser::parseWhiteSpace() {
	while (_code[_pos] == ' ' || _code[_pos] == '\t' || _code[_pos] == '\n'
		|| _code[_pos] == '\r')
		_pos++;
}

LispNode * Parser::parseNumber() {
	size_t start = _pos;
	while (isdigit(_code[_pos]) || _code[_pos] == '.') {
		_pos++;
	}
	std::string str(_code + start, _pos - start);
	try {
		auto node = new LispConstant;
		int num = std::stoi(str, nullptr, 10);
		node->setNumber(num);
		return node;
	}
	catch (std::invalid_argument &a) {
		throw ParseException("Invalid Number", a.what());
		// fprintf(stderr, "[Invalid number] \n%s: %s\n", a.what(), str.c_str());
		// return PARSE_NUMBER_ERROR;
	}
}

LispNode * Parser::parseSymbol() {
	size_t start = _pos;
	while (!isWhiteSpace(_code[_pos]) && _code[_pos] != '\0' && _code[_pos] != ')') {
		_pos++;
	}
	std::string str(_code + start, _pos - start);
	if (LispKeyWord::keywordTable.find(str) != LispKeyWord::keywordTable.end()) {
		auto n = new LispKeyWord;
		n->setName(str);
		appendElements(n);
		return n;
	}
	else if (LispFunction::customizedFuncTable.find(str) != LispFunction::customizedFuncTable.end()) {
		auto n = new LispFunction;
		n->setName(str);
		appendElements(n);
		return n;
	}
	else {
		auto n = new LispName(str);
		return n;
	}
}

void Parser::parseNode() {

	auto parent = _context.top();
	LispNode * node;
	if (_code[_pos] == '\0') {
		_context.pop();
	}
	if (isdigit(_code[_pos]) || (_code[_pos] == '-' && isdigit(_code[_pos + 1]))) {
		parent->appendChild(parseNumber());
		return;
	}
	else {
		switch (_code[_pos]) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '=':
		case '^': {
			node = new LispFunction;
			auto n = (LispFunction *)node;
			n->setName(_code[_pos]);
			appendElements(node);
			break;
		}
		case '>':
		case '<':
		case '!': {
			node = new LispFunction;
			auto n = (LispFunction *)(node);
			if (_code[_pos + 1] == '=') {
				switch (_code[_pos]) {
				case '>':
					n->setName(">=");
					break;
				case '<':
					n->setName("<=");
					break;
				case '!':
					n->setName("!=");
					break;
				default:
					break;
				}
				_pos++;
			}
			else {
				n->setName(_code[_pos]);
				switch (_code[_pos]) {
				case '!':
					n->setArgumentNum(1);
					break;
				default:
					break;
				}
			}
			appendElements(n);
			break;
		}
		case '&':
		case '|': {
			node = new LispFunction;
			auto n = (LispFunction *)(node);
			if (_code[_pos + 1] == _code[_pos]) {
				if (_code[_pos] == '&')
					n->setName("&&");
				else
					n->setName("||");
				_pos++;
			}
			else {
				n->setName(_code[_pos]);
			}
			appendElements(n);
			break;
		}
		case '~': {
			node = new LispFunction;
			auto n = (LispFunction *)(node);
			n->setArgumentNum(1);
			n->setName(_code[_pos]);
			appendElements(n);
			break;
		}
		case '(': {
			if (_code[_pos + 1] != ')') {
				auto n = new LispNode;
				_context.push(n);
				appendElements(n);
				parent->appendChild(n);
				return;
			}
			break;
		}
		case ')': {
			_context.pop();
			_pos++;
			return;
		}
		default: {
			node = parseSymbol();
		}
		}
	}
	parent->appendChild(node);
}

int Parser::parseKeyword(LispNode **node) {
	return 0;
}

void Parser::appendElements(LispNode *node) {
	_context.push(node);
	_pos++;
	parseWhiteSpace();
	while (_code[_pos] != '\0') {
		parseNode();
		if (_code[_pos] == '\0')
			break;
		parseWhiteSpace();
	}
	_context.pop();
}

ReturnValue Parser::_eval(LispNode *node) {
	return node->eval();
	/*    switch (node->type) {
			case ValueType::EXPRESSION: {
				return _eval(node->children[0]);
			}
			case ValueType::CONSTANT: {
				return node->v.value;
			}
			case ValueType::OPERATOR: {
				if (fuctionSymbolMap.find(node->v.value) == fuctionSymbolMap.end()) {
					fprintf(stderr, "%s\n", "Invalid Operator!");
					return 0;
				}
				int num = _eval(node->children[0]);
				return (this->*fuctionSymbolMap[node->v.value])(num, 0);
			}
			case ValueType::M_OPERATOR: {
				if (fuctionSymbolMap.find(node->v.value) == fuctionSymbolMap.end()) {
					fprintf(stderr, "%s\n", "Invalid Operator!");
					return 0;
				}

				int num = _eval(node->children[0]);
				for (int i = 1; i < node->children.size(); i++) {
					num = (this->*fuctionSymbolMap[node->v.value])(num, _eval(node->children[i]));
				}
				return num;
			}
			case ValueType::SYMBOL: {
				return _eval(&_lookupTable[std::string(node->v.content)]);
			}
			default:
				return 0;
				break;
		}*/
}

void Parser::clearRoot() {
	delete _root;
}

void Parser::clearNode(LispNode *n) {

}

bool Parser::isKeyword(const std::string &str) {
	return false;
}

void Parser::init() {
	LispFunction::setUpTable();
	LispKeyWord::setUpTable();
}



bool isWhiteSpace(char c) {
	return c == ' ' || c == '\t' || c == '\n'
		|| c == '\r';
}
