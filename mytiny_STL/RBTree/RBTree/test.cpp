#define _CRT_SECURE_NO_WARNINGS 1
#include "RBTree.h"

int main() {

	RBTree<int, int> t;
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 6, 16, 14 };

	for (auto x : arr) {
		t.insert(make_pair(x, x));
	}
	t.Levelorder();
	cout << t.heigh();
	return 0;
	return 0;
}