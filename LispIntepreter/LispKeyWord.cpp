#include "LispKeyWord.h"
#include "LispName.h"
#include "LispFunction.h"
#include "LispConstant.h"

std::set<std::string> LispKeyWord::keywordTable;



LispKeyWord::LispKeyWord() : LispNode()
{
}

int LispKeyWord::eval()
{
	if (this->_name == "define") {
		LispFunction::FunctionInfo info;
		if (this->children[0]->Type() == "name") {
			auto n = (LispName *)(this->children[0]);
			info.argNumber = 0;
			info.node = LispNode::copy(this->children[1]);
			LispFunction::customizedFuncTable[n->getName()] = info;
		}
	}
	return 0;
}

void LispKeyWord::setUpTable()
{
	keywordTable.insert("define");
	keywordTable.insert("if");
	keywordTable.insert("else");
	keywordTable.insert("let");
	keywordTable.insert("lambda");
}

