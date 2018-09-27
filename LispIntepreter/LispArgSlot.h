//
// Created by Chen Xujie on 9/27/18.
//

#ifndef LISPINTEPRETER_LISPARGSLOT_H
#define LISPINTEPRETER_LISPARGSLOT_H

#include <algorithm>

#include "LispNode.h"

class LispArgSlot : public LispNode {
public:
    explicit LispArgSlot(int slot) : _slot(slot) {}

    ReturnValue eval() override;

    void setNumber(int num) { _slot = num; }

    std::string Type() const override { return "arg_slot"; }

private:
    int _slot;
};


#endif //LISPINTEPRETER_LISPARGSLOT_H
