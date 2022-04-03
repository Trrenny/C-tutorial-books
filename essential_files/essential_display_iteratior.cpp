//#include "swap.h"

//const vector<string> cs_vec;//const 允许我们读取vector的元素，不允许写入
//vector<string>::const_iterator iter = cs_vec.begin();//::表示此iterator乃是位于string vector定义内的嵌套nested类型

//template <typename elemtype>
//void display_iterator(const vector<elemtype>& vec, ostream& os)
//{
//	vector<elemtype>::const_iterator iter = vec.begin();
//	vector<elemtype>::const_iterator end_it = vec.end();
//
//	//如果vec是空的，iter便等于end_it
//	for (; iter != end_it; ++iter)
//	{
//		os << *iter << ' '<< iter -> size();//对指针提领就是取值,通过iter调用底部的string元素所提供的操作
//		
//	}
//	os << endl;
//}

//template <typename elemtype>
//void display_iterator(const vector<int>& vec)
//{
//	vector<int>::const_iterator iter = vec.begin();
//	vector<int>::const_iterator end_it = vec.end();
//
//	//如果vec是空的，iter便等于end_it
//	for (; iter != end_it; ++iter)
//	{
//		std::cout << *iter << ' '<< iter->size();//对指针提领就是取值,通过iter调用底部的string元素所提供的操作
//		
//	}
//	 std::cout<<std::endl;
//}