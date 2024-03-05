#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <list>
using namespace std;

#include "list.h"

int main() {
	mylist::list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_front(23);

	mylist::list<int>::iterator it = l1.begin();   //øΩ±¥ππ‘Ï£∫«≥øΩ±¥
	for (auto it = l1.begin(); it != l1.end(); ++it) {
		cout << (*it) << ' ';
	}
	cout << endl;  


	cout << l1.size() << endl;
	/*const mylist::list<int> l2;
	for (auto it = l2.begin(); it != l2.end(); ++it) {
		cout << (*it) << ' ';
	}*/
	l1.clear();
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	for (auto rit = l1.rbegin(); rit != l1.rend(); ++rit) {
		cout << *(rit) << ' ';
	}
	cout << endl;
	return 0;
}