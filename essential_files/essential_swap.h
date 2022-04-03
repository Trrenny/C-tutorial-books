#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<fstream>//�ļ��Ķ�д
#include<algorithm> //
#include<Eigen/Dense>
using namespace std;
void swap(int &a, int &b);
void bubble_sort(vector<int> &vec, ofstream* ofil = 0);//�ں���������ͷ�ļ�����Ĭ�ϲ���
const vector<int>* fibon_seq(int size);//����ú��������ص���һ����ַ

bool seq_elem(int pos, int& elem, const vector<int>* (*seq_ptr)(int) = fibon_seq);//��ʼ����ֵһ��Ĭ�ϲ���

void display(vector<int> &vec);
//void display(const vector<int>* vec);
//void display(vector<string>& vec, int& vec_size);

void display_message(char ch);
void display_message(const string& str);
void display_message(const string& str, int& size);
void display_message(const string& str, int& size1, int& size2);
template <typename elemType>
void display_message(const string &str, const vector<elemType>& vec)
{
	cout << str << ':';
	for (unsigned int ix = 0 ; ix < vec.size(); ++ix)
	{
		elemType t = vec[ix];
		cout << t << ' ';
	}
	cout << endl;
}

template <typename elemType>
elemType* my_find(const elemType* my_array, int size, const elemType* value);
template <typename elemType>
elemType* my_find(const elemType* first, const elemType* last, const elemType* value);
template <typename IteratorType, typename elemtype>
IteratorType my_find(IteratorType first, IteratorType last, const elemtype& value);


//�������
class Stack {
public:
	//����Ĳ����������ִ�гɹ����ͷ���true
	//pop��peek�Ὣ�ַ�����������elem��
	bool push(const string&);
	bool pop(string& elem);
	bool peek(string& elem);
	bool empty();
	bool full();
	int size() {
		return _stack.size();//���еĳ�Ա���������Է���˽�г�Ա
	}
private:
	vector<string> _stack;

};

class Triangular_iterator
{//��������ã� ά��һ������ֵ������Triangular���е�static vector-->_elems
public:
	//Ϊ�˲�Ҫ��ÿ�η���Ԫ�ص�ʱ��ִ��-1�������˴���_index��ֵ��Ϊindex-1
	Triangular_iterator(int index) : _index(index - 1) {};//�����վͿ���//���캯���ڶ��ֳ�ʼ���﷨����Ա��ʼ���б��������index
	bool operator== (const Triangular_iterator&) const;//��������أ����صȺţ���Ҫ�������һ��
	bool operator!= (const Triangular_iterator&) const;
	int operator*() const;//���س˺ţ�û�в���
	Triangular_iterator& operator++();//ǰ�ð�
	Triangular_iterator& operator++(int);//���ð�
	void check_integrity() const; //��ʾ����Ա����


private:
	
	unsigned int _index;
};

class Triangular {
public:
	// ������һ������ص�constructor
	Triangular();//default constructors
	Triangular(int len);
	Triangular(int len, int beg_pos) : _length(len > 0 ? len : 1), _beg_pos(_beg_pos > 0 ? beg_pos : 1)
	{
		_next = _beg_pos - 1;
		int elem_cnt = _beg_pos + _length - 1;

		if (_elems.size() < elem_cnt)
			gen_elements(elem_cnt);
	}
	typedef Triangular_iterator tri_iterator;
	tri_iterator begin( ) const
	{
		return tri_iterator(_beg_pos);
	}

	
	tri_iterator end( ) const
	{
		return tri_iterator(_beg_pos + _length);
	}//ΪTriangular�����begin()/end()��member funciotn

	static int get_elems_size() { return _elems.size(); }
	static int get_max_elems() { return _max_elems; }
	
	static void gen_elements(unsigned int length)
	{
		if (length < 0 || length > _max_elems)
		{
			return;
		}

		if (_elems.size() < length)
		{
			unsigned int ix = _elems.size() ? _elems.size() + 1 : 1;
			for (; ix <= length; ++ix)
			{
				_elems.push_back(ix * (ix + 1) / 2);
			}
		}
	}
	static bool is_elem(int value)//����һ��ֵ�����ݸ�ֵ�Ƿ���Triangular�����ڶ�����true��false
	{
		if (!_elems.size() || _elems[_elems.size() - 1] < value)//Tri��������ǵ����ģ�������һ��Ԫ��С�ڸ�����value��˵�����ڣ�����գ���valueҲ�ǲ���
			gen_elements_to_value(value);

		vector<int>::iterator fount_it;
		vector<int>::iterator end_it = _elems.end();

		fount_it = find(_elems.begin(), end_it, value);
		return fount_it != end_it;
	}
	static void gen_elements_to_value(int value)//�������һ��cpp���壬���static���Բ��õ�����д
	{
		//���ã�������value��һ������ʱ������������鲢û�е���value���ֵ�����Խ����������չ
		int ix = _elems.size();
		if (!ix)
			_elems.push_back(1); ix = 1;
		while (_elems[ix - 1] < value && ix < _max_elems)
		{
			++ix;
			_elems.push_back(ix + (ix + 1) / 2);

		}

		if (ix == _max_elems)
			cout << "Triangular Sequence : oops: value too large" << value << "-- exceeds max size of " << _max_elems << endl;
	}
	//ͨ��������Ԫ��ϵ������һ������ʱ����˽�г�Ա
	friend int tri_iterator::operator*() const;
	friend void tri_iterator::check_integrity() const;
	//friend class tri_iterator;
	//static vector<int> _elems;
	//static const int _max_elems{ 1024 };
private:
	int _length;//Ԫ�صĸ���
	int _beg_pos;//��ʼλ��
	int _next; //��һ������Ŀ��
	static vector<int> _elems;
	static const int _max_elems{ 1024 };
};

class Matrix
{
public:
	Matrix(int row, int col) :_row(row), _col(col)
	{
		 _pmat = new double[ row * col ];
	}

	~Matrix()
	{
		delete[] _pmat;
	}

	Matrix& operator=(const Matrix& rhs);
private:
	int _row;
	int _col;
	double* _pmat;

};

class LessThan
{
public:
	LessThan(int val) : _val(val) {};//������Ĭ�ϵĹ��캯�������ǳ�ʼ��ʱ��һ��Ҫ�����������
	int get_comp_val()
	{
		return _val;
	}

	void set_comp_val(int nval)
	{
		_val = nval;
	}

	bool operator() (int _value) const;

	

private:
	int _val;

};

class common
{
public:
	int count_less_than(const vector<int>& vec, int comp);
};


class num_sequence//�������
{
public:
	virtual ~num_sequence() {};
	//�麯����ֵΪ0��ʾ����һ�����麯������ʾ����麯�����������û��ʵ�ʵ����壬���麯��û�ж���
	virtual int elem(int pos) const = 0;//�����û�ָ��λ���ϵ�Ԫ��
	
	virtual const char* what_am_i() const = 0;//����һ���ַ����������е�����
	virtual ostream& print(ostream& os = cout) const;

	virtual num_sequence* clone() = 0;//�������ķ�������ֵ��һ�����࣬������̳�ʱ��clone�����ɷ���һ��ָ��ָ��num_sequence�����������κ�һ��������

	int length() const
	{
		return _length;
	}

	int beg_pos() const
	{
		return _beg_pos;
	}
	
	static int max_elems()//�������Ԫ�ظ���
	{
		return _max_elems;
	}

protected:
	virtual void gen_elems(int pos) const = 0;//��������Ԫ��
	num_sequence(int len, int bp, vector<int>& re) : _length(len), _beg_pos(bp), _relems(re) {}
	bool check_integrity(int pos) const//�жϴ���pos�Ƿ�����Чλ��
	{
		if (pos <= 0 || pos > _max_elems)
		{
			cerr << "!! invalid position :" << pos << "Cannot honor request\n";
			return false;
		}
		return true;
	}
	const static int _max_elems = 1024;
	int _length;
	int _beg_pos;
	vector<int>& _relems;// ����ָ��������ĳ��static vector,�����޷�����ն���ָ���п����ǿ�

};

class Fibonacci : public num_sequence
{
public:
	Fibonacci(int len = 1, int beg_pos = 1);
	virtual const char* what_am_i() const
	{
		return "Fibonacci";
	}


	//Fibonacci* clone()
	//{
	//	return new Fibonacci(*this);
	//}

protected:
	virtual void gen_elems(int pos) const;
	static vector<int> _elems;
};

template <typename valtype>
class BTnode
{
	friend class BinaryTree<valtype>;
public:
	BTnode(const valtype& val);
	void insert_value(const valtype& val);
	void remove(const valtype& val);
	void remove_root(const valtype& val);
	void remove_value(const valtype& val, BTnode<valtype>*& prev);
	static void lchild_leaf(BTnode* leaf, BTnode* subtree)//��������Ҷ�ڵ�
	{
		while (subtree->_lchild)
			subtree = subtree->_lchild;//�ҵ������������ڶ���
		subtree->_lchild = leaf;//������Ҷ�ڵ㸳ֵΪleaf����ڵ㣬ʵ�ְ���

	}

	void preorder(BTnode* pt, ostream& os) const
	{
		if (pt)
		{
			display_val(pt, os);
			if (pt->_lchild)
				preorder(pt->_lchild, os);
			if (pt->_rchild)
				preorder(pt->_rchild, os);

		}


	}

	void inorder(BTnode* pt, ostream& os)
	{
		if (pt)
		{
			if (pt->_lchild)
				inorder(pt->_lchild, os);
			display_val(pt, os);
			if (pt->_rchild)
				inorder(pt->_rchild, os);

		}
	}

	void postorder(BTnode* pt, ostream& os) const
	{
		if (pt)
			if (pt->_lchild)
				postorder(pt->_lchild,os);
		if (pt->_rchild)
			postorder(pt->_rchild, os);

		display_val(pt, os);

	}

	friend ostream& operator<< (ostream& os, const BinaryTree& bt)//Ϊ����<<���غ����ܹ�˳������print���������Ϊprint
	{
		os << "Tree:" << endl;
		bt.print(os);
		return os;

		//���ã�BinaryTree<string> bts; cout << bts << endl;
	}

private:
	valtype _val;
	int _cnt;
	BTnode* _lchild;
	BTnode* _rchild;
};


//ʵ��һ��ģ����
template <typename elemType>
class BinaryTree
{
	
public:
	BinaryTree();
	BinaryTree(const BinaryTree&);
	~BinaryTree();
	BinaryTree<elemType> operator=(const BinaryTree<elemType>&);

	bool empty()
	{
		return _root == 0;
	}

	void clear()
	{
		if (_root)
		{
			clear(_root);
			_root = 0;
		}
	}
	void insert(const elemType& elem);
	


private:
	BTnode<elemType> *_root;
	void copy(BTnode<elemType>*tar, BTnode<elemType>*src);//��src��ָ�����������Ƶ�tar��ָ������
	void clear(BTnode<elemType>*);

}







//int *func()
//{
	//int *a = new int(10);
	//return a;
//}





