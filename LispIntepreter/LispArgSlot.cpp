//
// Created by Chen Xujie on 9/27/18.
//

#include "LispArgSlot.h"
#include "LispFunction.h"

ReturnValue LispArgSlot::eval() {
    return LispFunction::arg_context[_slot]->eval();
}
