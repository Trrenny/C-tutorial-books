#include "swap.h"

inline bool Triangular_iterator::operator== (const Triangular_iterator& rhs) const
{
	return _index == rhs._index;
}

inline bool Triangular_iterator::operator!= (const Triangular_iterator& rhs) const
{
	return !(*this == rhs);
}

inline int Triangular_iterator::operator* () const
{
	check_integrity();
	return Triangular::_elems[_index];

}

inline Triangular_iterator& Triangular_iterator::operator++()
{//ǰ�ð汾
	++_index;
	check_integrity();
	return *this;//��Ϊ����һ�����ã����Ի���Ӧ������һ��
}

inline Triangular_iterator& Triangular_iterator::operator++(int)
{//���ð汾,���������Զ�Ϊint����һ��0������������Ϊ�˷�ֹ������һ����������ʹ��int����
	Triangular_iterator tmp = *this;
	++_index;
	check_integrity();
	return tmp;//��Ϊ����һ�����ã����Ի���Ӧ������һ��
}

inline void Triangular_iterator::check_integrity() const
{//���ã�ȷ��_index������_max_elems����ȷ��_elems�����˱�Ҫ��Ԫ��
	if (_index >= Triangular::get_max_elems())
	{
		//throw iterator_overflow();
		return;
	}

	//��Ҫʱ��չ����
	if (_index >= Triangular::get_elems_size())
	{
		Triangular::gen_elements(_index + 1);
	}
}