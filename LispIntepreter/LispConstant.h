//
// Created by Chen Xujie on 9/18/18.
//

#ifndef LISPINTEPRETER_LISPCONSTANT_H
#define LISPINTEPRETER_LISPCONSTANT_H

#include <algorithm>

#include "LispNode.h"

class LispConstant : public LispNode {
public:
    LispConstant() : _value(0) {}

	LispConstant(int v) : _value(v) {}

	ReturnValue eval() override;

    void setNumber(int num) { _value = num; }

	int getNumber() { return _value; }

    std::string Type() const override { return "constant"; }

	std::string Description() const override {
		static char buf[256];
		sprintf(buf, "Value: %d", _value);
		return std::string(buf);
	}
private:
    int _value;
};


#endif //LISPINTEPRETER_LISPCONSTANT_H
