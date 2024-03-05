#define _CRT_SECURE_NO_WARNINGS 1
#include "my_unordered_map.h"
//#include "my_unordered_set.h"
//#include "open_address_hashtable.h"
#include <iostream>
#include <functional>
#include <unordered_map>
using namespace std;
struct Test {
	string s;
	int n;
};

int main() {
	//mystl::unordered_map<int, int> m1 = { {1,1}, {12, 2} };
	//mystl::unordered_map<int, int> m2 = { {1,2}, {13, 2} };
	//mystl::unordered_map<int, int> m3(m2);
	//for (auto p : m3) {
	//	cout << p.first << ' ' << p.second << endl;
	//}

	Test t1{ "sf", 2 };
	Test t2{ "s2", 2 };
	Test t3{ "sd", 2 };
	function<size_t(const Test&)> hf = [](const Test& t) -> size_t {return mystl::hash<string>()(t.s); };
	function<bool(const Test&, const Test&)> eq = [](const Test& t1, const Test& t2) -> bool {return t1.s == t2.s; };
	mystl::unordered_map<Test, int, decltype(hf), decltype(eq)> ump(8, hf, eq);
	ump.insert({ t1, 2 });
	ump.insert({ t2, 2 });
	ump.insert({ t3, 2 });
	for (auto p : ump) {
		cout << p.first.s << ' ' << p.first.n << ' ' << p.second << endl;
	}

	return 0;
} 