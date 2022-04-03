//#include<iostream> 
//using namespace std
#include"swap.h"

void display(const vector<int> &vec) {//意味着我想进行显示操作的时候，vector内所有的元素都会被复制...
										// 直接传入vector的地址，速度会更快...
										//少了const并不会造成错误，但加上可以让阅读程序的人了解到，以传址的方式来传递vector
										//是为了避免复制操作，而不是为了要在函数中对它进行修改
	for (unsigned int i = 0; i < vec.size(); i++)
	{	
		cout << vec[i] << ' ';
	}
	cout << endl;
}

//以指针传入的写法
//void display(const vector<int>* vec)
//{
//	if (!vec)
//	{
//		cout << "display(): the vector pointer is 0\n";
//		return;
//	}
//	for (unsigned int i = 0; i < vec->size(); ++i)
//	{	
//		cout << (*vec)[i] << ' ';
//	}
//	cout << endl;
//}
//
//void display(vector<string>& vec, int& vec_size)
//{
//	//输入一个vector指针
//	//输出：打印vector中的全部字符串
//	for (int i = 0; i < vec_size; ++i)
//	{
//		cout << &vec[i] << endl;
//	}
//
//}

//与引用的区别更重要的一点：指针可能（也可能不）指向某个实际对象，当我们提领指针的时候，一定要检查是否是非0
// 而引用必定代表某个对象，所以不必检查