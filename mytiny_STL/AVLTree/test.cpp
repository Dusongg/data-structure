#define _CRT_SECURE_NO_WARNINGS 1
#include "AVL.h"
int main() {
	AVLTree<int, int> t;
	//int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 6, 16, 14 };
	vector<int> v;
	srand(time(NULL));
	for (int i = 0; i < 10000; i++) {
		v.push_back(rand());
	}
	for (auto x : v) {
		t.insert(make_pair(x, x));
	}
	cout << t.isBalance();
	//t.Levelorder();
 	return 0;
}