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

bool ReturnValue::checkMatch(const std::string & str) const
{
	char buf[1024];
	if (_type == ValueType::NONE)
		sprintf(buf, "%s", "None");
	else if (_type == ValueType::INTEGER)
		sprintf(buf, "%d", _value.i);
	std::string r(buf);
	return r == str;
}


