//
// Created by Chen Xujie on 9/18/18.
//

#include "LispConstant.h"

LispNode * LispConstant::eval()
{
	return this;
}

std::string LispConstant::getVal() const
{
	return std::to_string(this->getNumber());
}
