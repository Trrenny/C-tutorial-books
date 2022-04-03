#include "swap.h"

inline bool Stack::empty() {
	return _stack.empty();//类的成员函数可以访问私有成员变量
}

bool Stack::pop(string &elem)
{
	if (empty())
		return false;
	elem = _stack.back();
	return true;

}

inline bool Stack::full()
{
	return _stack.size() == _stack.max_size();//将目前元素的个数拿来和底层vector的max_size()的数值做比较

}

bool Stack::peek(string& elem)
{
	if (empty())
	{
		return false;
	}

	elem = _stack.back();
	return true;
}

bool Stack::push(const string& elem)
{
	if (full())
	{
		return false;
	}

	_stack.push_back(elem);
	return true;
}











