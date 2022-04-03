// Helloworld1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "swap.h"

//枚举类型
enum ns_type {ns_fibon, ns_lucas, ns_pell, ns_triang, ns_square, ns_pent};

const int seq_size(18);
int pell_seq[seq_size];//定义大小为18的数组array

#include<vector>
vector<int> pell_seq2(seq_size);//定义大小为18的vector

int elem_seq[seq_size] = {
    1,2,3,
    3,4,7,
    2,5,12,
    3,6,10,
    4,9,16,
    5,12,22
}; vector<int> elem_seq2 = { elem_seq,elem_seq + seq_size };//利用array初始化vec

const int max_seq(6);
string seq_names[max_seq] = {
    "Fi",
    "Lu",
    "Pe",
    "Tri",
    "Sq",
    "Pen"
}; //定义字符串array

vector<string> seq_namess = { seq_names, seq_names + max_seq };
vector<string>* seq_namesss = &seq_namess;


int ival = 1024;
int* pi = &ival; // &取ival的地址,指针pi指向这个地址
int* pii = 0; string* ps = 0; double* pd = 0; 

//提领指针pi的值，*pi
// if (*pi != 1024)
//*pi = 1024


//防止对null指针进行提领操作，检验指针地址是否为0
//if( pi && *pi != 1024)
   // *pi =1024

//利用函数指针数组，将数个函数组织在一起，通过索引递增的方式访问
//const vector<int>* (*seq_array[])(int) = { fibon_seq, lucas_seq, pell_seq,triang_seq,square_seq,pent_seq };
//int seq_index = 0;
//while (next_seq == true)
//{
//    seq_ptr = seq_array[++seq_index];
//}



int main()
{
    ////int *a = func();
    //int b = 10;
    //int c = 20;
    //swap(b,c);
    ////std::cout << *a << endl;
    ////std::cout << *a << endl;

    //system("pause");
    

    int ia[8] = { 8, 34, 3, 13, 1, 21, 5, 2 };
    string sa[4] = { "a","b","c","string" };
    vector<string> vec_sa(sa, sa + 4);
    vector<int> vec( ia , ia + 8 );
    const vector<int> vec2{ 3,4,7,2,8 };
    vector<int> vec3(3);//测试vec大小


    //display_message( "before sort : ");
    //display_message("The size of vec is ", ival);

    //测试排序算法bublle_sort
    //string str = "before sort";
    //display_message(str,vec);//调用指针的写法display(&vec)
    //bubble_sort(vec);
    //str = "after sort";
    //display_message(str, vec);


    //测试my_find第三个函数
    //vector<int>::iterator iter1 = vec.begin();
    //vector<int>::iterator iter2 = vec.end();
    //vector<int>::iterator it = my_find(iter1, iter2, 34);
    //cout << vec[it] << endl;

    //测试my_find第二个函数
    //int* pia = my_find(ia, ia+7, ia[3]);
    //string* ps = find(sa, sa+4, sa[3]);//用数组测试函数2的方式
    //string* ps2 = find(&vec_sa[0], &vec_sa[3], vec_sa[3]);//用vector测试函数2的方式
    common com;
    cout << com.count_less_than(vec2,5)<< endl;







    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

