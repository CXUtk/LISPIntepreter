#include <cassert>
#include "LispKeyWord.h"
#include "LispName.h"
#include "LispFunction.h"
#include "LispConstant.h"

std::set<std::string> LispKeyWord::keywordTable;


LispKeyWord::LispKeyWord() : LispNode() {
}

ReturnValue LispKeyWord::eval() {
	if (this->_name == "define") {
		LispFunction::FunctionInfo info;
		if (this->children[0]->Type() == "name") {
			auto n = (LispName *)(this->children[0]);
			info.argNumber = 0;
			info.node = LispNode::copy(this->children[1]);
			LispFunction::customizedFuncTable[n->getName()] = info;
		}
		else if (this->children[0]->Type() == "node") {
			auto n = this->children[0];
			bool first = true;
			std::string name;
			int i = 0;
			for (; i < n->children.size(); i++) {
				info.argNumber = 0;
				if (n->children[i]->Type() == "name") {
					if (first) {
						auto nameNode = n->children[i];
						name = ((LispName *)(nameNode))->getName();
						first = false;
					}
					else
						info.argNumber++;
				}
			}
			assert(this->children[i]->Type() == "node");
			info.node = LispNode::copy(this->children[i]);
			LispFunction::customizedFuncTable[name] = info;
		}
		else {
			throw;
		}
	}
	return ReturnValue(ValueType::NONE);
}

void LispKeyWord::setUpTable() {
	keywordTable.insert("define");
	keywordTable.insert("if");
	keywordTable.insert("else");
	keywordTable.insert("let");
	keywordTable.insert("lambda");
}

