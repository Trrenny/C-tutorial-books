//#include<iostream> 
//using namespace std
#include"swap.h"

void display(const vector<int> &vec) {//��ζ�����������ʾ������ʱ��vector�����е�Ԫ�ض��ᱻ����...
										// ֱ�Ӵ���vector�ĵ�ַ���ٶȻ����...
										//����const��������ɴ��󣬵����Ͽ������Ķ���������˽⵽���Դ�ַ�ķ�ʽ������vector
										//��Ϊ�˱��⸴�Ʋ�����������Ϊ��Ҫ�ں����ж��������޸�
	for (unsigned int i = 0; i < vec.size(); i++)
	{	
		cout << vec[i] << ' ';
	}
	cout << endl;
}

//��ָ�봫���д��
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
//	//����һ��vectorָ��
//	//�������ӡvector�е�ȫ���ַ���
//	for (int i = 0; i < vec_size; ++i)
//	{
//		cout << &vec[i] << endl;
//	}
//
//}

//�����õ��������Ҫ��һ�㣺ָ����ܣ�Ҳ���ܲ���ָ��ĳ��ʵ�ʶ��󣬵���������ָ���ʱ��һ��Ҫ����Ƿ��Ƿ�0
// �����ñض�����ĳ���������Բ��ؼ��