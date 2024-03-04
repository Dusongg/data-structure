#pragma once
#include "RBTree.h"
namespace myset {
	template<class K>
	class set {
		struct SetKeyOfT {
			const K& operator()(const K& key) {
				return key;
			}
		};
	public:
		typedef typename RBTree<K, K, SetKeyOfT>::const_iterator iterator;
		typedef typename RBTree<K, K, SetKeyOfT>::const_iterator const_iterator;
		iterator begin() const {
			return _t.begin();
		}
		iterator end() const {
			return _t.end();
		}
		pair<iterator, bool> insert(const K& key) {
			//返回普通迭代器，调用const迭代器的构造函数
			pair<typename RBTree<K, K, SetKeyOfT>::iterator, bool> ret = _t.insert(key);
			return pair<iterator, bool>(ret.first, true);
		}
		//typedef typename RBTree<K, K, SetKeyOfT>::const_iterator iterator;
		iterator find(const K& key) {   
			return _t.find(key);      //返回普通迭代器，调用const迭代器的构造函数
		}
	private:
		RBTree<K, K, SetKeyOfT> _t;
	};
}