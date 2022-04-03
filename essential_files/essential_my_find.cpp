#include "swap.h"
//函数的作用：传入一个任意类型（使用模板函数）的数组array，传入一个值，查找array中有没有这个数，如有，返回其位置
template <typename elemType>
elemType *my_find(const elemType* my_array, int size, const elemType* value)
//知识点：当array被传入，仅有第一个元素的地址被传递，注意形参的写法，当调用这个的时候，直接传入array，下面直接操作array，不用管*，有*是提领的操作
{
	if (!my_array || size < 1)
	{
		return 0;
	}

	for (int ix = 0; ix < size; ++ix)//另一种写的方式是 for(int ix =0 ; ix < size ; ++my_array)--- if (*array == value)
	{
		if (my_array[ix] == value)
		{
			return &my_array[ix];// 因为函数的返回值是*指针地址，所以返回&地址；如果返回值，array[ix]《当写下这个，指针的算术运算和提领操作都会自动完成》或者 *（array + ix）都可以
		}
	}
	return 0;
}

//使用第二个指针
template <typename elemType>
elemType* my_find(const elemType *first, const elemType *last, const elemType &value)
{
	if (!last || !first) //如果 last \ first 指针都是0，返回
		return 0;

	for (; first != last; ++first)
	{
		if (*first == value)
			return first;
	}

	return 0;
}

//调用find
// string sa[4] = {"pooh","piglet","eeyore","tigger"};
// string *ps = my_find(sa,sa+4,sa[3])

//使用Iterator 
template <typename IteratorType,typename elemtype>
IteratorType my_find(IteratorType first, IteratorType last, const elemtype& value)
{
	for (; first != last; ++first)
	{
		if (value == *first)
			return first;
	}

	return last;
}

//调用 
//const int asize = 8;
//int ia[ asize ] = {1,1,2,3,5,8,13,21};
//vector<int> ivec{ ia,ia + asize };
//list<int> ilist{ ia, ia + asize };

//int* pia = my_find(ia, ia + asize, 1024);

//vector<int>::iterator it = find(ivec.begin(), ivec.end(), 1024);

//list<int>::iterator iter =  find(ilist.begin(), ilist.end(), 1024);
