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
{//前置版本
	++_index;
	check_integrity();
	return *this;//因为返回一个引用，所以还是应该提领一下
}

inline Triangular_iterator& Triangular_iterator::operator++(int)
{//后置版本,编译器会自动为int分配一个0参数，这里是为了防止函数名一样，并不会使用int参数
	Triangular_iterator tmp = *this;
	++_index;
	check_integrity();
	return tmp;//因为返回一个引用，所以还是应该提领一下
}

inline void Triangular_iterator::check_integrity() const
{//作用：确保_index不大于_max_elems，并确保_elems储存了必要的元素
	if (_index >= Triangular::get_max_elems())
	{
		//throw iterator_overflow();
		return;
	}

	//必要时扩展容器
	if (_index >= Triangular::get_elems_size())
	{
		Triangular::gen_elements(_index + 1);
	}
}