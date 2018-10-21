#ifndef _LISP_DELETER_
#define _LISP_DELETER_
#include "LispNode.h"
#include <vector>
class Deleter
{
public:
	Deleter();
	~Deleter();

	static LispNode * getCopy(LispNode * node) { return LispNode::copy(node); }

	static void Clear() { for (auto p : _pointers) delete p; }

private:
	static std::vector<LispNode *> _pointers;
};

#endif // !_LISP_DELETER_


