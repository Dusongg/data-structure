#define _CRT_SECURE_NO_WARNINGS 1
#include "SList.h"

void test1() {
	SListNode* dummy = BuySListNode(-1);

	SListPushBack(&dummy, 1);
	SListPushBack(&dummy, 2);
	SListPushBack(&dummy, 3);
	SListPushBack(&dummy, 4);
	SListPopFront(&dummy);
	SListPushFront(&dummy, 5);
	SListPrint(dummy);

	SListPopBack(&dummy);
	SListPrint(dummy);

	SListPopFront(&dummy);
	SListPrint(dummy);

	SListDestroy(dummy);
}

int main() 
{
	test1();

	return 0;
}