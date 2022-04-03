#include"swap.h"
void swap(int &a, int &b) {
	int temp = 0;
	temp = a;
	a = b;
	b = temp;
	//cout << "After swap:" << "a = " << a << ";" << "b = " << b << endl;
}