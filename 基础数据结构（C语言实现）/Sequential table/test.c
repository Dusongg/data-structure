#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"

void test() {
	SeqList list;
	SeqListInit(&list);
	SeqListPushBack(&list, 2);
	SeqListPushBack(&list, 2);
	SeqListPushBack(&list, 2);
	SeqListPushBack(&list, 2);
	SeqListPushBack(&list, 2);
	SeqListPushBack(&list, 2);
	SeqListPrint(&list);
}

int main() 
{
	test();
	return 0;
}