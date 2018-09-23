//
// Created by Chen Xujie on 9/18/18.
//

#include "LispConstant.h"

ReturnValue LispConstant::eval()
{
	ReturnValue ret(ValueType::INTEGER); 
	ret.setInt(_value); 
	return ret;
}
