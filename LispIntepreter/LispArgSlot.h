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

	LispNode * eval() override;

    void setSlot(int num) { _slot = num; }
    int getSlot() {return _slot;}

    std::string Type() const override { return "arg_slot"; }

	std::string Description() const override {
		static char buf[256];
		sprintf(buf, "Slot: %d", _slot);
		return std::string(buf);
	}

private:
    int _slot;
};


#endif //LISPINTEPRETER_LISPARGSLOT_H
