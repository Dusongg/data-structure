#pragma once
#include <vector>
using namespace std;
enum STATE {
	EXIST,   //0
	EMPTY,   //1
	DELETE   //2
};
template<class Value>
struct hashdata {
	STATE _state = EMPTY;
	Value _data;
};
template<class Key, class Value, class KeyOfValue, class HashFunc>
class hashtable {
public:
	hashtable() {
		_ht.resize(100);
		count = 0;
	}
	bool insert(const Value& data) {
		KeyOfValue kov;
		if (find(kov(data))) return false;
		if (count * 10 / _ht.size() > 7) {
			hashtable<Key, Value, KeyOfValue, HashFunc> newhashtable;
			newhashtable._ht.resize(_ht.size() * 2);
			for (int i = 0; i < _ht.size(); i++) {
				if (_ht[i]._state == EXIST) {
					newhashtable.insert(_ht[i]._data);
				}
			}
		}
		HashFunc hf;
		int index = hf(kov(data));

	}
	Value& find(const Key& key) {

	}

private:
	vector<hashdata<Value>> _ht;
	size_t count;
};
