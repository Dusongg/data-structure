#define _CRT_SECURE_NO_WARNINGS 1
#include "dList.h"
bool isEmpty(ListNode* pHead) {
	return pHead->next == pHead;
}

ListNode* ListCreate(int x) {
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	if (newnode == NULL) {
		perror("malloc fail");
		return;
	}
	newnode->next = newnode;
	newnode->prev = newnode;
	newnode->val = x;
	return newnode;
}

void ListPrint(ListNode* pHead) {
	ListNode* cur = pHead->next;
	printf("dummy<=>");
	while (cur != pHead) {
		printf("%d<=>", cur->val);
		cur = cur->next;
	}
	return;
}

void ListPushBack(ListNode* pHead, LTDataType x) {
	/*ListNode* newnode = ListCreate(x);
	ListNode* last = pHead->prev;

	last->next = newnode;
	newnode->prev = last;
	newnode->next = pHead;
	pHead->prev = newnode;*/

	ListInsert(pHead, x);
}

void ListPopBack(ListNode* pHead) {
	/*assert(!isEmpty(pHead));

	ListNode* last = pHead->prev;
	ListNode* Llast = pHead->prev->prev;

	Llast->next = pHead;
	pHead->prev = Llast;
	free(last);
	last = NULL;*/

	ListErase(pHead);
}

void ListPushFront(ListNode* pHead, LTDataType x) {
	//ListNode* newnode = ListCreate(x);

	//newnode->next = pHead->next;
	//pHead->next->prev = newnode;
	//pHead->next = newnode;
	//newnode->prev = pHead;

	ListInsert(pHead->next,x);
}

void ListPopFront(ListNode* pHead) {
	/*assert(!isEmpty(pHead));

	ListNode* front = pHead->next;
	pHead->next = front->next;
	front->prev = pHead;
	free(front);
	front = NULL;*/

	ListErase(pHead->next);
}

ListNode* ListFind(ListNode* pHead, LTDataType x) {
	for (ListNode* cur = pHead->next; cur != pHead; cur = cur->next) {
		if (cur->val == x) {
			return cur;
		}
	}
	return NULL;
}

//ÔÚposÇ°²åÈë
void ListInsert(ListNode* pos, LTDataType x) {
	assert(pos);
	ListNode* newnode = ListCreate(x);
	ListNode* pre = pos->prev;

	newnode->next = pos;
	pos->prev = newnode;
	pre->next = newnode;
	newnode->prev = pre;
}

void ListErase(ListNode* pos) {
	assert(pos);
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
	pos = NULL;
}

void ListDestory(ListNode* pHead) {
	assert(pHead);
	ListNode* cur = pHead->next;
	while (cur != pHead)
	{
		ListNode* next = cur->next;
		free(cur);
		cur = NULL;
		cur = next;
	}
	free(pHead);
	pHead = NULL;
}
