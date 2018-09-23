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

	ReturnValue eval() override;

    void setNumber(int num) { _value = num; }

    std::string Type() const override { return "constant"; }
private:
    int _value;
};


#endif //LISPINTEPRETER_LISPCONSTANT_H
