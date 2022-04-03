#include "swap.h"

inline bool Stack::empty() {
	return _stack.empty();//��ĳ�Ա�������Է���˽�г�Ա����
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
	return _stack.size() == _stack.max_size();//��ĿǰԪ�صĸ��������͵ײ�vector��max_size()����ֵ���Ƚ�

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











