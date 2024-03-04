#pragma once
#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>
using namespace std;

#include <cstdlib>

template<class K, class V>
struct AVLTreeNode {
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;
	AVLTreeNode(const pair<K, V>& kv) : _kv(kv), _left(nullptr), _right(nullptr), _parent(nullptr), _bf(0) {}
};

template<class K, class V>
class AVLTree {
	typedef AVLTreeNode<K, V> Node;
public:
	bool insert(const pair<K, V>& kv) {
		if (_root == nullptr) {
			_root = new Node(kv);
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
		while (parent) {
			if (cur == parent->_left) {
				parent->_bf--;
			} else if (cur == parent->_right) {
				parent->_bf++;
			}
			if (parent->_bf == 0) break;

			if (abs(parent->_bf) == 2) {
				if (parent->_bf == 2 && cur->_bf == 1) {
					RotateLeft(parent);
				} else if (parent->_bf == 2 && cur->_bf == -1) {
					RotateRightToLeft(parent);
				} else if (parent->_bf == -2 && cur->_bf == -1) {
					RotateRight(parent);
				} else if (parent->_bf == -2 && cur->_bf == 1) {
					RotateLeftToRight(parent);
				}
				break;
			} else if (abs(parent->_bf) == 1) {
				cur = parent;
				parent = parent->_parent;
			} else assert(false);
		}
		return true;

	}

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
		cur->_bf = parent->_bf = 0;
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
		cur->_bf = parent->_bf = 0;
	}
	void RotateRightToLeft(Node* parent) {
		Node* cur = parent->_right;
		int bf = cur->_left->_bf;
		RotateRight(cur);
		RotateLeft(parent);

		if (bf == 1) {
			parent->_bf = -1;
		} else if (bf == -1) {
			cur->_bf = 1;
		}
	}
	void RotateLeftToRight(Node* parent) {
		Node* cur = parent->_left;
		int bf = cur->_right->_bf;
		RotateLeft(cur);
		RotateRight(parent);
		if (bf == 1) {
			cur->_bf = -1;
		} else if (bf == -1) {
			parent->_bf = 1;
		}
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
	int _isBalance(Node* root) {
		if (root == nullptr) return 0;
		int l = _isBalance(root->_left);
		int r = _isBalance(root->_right);
		if (abs(r - l) >= 2 || r - l != root->_bf) return -1;
		return max(r, l) + 1;
	}
	bool isBalance() {
		return _isBalance(_root) != -1;
	}
private:
	Node* _root = nullptr;
};
