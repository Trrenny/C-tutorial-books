
#include"swap.h"

template <typename elemtype>
inline BinaryTree<elemtype>::BinaryTree() :_root{ 0 }
{}

template <typename elemType>
inline BinaryTree<elemType>::BinaryTree( const BinaryTree &rhs )
{
	copy(_root, rhs._root);
}

template <typename elemType>
inline BinaryTree<elemType>::~BinaryTree()
{
	clear();
}

template <typename elemType>
inline BinaryTree<elemType>& BinaryTree<elemType>::operator=(const BinaryTree& rhs)
{
	if (this != &rhs)
	{
		clear();
		copy(_root, rhs._root);
	}

	return *this;
}

template <typename elemType>
inline void BinaryTree<elemType>::insert(const elemType& elem)
{
	if (!_root)
		_root = new BTnode<elemType>(elem);
	else
		_root->insert_value(elem);
}

template<typename elemType>
void BinaryTree<elemType>::clear(BTnode<elemType> *pt)
{
	if (pt)
	{
		clear(pt->_lchild);
		clear(pt->_rchild);
		delete pt;
	}

}

template <typename valType>
inline BTnode<valType>::BTnode(const valType &val):_val(val)
{
	_cnt = 1;
	_lchild = _rchild = 0;
}

template<typename valtype>
void BTnode<valtype>::insert_value(const valtype& val)
{
}

template<typename valtype>
void BTnode<valtype>::remove(const valtype& val)
{
	if (!_root)
	{
		if (_root->_val == val)
			remote_root();//根节点的删除做特殊的函数处理，因为他跟其他节点的删除不一样

		else
			_root->remove_value(elem, _root);//从根节点这里开始向下搜索，直到找到，然后删除，递归调用
	}

	
}

template<typename valtype>
void BTnode<valtype>::remove_root(const valtype &val)
{
	if (!_root)
		return;

	BTnode<valtype>* temp = _root;
	if (_root->_rchild)
	{
		_root = _root->_rchild;//如果右子树存在，删除根节点，将右边的子树移上来取代根节点

		//将左子树接上右子树
		if (temp->_lchild)
		{
			BTnode<valtype>* lc = temp->_lchild;
			BTnode<valtype>* newlc = _root->_lchild;
			if (!newlc)
				_root->_lchild = lc;//如果没有左子树，就直接接上
			else
				BTnode<valtype>::lchild_leaf(lc, newlc);//将其接在原来右子树最左边的最下面
		}

	}

	else
		_root = _root->_lchild;//若果没有右子树，接上左子树

	delete temp;
		
}

template<typename valtype>
void BTnode<valtype>::remove_value(const valtype& val, BTnode<valtype>*& prev)
{
	if (_val < val)
	{
		if (!_lchild)
			return;
		else
			_lchild->remove_value(val,_lchild);
	}

	else if (_val > val)
	{
		if (!rchild)
			return;
		else
			_rchild->remove_value(val,_rchild);

	}

	else//找到该值了
	{
		if (!_rchild)
		{
			prev = _rchild;
			if(!_lchild)
			{
				if (!prev->_lchild)
				{
					prev->_lchild = _lchild;
				}
				else
				{
					BTnode<valtype>::lchild_leaf(_lchild, prev->_lchild);
				}
			}
		}

		else
		{
			prev = _lchild;
		}

		delete this;//删除这个类，这个类就是这个节点
	}




}

template <typename valType>
inline void BTnode<valType>::insert_value(const valType& val)
{
	if (val == _val)
	{
		_cnt++;
		return;
	}

	if (val < _val)
	{
		if (!_lchild)
			_lchild = new BTnode(val);

		else
			_lchild->insert_value(val);

	}

	else
	{
		if (!_rchild)
			_rchild = new BTnode(val);
		else
			_rchild->insert_value(val);
	}
}

