#include"swap.h"


void bubble_sort(vector<int> &vec, ofstream *ofil) {//�ں���ʵ�ִ��Ͳ��ö���Ĭ�ϲ���
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		for (unsigned int j = i + 1; j < vec.size(); j++)
		{
			if (vec[i] > vec[j])
			{	
				if (ofil != 0)
				{
					(*ofil) << "about to call swap! " << "i = " << i << "; j = " << j << '\t' << "swapping :" << vec[i] << "with" << vec[j] << endl;
				}
				swap(vec[i], vec[j]);
			}
		}
	}
}