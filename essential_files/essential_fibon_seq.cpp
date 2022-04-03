#include"swap.h"

const vector<int>* fibon_seq(int size)//定义该函数，返回的是一个地址
{
	const int max_size = 1024;
	static vector<int> elems;

	if (size == 0 || size > 1024)
	{
		cerr << "fibon_seq(): oops : invalid size : " << size << "can't fullfill request. \n";
		return 0;
	}

	for (int i = elems.size(); i < size; i++)
	{
		if (i == 0 || i == 1)
		{
			elems.push_back(1);
		}

		else
			elems.push_back(elems[i - 1] + elems[i - 2]);
	}

	return &elems;
}