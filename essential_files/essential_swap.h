#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<fstream>//文件的读写
#include<algorithm> //
#include<Eigen/Dense>
using namespace std;
void swap(int &a, int &b);
void bubble_sort(vector<int> &vec, ofstream* ofil = 0);//在函数声明的头文件定义默认参数
const vector<int>* fibon_seq(int size);//定义该函数，返回的是一个地址

bool seq_elem(int pos, int& elem, const vector<int>* (*seq_ptr)(int) = fibon_seq);//初始化赋值一个默认参数

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


//类的声明
class Stack {
public:
	//这里的操作函数如果执行成功，就返回true
	//pop和peek会将字符串内容置于elem中
	bool push(const string&);
	bool pop(string& elem);
	bool peek(string& elem);
	bool empty();
	bool full();
	int size() {
		return _stack.size();//类中的成员函数，可以访问私有成员
	}
private:
	vector<string> _stack;

};

class Triangular_iterator
{//该类的作用： 维护一个索引值，索引Triangular类中的static vector-->_elems
public:
	//为了不要在每次访问元素的时候都执行-1操作，此处将_index的值设为index-1
	Triangular_iterator(int index) : _index(index - 1) {};//保留空就可以//构造函数第二种初始化语法：成员初始化列表，带入参数index
	bool operator== (const Triangular_iterator&) const;//运算符重载，重载等号，需要传入参数一下
	bool operator!= (const Triangular_iterator&) const;
	int operator*() const;//重载乘号，没有参数
	Triangular_iterator& operator++();//前置版
	Triangular_iterator& operator++(int);//后置版
	void check_integrity() const; //表示常成员函数


private:
	
	unsigned int _index;
};

class Triangular {
public:
	// 可能由一组的重载的constructor
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
	}//为Triangular类添加begin()/end()的member funciotn

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
	static bool is_elem(int value)//给定一个值，根据该值是否在Triangular数列内而返回true或false
	{
		if (!_elems.size() || _elems[_elems.size() - 1] < value)//Tri这个数列是递增的，如果最后一个元素小于给定的value，说明不在，如果空，那value也是不在
			gen_elements_to_value(value);

		vector<int>::iterator fount_it;
		vector<int>::iterator end_it = _elems.end();

		fount_it = find(_elems.begin(), end_it, value);
		return fount_it != end_it;
	}
	static void gen_elements_to_value(int value)//如果单独一个cpp定义，这个static可以不用单独再写
	{
		//作用：当传入value给一个数组时，这个递增数组并没有到达value这个值，所以将这个数组扩展
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
	//通过建立友元关系来让另一个类访问本类的私有成员
	friend int tri_iterator::operator*() const;
	friend void tri_iterator::check_integrity() const;
	//friend class tri_iterator;
	//static vector<int> _elems;
	//static const int _max_elems{ 1024 };
private:
	int _length;//元素的个数
	int _beg_pos;//起始位置
	int _next; //下一个迭代目标
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
	LessThan(int val) : _val(val) {};//不适用默认的构造函数，就是初始化时候一定要带有这个参数
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


class num_sequence//抽象基类
{
public:
	virtual ~num_sequence() {};
	//虚函数赋值为0表示他是一个纯虚函数，表示这个虚函数对于这个类没有实际的意义，纯虚函数没有定义
	virtual int elem(int pos) const = 0;//返回用户指定位置上的元素
	
	virtual const char* what_am_i() const = 0;//返回一个字符串代表数列的名称
	virtual ostream& print(ostream& os = cout) const;

	virtual num_sequence* clone() = 0;//这里基类的方法返回值是一个基类，派生类继承时，clone函数可返回一个指针指向num_sequence派生出来的任何一个派生类

	int length() const
	{
		return _length;
	}

	int beg_pos() const
	{
		return _beg_pos;
	}
	
	static int max_elems()//返回最大元素个数
	{
		return _max_elems;
	}

protected:
	virtual void gen_elems(int pos) const = 0;//产生数列元素
	num_sequence(int len, int bp, vector<int>& re) : _length(len), _beg_pos(bp), _relems(re) {}
	bool check_integrity(int pos) const//判断传入pos是否是有效位置
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
	vector<int>& _relems;// 用来指向派生类某个static vector,引用无法代表空对象，指针有可能是空

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
	static void lchild_leaf(BTnode* leaf, BTnode* subtree)//剥离左子叶节点
	{
		while (subtree->_lchild)
			subtree = subtree->_lchild;//找到左子树倒数第二层
		subtree->_lchild = leaf;//将左子叶节点赋值为leaf这个节点，实现剥离

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

	friend ostream& operator<< (ostream& os, const BinaryTree& bt)//为了让<<重载函数能够顺利调用print，因此声明为print
	{
		os << "Tree:" << endl;
		bt.print(os);
		return os;

		//运用：BinaryTree<string> bts; cout << bts << endl;
	}

private:
	valtype _val;
	int _cnt;
	BTnode* _lchild;
	BTnode* _rchild;
};


//实现一个模板类
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
	void copy(BTnode<elemType>*tar, BTnode<elemType>*src);//将src所指的子树，复制到tar所指的子树
	void clear(BTnode<elemType>*);

}







//int *func()
//{
	//int *a = new int(10);
	//return a;
//}





