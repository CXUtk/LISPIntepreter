#include "Semantic.h"
#include "LispFunction.h"
#include "LispConstant.h"
#include "LispKeyWord.h"
#include "LispName.h"
#include <cassert>


Semantic::Semantic() : _root(nullptr), _analyzedRoot(nullptr)
{
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
}

LispNode * Semantic::_analyze()
{
	LispNode * node = _context.back();
	if (node->Type() == "node") {
		_context.push_back(node->children[0]);
		return _analyze();
	}
	else if (node->Type() == "name") {
		LispName * lispName = (LispName *) node;
		auto name = lispName->getName();
		if (LispKeyWord::keywordTable.find(name) != LispKeyWord::keywordTable.end()) {
			auto n = new LispKeyWord;
			n->setName(name);
			// TODO: appendElements(n);
			return n;
		}
		else {
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
			_context.pop_back();
			// TODO: appendElements(n);
			return n;
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

