#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

#include "Binary_Sreach_Tree.h"

int main() {
	BSTree<int> t;
	int a[] = { 1, 3, 54,6, 723, 5, 23 };
	for (auto x : a) {
		t.insert(x);
	}
	t.erase(1);
	t.erase(54);
	t.erase(723);
	t.erase(5);
	t.erase(23);


	t.inoder();
	return 0;
}