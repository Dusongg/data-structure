#pragma once
#include "hashtable.h"
template<class K> 
class my_unordered_set {
	struct UnorderedSetKeyOfT {
		const K& operator() (const K& key) {
			return key;
		}
	};
public:
	typedef typename hashtable<K, K, UnorderedSetKeyOfT>::const_iterator iterator;
	typedef typename hashtable<K, K, UnorderedSetKeyOfT>::const_iterator const_iterator;

	iterator begin() const{
		return _ht.begin();
	}
	iterator end() const{
		return _ht.end();
	}
	iterator find(const K& key) {
		return _ht.find(key);
	}
	pair<iterator, bool> insert(const K& data) {
		return _ht.insert(data);
	}
private:
	hashtable<K, K, UnorderedSetKeyOfT> _ht;
};