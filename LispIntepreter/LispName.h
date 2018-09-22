#ifndef LISPINTEPRETER_LISPNAME_H
#define LISPINTEPRETER_LISPNAME_H

#include "LispNode.h"
#include <set>
class LispName : public LispNode
{
public:
	LispName(const std::string& s) : _name(s) {}

	ReturnValue eval() override { return 0; }

	std::string getName() { return _name; }

	std::string Type() const override { return "name"; }

private:
	std::string _name;
};

#endif