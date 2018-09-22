#include "LispKeyWord.h"

std::set<std::string> LispKeyWord::keywordTable;

LispKeyWord::LispKeyWord() : LispNode()
{
}

int LispKeyWord::eval()
{
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

