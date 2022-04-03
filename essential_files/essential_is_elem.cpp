#include"swap.h"

//前置声明
//extern bool grow_vec(vector<int>&, int);//持续将数列加入vector

bool is_elem(vector<int>& vec, int elem)
{
	//int max_value = max_element(vec.begin(), vec.end());
	int max_value = vec.empty() ? 0 : vec[vec.size() - 1];
	//if (max_value < elem)//如果所给的值大于数组的最大值，就要将其扩容
	//{
	//	return grow_vec(vec, elem);
	//}

	if (max_value == elem)
	{
		return true;
	}

	return binary_search(vec.begin(), vec.end(), elem);//限定一定是有序的vec
}
