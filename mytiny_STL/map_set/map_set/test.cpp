#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "Map.h"
#include "Set.h"
int main() {
	mymap::map<int, int> m;
	for (int i = 0; i < 10; i++) {
		m.insert(make_pair(i, i));

	}

	m[1] = 10;
	m[2] = 10;
	auto fit = m.find(1);
	fit->second = 100;
	for (auto it = m.begin(); it != m.end(); ++it) {
		cout << it->first << ' '<<it->second << endl;
	}

	myset::set<int> s;
	for (int i = 0; i < 10; i++) {
		s.insert(i);
	}
	auto ffit = s.find(1);
	
	return 0;
}