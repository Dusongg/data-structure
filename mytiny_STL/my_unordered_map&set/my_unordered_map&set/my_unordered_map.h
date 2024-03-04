#pragma once
#include "hashtable.h"
#include <initializer_list>
namespace mystl {
	template<class Key>
	struct hash {
		size_t operator() (const Key& key) {
			return (size_t)key;
		}
	};
	template<>
	struct hash<string> {
		size_t ret = 0;
		size_t operator() (const string& key) {
			for (auto c : key) {
				ret *= 131;
				ret += c;
			}
			return ret;
		}
	};
	template <class T> 
	struct equal_to {
		bool operator() (const T& x, const T& y) const { return x == y; }
	};

	template<class Key, class T, class Hash = hash<Key>, class Pred = equal_to<Key>>
	class unordered_map {
		typedef Key key_type;
		typedef T  value_type;
		typedef Hash hasher;
		typedef Pred key_equal;
		struct UnorderedMapKeyOfT {
			const Key& operator() (const pair<Key, T>& data) {
				return data.first;
			}
		};
	public:
		typedef typename hashtable<Key, pair<const Key, T>, Hash, Pred, UnorderedMapKeyOfT>::iterator iterator;
		typedef typename hashtable<Key, pair<const Key, T>, Hash, Pred, UnorderedMapKeyOfT>::const_iterator const_iterator;
		/*empty*/
		explicit unordered_map(size_t n, const hasher& hf = hasher(), const key_equal& eql = key_equal()) 
			: _ht(n, hf, eql) {}
		explicit unordered_map() {}
		/*range*/
		unordered_map(iterator first, iterator last, size_t n = 8, const hasher& hf = hasher(), const key_equal& eql = key_equal())
		:_ht(n, hf, eql) {
			for (; first != last; first++) {
				_ht.insert(*first);
			}
		}
		/*copy*/
		unordered_map(unordered_map& ump) {
			for (auto p : ump) {
				_ht.insert({p.first, p.second});
			}
		}
		/*initializer_list*/
		unordered_map(initializer_list<pair<const Key, T>> init_lt, size_t n = 8, const hasher& hf = hasher(), const key_equal& eql = key_equal()) 
		: _ht(n, hf, eql) {
			for (auto& t : init_lt) {
				_ht.insert(t);
			}
		}

		iterator begin() { return _ht.begin(); }
		iterator end() { return _ht.end(); }
		const_iterator begin() const { return _ht.begin(); }
		const_iterator end() const { return _ht.end(); }

		iterator find(const Key& key) { return _ht.find(key); }

		T& operator[](const Key& key) {
			auto it = _ht.insert(make_pair(key, T()));
			return it.first->second;
		}

		pair<iterator, bool> insert(const pair<Key, T>& data) {
			pair<typename hashtable<Key, pair<const Key, T>, Hash, Pred, UnorderedMapKeyOfT>::iterator, bool> ret = _ht.insert(data);
			return make_pair(iterator(ret.first), ret.second);
			//return _ht.insert(data);   等同，因为会隐式类型转换
		}

		template<class... Args>
		pair<iterator, bool> emplace(Args &&...args) {
			return _ht.emplace(forward<Args>(args...));    //是否需要完美转发
		}

		size_t bucket_count() { return _ht.bucket_count(); }
		size_t max_bucket_count() { return _ht.max_bucket_count(); }
		size_t bucket_size(size_t n) { return _ht.bucket_size(n); }
		size_t bucket(key_type key) { return _ht.bucket(key); }
	private:
		hashtable<Key, pair<const Key, T>, Hash, Pred, UnorderedMapKeyOfT> _ht;
	};
}