#include"swap.h"

int common::count_less_than(const vector<int>& vec, int comp)
{
	LessThan Lt(comp);

	int count{ 0 };

	for (int ix = 0; ix < vec.size(); ++ix)
	{
		if (Lt(vec[ix]))
			++count;

	}
	return count;
}