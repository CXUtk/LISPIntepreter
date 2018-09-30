#ifndef LISPINTEPRETER_LISPKEYWORD_H
#define LISPINTEPRETER_LISPKEYWORD_H

#include "LispNode.h"
#include <set>

class LispKeyWord : public LispNode
{
public:
	LispKeyWord();

	ReturnValue eval() override;

	void setName(const std::string& str) { _name = str; }

	std::string getName() { return _name; }

	static std::set<std::string> keywordTable;
	static void setUpTable();

	std::string Type() const override { return "keyword"; }

private:
	std::string _name;

	LispNode * fixArgs(LispNode *, std::vector<std::string>&);
	ReturnValue evalDefine();
	ReturnValue evalIf();
};

#endif
