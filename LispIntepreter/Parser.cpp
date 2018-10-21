#include "Parser.h"
#include "LispFunction.h"
#include "LispConstant.h"
#include "LispKeyWord.h"
#include "LispName.h"
#include "Lexical.h"
#include "Semantic.h"

Parser::Parser() : _pos(0), _code(nullptr) {
	init();
    //_root = new LispNode;
}


Parser::~Parser() {
	clearRoot();
}

void Parser::Parse(const char *str) {
	try {
        _code = str;
		Lexical lex;
		lex.Parse(str);
		Semantic sem;
		sem.Analyze(lex);
		sem.Display();
	}
	catch (ParseException &ex) {
		fprintf(stderr, "%s\n", ex.what());
	}

}

void Parser::Eval() {
    //auto ret = _root->eval();
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
		if (str == "define") {
			argMode = true;
		}
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
			n->setName(_code[_pos]);
			appendElements(n);
			break;
		}
		case '(': {
			if (!argMode) {
				_pos++;
				return;
			}
			if (_code[_pos + 1] != ')') {
				auto n = new LispNode; 
				_context.push(n);
				_pos++;
				parseWhiteSpace();
				while (_code[_pos] != '\0' && _pos < _len) {
					parseNode();
					if (_code[_pos] == '\0' || breakSign) {
						breakSign = false;
						break;
					}
					parseWhiteSpace();
				}
				_context.pop();
				parent->appendChild(n);
				return;
			}
			break;
		}
		case ')': {
			if(argMode){
				argMode = false;
			}
			breakSign = true;
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
	while (_code[_pos] != '\0' && _pos < _len) {
		parseNode();
		if (_code[_pos] == '\0' || breakSign) {
			breakSign = false;
			break;
		}
		parseWhiteSpace();
	}
	_context.pop();
}

LispNode * Parser::_eval(LispNode *node) {
	return node->eval();
}

void Parser::clearRoot() {
    // delete _root;
}

void Parser::clearNode(LispNode *n) {

}

bool Parser::isKeyword(const std::string &str) {
	return false;
}

void Parser::displayNode(LispNode * node, int n) const
{
	for (int i = 0; i < n * 4; i++) {
		printf(" ");
	}
	printf("(%s) [%s]\n", node->Type().c_str(), node->Description().c_str());
	for (int i = 0; i < node->getChildrenSize(); i++) {
		displayNode(node->children[i], n + 1);
	}
}

void Parser::init() {
	LispFunction::setUpTable();
	LispKeyWord::setUpTable();
}

bool Parser::checkSucceed(const char *code, const std::string &str) const {
	LispNode * res = nullptr;
	Lexical lex;
	Semantic sem;
    try {
        lex.Parse(code);
        sem.Analyze(lex);
		sem.Display();
        res = sem.GetRoot()->eval();
		res->getVal();
    }
    catch (ParseException &ex) {
        fprintf(stderr, "%s\n", ex.what());
    }
	return LispNode::checkMatch(res, str);

}


bool isWhiteSpace(char c) {
	return c == ' ' || c == '\t' || c == '\n'
		|| c == '\r';
}
