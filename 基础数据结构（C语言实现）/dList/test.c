#define _CRT_SECURE_NO_WARNINGS 1
#include "dList.h"

void ListTest1() {
	ListNode* dummy = ListCreate(-1);
	ListPushBack(dummy, 1);
	ListPushBack(dummy, 3);
	ListPushBack(dummy, 2);
	ListPushBack(dummy, 4);
	ListPopFront(dummy);
	ListPushFront(dummy, 5);
	ListPrint(dummy);
	ListDestory(dummy);
}
int main() {
	ListTest1();
	return 0;
}