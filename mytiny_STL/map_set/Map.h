#pragma once
#include "RBTree.h"
namespace mymap {
	template<class K, class V>
	class map {
		struct MapKeyofT {
			const K& operator()(const pair<K, V>& kv) {
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<K, pair<const K, V>, MapKeyofT>::iterator iterator;
		typedef typename RBTree<K, pair<const K, V>, MapKeyofT>::const_iterator const_iterator;
		iterator find(const K& key) {
			return _t.find(key);
		}
		iterator begin() {
			return _t.begin();
		}
		iterator end() {
			return _t.end();
		}
		const_iterator begin() const {
			return _t.begin();
		}
		const_iterator end() const {
			return _t.end();
		}
		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return _t.insert(kv);
		}
		V& operator[](const K& key) {
			pair<iterator, bool> ret = _t.insert(make_pair(key, V()));
			return ret.first->second;
		}
	private:
		RBTree<K, pair<const K, V>, MapKeyofT> _t;
	};
}