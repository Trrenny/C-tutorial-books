#include "swap.h"

//提供重载函数

void display_message(char ch)
{
	cout << ch;

}
void display_message(const string &str)
{
	cout << str << endl;
}

void display_message(const string& str, int& size)
{
	cout << str << size << endl;

}

void display_message(const string& str, int& size1, int& size2)
{
	cout << str << size1 << ' ' << size2 << endl;
}