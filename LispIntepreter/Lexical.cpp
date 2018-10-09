#include "Lexical.h"
#include "LispConstant.h"
#include "LispName.h"

bool isWhiteSpace(int c) {
	return c == ' ' || c == '\t' || c == '\n'
		|| c == '\r';
}


Lexical::Lexical() : _code(nullptr), _pos(0), _len(0)
{
}


Lexical::~Lexical()
{
	delete _root;
}

void Lexical::Parse(const char * str)
{
	_code = str;
	_len = strlen(str);
	_pos = 0;
	_root = new LispNode;
	_context.push(_root);
	while (_pos < _len) {
		parseNext();
	}
	_context.pop();
	if (!_context.empty()) {
		while (!_context.empty()) {
			free(_context.top());
			_context.pop();
		}
		throw ParseException("Stack", "Stack is not empty at end");
	}
}

void Lexical::Display() const
{
	displayNode(_root, 0);
}

void Lexical::displayNode(LispNode * node, int n) const
{
	for (int i = 0; i < n * 4; i++) {
		printf("-");
	}
	printf("(%s) [%s]\n", node->Type().c_str(), node->Description().c_str());
	for (int i = 0; i < node->getChildrenSize(); i++) {
		displayNode(node->children[i], n + 1);
	}
}

LispNode * Lexical::parseNumber() {
	size_t start = _pos;
	while (isdigit(get()) || get() == '.') {
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

void Lexical::parseNext()
{
	parseWhiteSpace();
	char c = get();
	if (c == '(') {
		_context.push(new LispNode);
		_pos++;
		return;
	}
	if (c == ')') {
		auto node = _context.top();
		_context.pop();
		_context.top()->appendChild(node);
		_pos++;
		return;
	}
	if (isdigit(c) || (c == '-' && isdigit(_code[_pos + 1]))) {
		_context.top()->appendChild(parseNumber());
		return;
	}

	size_t start = _pos;
	while (!isWhiteSpace(_code[_pos]) && _code[_pos] != '\0' && _code[_pos] != ')') {
		_pos++;
	}
	std::string str(_code + start, _pos - start);
	auto node = new LispName(str);
	_context.top()->appendChild(node);
}

void Lexical::parseWhiteSpace()
{
	char c = get();
	while (isWhiteSpace(c)) {
		_pos++;
		c = get();
	}
}
