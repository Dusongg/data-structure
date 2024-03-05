#pragma once
template<class K>
struct BSTNode {
	BSTNode(const K& key = K()) :_left(nullptr), _right(nullptr), _key(key) {}

	BSTNode<K>* _left;
	BSTNode<K>* _right;
	K _key;
};

template<class K>
class BSTree {
	typedef BSTNode<K> Node;
public:
	BSTree() :_root(nullptr) {}
	BSTree(const Node*& t) {
		_root = CopyTree();
	}
	~BSTree() {
		DestroyTree(_root);
	}
	BSTree<K>& operator=(BSTree<K> t) {
		swap(t._root, _root);
		return *this;
	}
	bool insert(const K& key) {
		if (_root == nullptr) {
			_root = new Node(key);
			return true;
		}

		Node* cur = _root;
		while (cur != nullptr) {
			if (cur->_key > key) {
				if (cur->_left == nullptr) {
					cur->_left = new Node(key);
					return true;
				}
				cur = cur->_left;
			} else if (cur->_key < key) {
				if (cur->_right == nullptr) {
					cur->_right = new Node(key);
					return true;
				}
				cur = cur->_right;
			} else {
				return false;
			}
		}
	}
	void inoder() {
		_inoder(_root);
	}
	void erase(const K& key) {
		_erase(_root, key);
	}
	Node* find(const K& key) {
		Node* cur = _root;
		while (!cur) {
			if (cur->_key > key) {
				cur = cur->_left;
			} else if (cur->_key < key) {
				cur = cur->_right;
			}
			else {
				return cur;
			}
		}
		return nullptr;
	}
private:
	void _inoder(Node* root) {
		if (root == nullptr) return;

		_inoder(root->_left);
		cout << root->_key << ' ';
		_inoder(root->_right);
	}
	Node* _erase(Node* root, const K& key) {
		if (root == nullptr) return nullptr;

		if (root->_key == key) {
			if (root->_right == nullptr) {
				return root->_left;
			}
			Node* cur = root->_right;
			while (cur->_left) {
				cur = cur->_left;
			}
			std::swap(cur->_key, root->_key);
		}
		root->_left = _erase(root->_left, key);
		root->_right = _erase(root->_right, key);
		return root;
	}
	void DestroyTree(Node*& node) {
		if (node == nullptr) return;

		DestroyTree(node->_left);
		DestroyTree(node->_right);
		delete node;
		node = nullptr;
	}

	Node* CopyTree(Node* node) {
		if (node == nullptr) return nullptr;

		Node* retnode = new Node(node->_key);
		retnode = CopyTree(node->_left);
		retnode = CopyTree(node->_right);
		return retnode;
	}
private:
	Node* _root;
};