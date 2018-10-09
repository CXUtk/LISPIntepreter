#ifndef LISPINTEPRETER_LISPNAME_H
#define LISPINTEPRETER_LISPNAME_H

#include "LispNode.h"
#include <set>
class LispName : public LispNode
{
public:
	LispName(const std::string& s) : _name(s) {}

	ReturnValue eval() override { return ReturnValue(ValueType::NONE); }

	std::string getName() { return _name; }

	std::string Type() const override { return "name"; }

	std::string Description() const override {
		static char buf[256];
		sprintf(buf, "Name: %s", _name.c_str());
		return std::string(buf);
	}

private:
	std::string _name;
};

#endif