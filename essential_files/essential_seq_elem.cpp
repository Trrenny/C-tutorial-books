#include "swap.h"

bool seq_elem(int pos, int& elem, const vector<int>* (*seq_ptr)(int))
{
	//函数指针，形式有点复杂，他本质上是一个指针，是一个指向函数的指针（不是地址），表达要与其指向函数的一致
	//即，参考fibon_seq函数，需要指明其所指函数的返回类型const vector<int>*、参数列表(int)
	//作为一个指针，传入本函数中
	//呈现在程序中，不需要带*号

	const vector<int>* pseq = seq_ptr(pos);//调用函数指针，但是不知道是不是真的会指向那个函数，所以最好判断下

	if (!seq_ptr)
		display_message("Internal Error: seq_ptr is set to null ");

	if (!pseq)
	{
		elem = 0; return false;
	}

	elem = (*pseq)[pos - 1];

	return true;
}