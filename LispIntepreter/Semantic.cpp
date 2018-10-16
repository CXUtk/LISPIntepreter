#include "Semantic.h"
#include "LispFunction.h"
#include "LispConstant.h"
#include "LispKeyWord.h"
#include "LispName.h"

#include <cassert>


Semantic::Semantic() : _root(nullptr), _analyzedRoot(nullptr)
{
	LispFunction::setUpTable();
	LispKeyWord::setUpTable();
}

Semantic::~Semantic()
{
	if (_analyzedRoot) {
		delete _analyzedRoot;
	}
}

void Semantic::Analyze(const Lexical& lex)
{
	_root = lex.GetRoot();
	_analyzedRoot = new LispNode;
	_context.push_back(_root->children[0]);
	_analyzedRoot->appendChild(_analyze());
	_context.pop_back();
	assert(_context.empty());
	//_analyze();
}

void Semantic::Display() const
{
	LispNode::display(_analyzedRoot, 0);
	auto ret = _analyzedRoot->eval();
	ret.printValue();
}

LispNode * Semantic::_analyze()
{
	LispNode * node = _context.back();
	if (node->Type() == "node") {
		_context.push_back(node->children[0]);
		auto ret = _analyze();
		_context.pop_back();
		return ret;
	}
	else if (node->Type() == "name") {
		LispName * lispName = (LispName *) node;
		auto name = lispName->getName();
		if (LispKeyWord::keywordTable.find(name) != LispKeyWord::keywordTable.end()) {
			auto n = new LispKeyWord;
			n->setName(name);
			auto prevNode = _context[_context.size() - 2];
			if (name == "define") {
				for (int i = 1; i < prevNode->children.size(); i++) {
					if (i == 1) {
						n->appendChild(LispNode::copy(prevNode->children[1]));
						if (prevNode->children[1]->children[0]->Type() != "name") {
							throw ParseException("Function name", "Cannot parse function name");
						}
						auto funcName = (LispName *)prevNode->children[1]->children[0];
						FunctionInfo info;
						info.argNumber = prevNode->children[1]->getChildrenSize() - 1;
						info.node = nullptr;
						LispFunction::customizedFuncTable[funcName->getName()] = info;
					}
					else {
						auto args = new LispNode;
						_context.push_back(prevNode->children[i]);
						args->appendChild(_analyze());
						n->appendChild(args);
						_context.pop_back();
					}
				}
			}
			else {
				for (int i = 1; i < prevNode->children.size(); i++) {
					_context.push_back(prevNode->children[i]);
					n->appendChild(_analyze());
					_context.pop_back();
				}
			}
			// TODO: appendElements(n);
			return n;
		}
		else if(LispFunction::customizedFuncTable.find(name) != LispFunction::customizedFuncTable.end()
			|| LispFunction::opFuncTable.find(name) != LispFunction::opFuncTable.end()) {
			// (LispFunction::customizedFuncTable.find(name) != LispFunction::customizedFuncTable.end())
			auto n = new LispFunction;
			n->setName(name);
			auto prevNode = _context[_context.size() - 2];
			for (auto a : prevNode->children) {
				if (a != node) {
					_context.push_back(a);
					n->appendChild(_analyze());
					_context.pop_back();
				}
			}
			// TODO: appendElements(n);
			return n;
		}
		else {
			return new LispName(name);
		}
	}
	else if (node->Type() == "constant") {
		auto n = new LispConstant;
		auto orig = (LispConstant *) node;
		n->setNumber(orig->getNumber());
		return n;
	}
	return new LispNode;
}

