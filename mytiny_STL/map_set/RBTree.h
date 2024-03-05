#pragma once
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
enum Color {
	RED,
	BLACK
};
template<class T>
struct RBTreeNode {
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	T _data;
	Color _col;
	RBTreeNode(const T& data) : _left(nullptr), _right(nullptr), _parent(nullptr), _data(data), _col(RED) {}
};



template<class T, class Ptr, class Ref>
struct __RBTreeIterator {
	typedef RBTreeNode<T> Node;
	Node* _node;
	typedef __RBTreeIterator<T, T*, T&> iterator;
	typedef __RBTreeIterator<T, Ptr, Ref> Self;

	//当该类实例化为const迭代器时，有以下两种情况调用函数：
	//1.当传入const迭代器时，相当于拷贝构造
	//2.当传入普通迭代器时，相当于用普通迭代器构造const迭代器
	//无论是什么迭代器，typedef __RBTreeIterator<T, T*, T&> iterator 均为普通迭代器，以完成构造
	__RBTreeIterator(const iterator& it) :_node(it._node) {}
	__RBTreeIterator(Node* node) : _node(node) {}
	Ref operator*() {
		return _node->_data;
	}
	Ptr operator->() {    //const T*   T* const
		return &_node->_data;
	}

	bool operator!=(const Self& it) {
		return _node != it._node;
	}

	//前置++， 找下一个比_node大的节点，
	//1.右边不为空，找右边最小
	//2.右边为空，往上找大，parent的左节点为cur
	Self& operator++() {  
		if (_node->_right) {
			Node* leftmin = _node->_right;
			while (leftmin->_left) {
				leftmin = leftmin->_left;
			}
			_node = leftmin;
		} else {
			Node* parent = _node->_parent, * cur = _node;
			while (parent) {
				if (cur == parent->_left) break;
				else {
					cur = parent;
					parent = parent->_parent;
				}
			}
			_node = parent;
		}
		return *this;
	}
	
	Self& operator--() {
		if (_node->_left) {
			Node* rightmax = _node->_left;
			while (rightmax->_right) {
				rightmax = rightmax->_right;
			}
			_node = rightmax;
		} else {
			Node* parent = _node->_parent, * cur = _node;
			while (parent) {
				if (cur == parent->_right) break;
				else {
					cur = parent;
					parent = parent->_parent;
				}
			}
			_node = parent;
		}
		return *this;
	}
};



template<class K, class T, class KeyOfT>
class RBTree {
	typedef RBTreeNode<T> Node;
public:
	typedef __RBTreeIterator<T, T*, T&> iterator;
	typedef __RBTreeIterator<T, const T*, const T&> const_iterator;

	iterator begin() {
		Node* leftmin = _root;
		while (leftmin && leftmin->_left) {
			leftmin = leftmin->_left;
		}
		return leftmin;
	}
	iterator end() {
		return nullptr;
	}
	const_iterator begin() const{
		Node* leftmin = _root;
		while (leftmin && leftmin->_left) {
			leftmin = leftmin->_left;
		}
		return leftmin;
	}
	const_iterator end() const{
		return nullptr;
	}

	iterator find(const K& key) {
		Node* cur = _root;
		KeyOfT kot;
		while (cur) {
			if (kot(cur->_data) > key) {
				cur = cur->_left;
			} else if (kot(cur->_data) < key) {
				cur = cur->_right;
			} else return iterator(cur);
		}
		return nullptr;
	}
	pair<iterator, bool> insert(const T& data) {
		KeyOfT kot;
		//空树情况
		if (_root == nullptr) {
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(_root, true);
		}
		//寻找插入位置
		Node* cur = _root, * parent = nullptr;
		while (cur) {
			if (kot(cur->_data) > kot(data)) {
				parent = cur;
					cur = cur->_left;
			} else if (kot(cur->_data) < kot(data)) {
					parent = cur;
						cur = cur->_right;
				} else {
					return make_pair(cur, false);
				}
		}
		//创建节点并插入
		cur = new Node(data);
		(kot(parent->_data) > kot(data) ? parent->_left : parent->_right) = cur;
		cur->_parent = parent;
		Node* newnode = cur;   //cur节点会变，新节点保存到newnode，用于返回构造iterator

		while (parent && parent->_col == RED) {
			Node* grandfather = parent->_parent, * uncle = grandfather->_left == parent ? grandfather->_right : grandfather->_left; 
			if (uncle && uncle->_col == RED) {
				parent->_col = uncle->_col = BLACK;
				grandfather->_col = RED;
				cur = grandfather;
				parent = cur->_parent;
			} else {   //uncle == nullptr || uncle->_col == BLACK
				if (grandfather->_left == parent && parent->_left == cur) {
					RotateRight(grandfather);
					parent->_col = BLACK;
				} else if (grandfather->_left == parent && parent->_right == cur) {
					RotateLeft(parent);
					RotateRight(grandfather);
					cur->_col = BLACK;

				} else if (grandfather->_right == parent && parent->_right == cur) {
					RotateLeft(grandfather);
					parent->_col = BLACK;
				} else if (grandfather->_right == parent && parent->_left == cur) {
					RotateRight(parent);
					RotateLeft(grandfather);
					cur->_col = BLACK;
				}
				grandfather->_col = RED;
				break;
			}
		}
		_root->_col = BLACK;
		return make_pair(iterator(newnode), true);
	}
	void Levelorder() {
		queue<Node*> q;
		if (_root) q.push(_root);
		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				Node* node = q.front();
				q.pop();
				cout << node->_kv.first << ' ';
				if (node->_left) q.push(node->_left);
				if (node->_right) q.push(node->_right);
			}
			cout << endl;
		}
	}
	int heigh(Node* node) {
		if (node == nullptr) return 0;
		int l = heigh(node->_left);
		int r = heigh(node->_right);
		return max(l, r) + 1;
	}
	int heigh() {
		return heigh(_root);
	}
private:
	void RotateLeft(Node* parent) {
		Node* cur = parent->_right, * cur_l = cur->_left, * ppnode = parent->_parent;
		//第一步：将cur的左节点与cur的parent相连
		parent->_right = cur_l;
		if (cur_l) cur_l->_parent = parent;
		//第二步：将parent连到cur的左边
		cur->_left = parent;
		parent->_parent = cur;
		//第三步将parent的parent与cur相连：两种情况
		if (parent == _root) {
			_root = cur;
			cur->_parent = nullptr;
		} else {
			(ppnode->_left == parent ? ppnode->_left : ppnode->_right) = cur;
			cur->_parent = ppnode;
		}
	}
	void RotateRight(Node* parent) {
		Node* cur = parent->_left, * cur_r = cur->_right, * ppnode = parent->_parent;
		parent->_left = cur_r;
		if (cur_r) cur_r->_parent = parent;
		cur->_right = parent;
		parent->_parent = cur;
		if (parent == _root) {
			_root = cur;
			cur->_parent = nullptr;
		} else {
			(ppnode->_left == parent ? ppnode->_left : ppnode->_right) = cur;
			cur->_parent = ppnode;
		}
	}

private:
	Node* _root = nullptr;
};