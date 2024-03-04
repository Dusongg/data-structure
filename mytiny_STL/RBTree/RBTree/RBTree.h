#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
enum Color {
	RED,
	BLACK
};
template<class K, class V> 
struct RBTreeNode {
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	Color _col;
	RBTreeNode(const pair<K, V>& kv) : _left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _col(RED) {}
};
template<class K, class V> 
class RBTree {
	typedef RBTreeNode<K, V> Node;
public:
	bool insert(const pair<K, V>& kv) {
		if (_root == nullptr) {
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* cur = _root, * parent = nullptr;
		while (cur) {
			if (cur->_kv.first > kv.first) {
				parent = cur;
				cur = cur->_left;
			} else if (cur->_kv.first < kv.first) {
				parent = cur;
				cur = cur->_right;
			} else {				
				return false;
			}
		}
		cur = new Node(kv);
		(parent->_kv.first > kv.first ? parent->_left : parent->_right) = cur;
		cur->_parent = parent;
		
		while (parent && parent->_col == RED) {
			Node* grandfather = parent->_parent, * uncle = grandfather->_left == parent ? grandfather->_right : grandfather->_left;
			if (uncle && uncle->_col == RED) {
				parent->_col = uncle->_col = BLACK;
				grandfather->_col = RED;
				cur = grandfather;
				parent = cur->_parent;
			}
			else {   //uncle == nullptr || uncle->_col == BLACK
				if (grandfather->_left == parent && parent->_left == cur) {
					RotateRight(grandfather);
					parent->_col = BLACK;
				}
				else if (grandfather->_left == parent && parent->_right == cur) {
					RotateLeft(parent);
					RotateRight(grandfather);
					cur->_col = BLACK;

				} 
				else if (grandfather->_right == parent && parent->_right == cur) {
					RotateLeft(grandfather);
					parent->_col = BLACK;
				}
				else if (grandfather->_right == parent && parent->_left == cur) {
					RotateRight(parent);
					RotateLeft(grandfather);
					cur->_col = BLACK;
				}
				grandfather->_col = RED;
				break;
			}
		}
		_root->_col = BLACK;
		return true;

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
		parent->_right = cur_l;
		if (cur_l) cur_l->_parent = parent;
		cur->_left = parent;
		parent->_parent = cur;
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
	Node* _root = nullptr  ;
};