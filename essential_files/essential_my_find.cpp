#include "swap.h"
//���������ã�����һ���������ͣ�ʹ��ģ�庯����������array������һ��ֵ������array����û������������У�������λ��
template <typename elemType>
elemType *my_find(const elemType* my_array, int size, const elemType* value)
//֪ʶ�㣺��array�����룬���е�һ��Ԫ�صĵ�ַ�����ݣ�ע���βε�д���������������ʱ��ֱ�Ӵ���array������ֱ�Ӳ���array�����ù�*����*������Ĳ���
{
	if (!my_array || size < 1)
	{
		return 0;
	}

	for (int ix = 0; ix < size; ++ix)//��һ��д�ķ�ʽ�� for(int ix =0 ; ix < size ; ++my_array)--- if (*array == value)
	{
		if (my_array[ix] == value)
		{
			return &my_array[ix];// ��Ϊ�����ķ���ֵ��*ָ���ַ�����Է���&��ַ���������ֵ��array[ix]����д�������ָ������������������������Զ���ɡ����� *��array + ix��������
		}
	}
	return 0;
}

//ʹ�õڶ���ָ��
template <typename elemType>
elemType* my_find(const elemType *first, const elemType *last, const elemType &value)
{
	if (!last || !first) //��� last \ first ָ�붼��0������
		return 0;

	for (; first != last; ++first)
	{
		if (*first == value)
			return first;
	}

	return 0;
}

//����find
// string sa[4] = {"pooh","piglet","eeyore","tigger"};
// string *ps = my_find(sa,sa+4,sa[3])

//ʹ��Iterator 
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

//���� 
//const int asize = 8;
//int ia[ asize ] = {1,1,2,3,5,8,13,21};
//vector<int> ivec{ ia,ia + asize };
//list<int> ilist{ ia, ia + asize };

//int* pia = my_find(ia, ia + asize, 1024);

//vector<int>::iterator it = find(ivec.begin(), ivec.end(), 1024);

//list<int>::iterator iter =  find(ilist.begin(), ilist.end(), 1024);
