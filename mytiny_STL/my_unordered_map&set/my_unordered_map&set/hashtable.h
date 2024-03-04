#pragma once
#define __max_bucket_count 536870911
#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace mystl {
	template<class T>
	struct HashNode {
		HashNode(const T& data) : _data(data), next(nullptr) {}
		T _data;
		HashNode<T>* next;
	};

	template<class Key, class T, class Hash, class Pred, class KeyOfT>
	class hashtable;

	//通过iterator与const_iterator指定ptr与ref
	template<class Key, class T, class Ptr, class Ref, class Hash, class Pred, class KeyOfT>
	struct __hashtable_iterator {
		typedef HashNode<T> Node;
		typedef __hashtable_iterator<Key, T, Ptr, Ref, Hash, Pred, KeyOfT> Self;
		typedef __hashtable_iterator<Key, T, T*, T&, Hash, Pred, KeyOfT> iterator;

		Node* cur;
		hashtable<Key, T, Hash, Pred, KeyOfT>* pht;
		Hash hasher;
		KeyOfT get_key;

		__hashtable_iterator(const iterator& it) : cur(it.cur), pht(it.pht) {}
		__hashtable_iterator(Node* node, hashtable<Key, T, Hash, Pred, KeyOfT>* p) : cur(node), pht(p) {}  //传this指针

		Self& operator++();
		bool operator!=(const Self& it) { return cur != it.cur; }
		Ref operator*() { return cur->_data; }
		Ptr operator->() { return &(cur->_data); }
	};

	template<class Key, class T, class Hash, class Pred, class KeyOfT>
	class hashtable {
		typedef HashNode<T> Node;

		//友元类为类模板时需要带上模板参数
		template<class Key, class T, class Ptr, class Ref, class Hash, class Pred, class KeyOfT>
		friend struct __hashtable_iterator;

	public:
		typedef __hashtable_iterator<Key, T, T*, T&, Hash, Pred, KeyOfT> iterator;
		typedef __hashtable_iterator<Key, T, const T*, const T&, Hash, Pred, KeyOfT> const_iterator;

		iterator begin() {
			for (int i = 0; i < buckets.size(); i++) {
				if (buckets[i]) return iterator(buckets[i], this);
			}
			return iterator(nullptr, this);
		}
		iterator end() {
			return iterator(nullptr, this);
		}
		const_iterator begin() const {
			for (int i = 0; i < buckets.size(); i++) {
				if (buckets[i]) return iterator(buckets[i], this);
			}
			return const_iterator(nullptr, this);
		}
		const_iterator end() const {
			return const_iterator(nullptr, this);
		}

		hashtable() { buckets.resize(10, nullptr); }
		hashtable(size_t n, Hash hasher, Pred key_equal)
			: hasher(hasher), key_equal(key_equal)
		{
			buckets.resize(max((size_t)8, n), nullptr);
		}
		~hashtable() {
			clear();
		}
		hashtable& operator=(hashtable& ht) {
			if (&ht != this) {
				clear();
				hasher = ht.hasher;
				key_equal = ht.key_equal;
				get_key = ht.get_key;
				copy_from(ht);
			}
			return *this;
		}
	private:
		size_t bkt_num_key(const Key& key) {
			return hasher(key);
		}
		void clear() {
			for (int i = 0; i < buckets.size(); i++) {
				Node* cur = buckets[i];
				while (cur) {
					Node* next = cur->next;
					delete cur;
					cur = next;
				}
				buckets[i] = nullptr;
			}
			count = 0;
		}
		void copy_from(hashtable& ht) {
			buckets.clear();
			buckets.reserve(ht.buckets.size());
			buckets.insert(buckets.end(), ht.buckets.size(), nullptr);   //?
			for (size_t i = 0; i < ht.buckets.size(); i++) {
				if (const Node* cur = ht.buckets[i]) {
					Node* copy = new Node(cur->_data);
					buckets[i] = copy;
					for (Node* next = cur->next; next; next = next->next) {
						copy->next = new Node(next->_data);
						copy = copy->next;
					}
				}
			}
			count = ht.count;
		}
	public:
		iterator find(const Key& key) {
			Node* cur = buckets[hasher(key) % buckets.size()];
			while (cur) {
				if (key_equal(get_key(cur->_data), key)) return iterator(cur, this);
				cur = cur->next;
			}
			return iterator(nullptr, this);
		}
		bool erase(const Key& key) {
			size_t hash_i = hasher(key) % buckets.size();
			Node* pre = nullptr, * cur = buckets[hash_i];
			while (cur) {
				if (get_key(cur->_data) == key) {
					if (pre == nullptr) buckets[hash_i] = cur->next;
					else pre->next = cur->next;
					delete cur;
					count--;
					return true;
				}
			}
			return false;
		}
		pair<iterator, bool> insert(const T& data) {
			size_t n = buckets.size();
			auto it = find(get_key(data));
			if (it != end()) return make_pair(it, false);

			if (count == n) {
				size_t newsize = n * 2;
				vector<Node*> newbuckets(newsize, nullptr);
				//不去调用insert，因为会重新new节点，浪费空间，并且需要释放之前的节点
				for (int i = 0; i < n; i++) {
					Node* cur = buckets[i];
					while (cur) {
						Node* next = cur->next;
						size_t hash_i = hasher(get_key(cur->_data)) % newsize;
						cur->next = newbuckets[hash_i];
						newbuckets[hash_i] = cur;
						cur = next;
					}
				}
				buckets.swap(newbuckets);
			}
			size_t hash_i = hasher(get_key(data)) % buckets.size();
			Node* newnode = new Node(data);
			newnode->next = buckets[hash_i];
			buckets[hash_i] = newnode;
			count++;
			return make_pair(iterator(newnode, this), true);
		}


		bool empty()const { return count == 0; }
		//正在使用的桶的数目
		size_t bucket_count() {
			size_t ret = 0;
			for (auto& bucket : buckets) if (bucket) ++ret;
			return ret;
		}
		//容器能容纳的最多的桶的数量
		size_t max_bucket_count() { return __max_bucket_count; }
		//第n个桶中有多少个元素
		size_t bucket_size(size_t n) {
			if (n >= buckets.size()) return 0;
			size_t ret = 0;
			Node* cur = buckets[n];
			while (cur) {
				ret++;
				cur = cur->next;
			}
			return ret;
		}
		//关键字为k的元素在哪个桶中
		size_t bucket(Key key) { return hasher(key) % buckets.size(); }

	private:
		vector<Node*> buckets;
		size_t count = 0;
		Hash hasher;
		Pred key_equal;
		KeyOfT get_key;
	};

	template<class Key, class T, class Ptr, class Ref, class Hash, class Pred, class KeyOfT>
	__hashtable_iterator<Key, T, Ptr, Ref, Hash, Pred, KeyOfT>&
		__hashtable_iterator< Key, T, Ptr, Ref, Hash, Pred, KeyOfT>::operator++() {
		const Node* old = cur;
		cur = cur->next;
		if (cur == nullptr) {
			size_t bucket = pht->bkt_num_key(get_key(old->_data));
			while (cur == nullptr && ++bucket < pht->buckets.size())
				cur = pht->buckets[bucket];
		}
		return *this;
	}

}