#include "ReturnValue.h"
#include <cassert>

ReturnValue::~ReturnValue()
{
}

void ReturnValue::setInt(int i)
{
	assert(this->_type == ValueType::INTEGER);
	this->_value.i = i;
}

int ReturnValue::getInt() const
{
	assert(this->_type == ValueType::INTEGER);
	return this->_value.i;
}

void ReturnValue::printValue() const
{
	if (_type == ValueType::NONE) {
		printf("%s\n", "None");
	}
	else if (_type == ValueType::INTEGER) {
		printf("%d\n", _value.i);
	}
}
