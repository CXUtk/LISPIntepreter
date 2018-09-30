#ifndef LISPINTEPRETER_RETVAL_H
#define LISPINTEPRETER_RETVAL_H
#include <string>
enum class ValueType {
	INTEGER,
	DOUBLE,
	STRING,
	FUNCTION,
	NONE
};

class ReturnValue {
public:
	explicit ReturnValue(ValueType type) : _type(type) {}
	~ReturnValue();
	void setInt(int i);
	int getInt() const;
	ValueType getType() const { return _type; }

	void printValue() const;
	bool checkMatch(const std::string& str) const;

private:
	ValueType _type;
	union Value
	{
		int i;
		double d;
		char * string;
		void * func;
		Value() {
			d = 0.0;
		}
	};
	Value _value;
};
#endif