#include "swap.h"

void Fibonacci::gen_elems(int pos) const
{
	if (_elems.size())
	{	
		_elems.push_back(1);
		_elems.push_back(1);
	}

	if (_elems.size() <= pos)
	{
		int ix = _elems.size();
		int n_2 = _elems[ix - 2];
		int n_1 = _elems[ix - 1];

		for (; ix <= pos; ++ix)
		{
			int elem = n_2 + n_1;
			_elems.push_back(elem);
			n_2 = n_1;
			n_1 = elem;
		}

	}
}

ostream& Fibonacci::print(ostream& os) const
{
	int elem_pos = _beg_pos - 1;
	int end_pos = elem_pos + _length;

	if (end_pos > _elems.size())
	{
		Fibonacci::gen_elems(end_pos);
	}

	while (elem_pos < end_pos)
	{
		os << _elems[elem_pos++] << "  ";

	}
	return os;
}