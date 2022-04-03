#include "swap.h"

bool seq_elem(int pos, int& elem, const vector<int>* (*seq_ptr)(int))
{
	//����ָ�룬��ʽ�е㸴�ӣ�����������һ��ָ�룬��һ��ָ������ָ�루���ǵ�ַ�������Ҫ����ָ������һ��
	//�����ο�fibon_seq��������Ҫָ������ָ�����ķ�������const vector<int>*�������б�(int)
	//��Ϊһ��ָ�룬���뱾������
	//�����ڳ����У�����Ҫ��*��

	const vector<int>* pseq = seq_ptr(pos);//���ú���ָ�룬���ǲ�֪���ǲ�����Ļ�ָ���Ǹ���������������ж���

	if (!seq_ptr)
		display_message("Internal Error: seq_ptr is set to null ");

	if (!pseq)
	{
		elem = 0; return false;
	}

	elem = (*pseq)[pos - 1];

	return true;
}