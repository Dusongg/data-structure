#define _CRT_SECURE_NO_WARNINGS 1

#include "SList.h"

SListNode* BuySListNode(SLTDateType x) {
	SListNode* newnode = (SListNode*)malloc(sizeof(SListNode));
	if (newnode == NULL) {
		perror("malloc fail");
		return;
	}
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}


void SListPrint(SListNode* plist) {
	for (SListNode* tmp = plist->next; tmp; tmp = tmp->next) {
		if (tmp != NULL)
			printf("%d -> ", tmp->data);
	}
	printf("NULL\n");
}


void SListPushBack(SListNode** pplist, SLTDateType x) {
	assert(pplist);

	SListNode* tmp = *pplist;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = BuySListNode(x);
}


void SListPushFront(SListNode** pplist, SLTDateType x) {
	assert(pplist);

	SListNode* newnode = BuySListNode(x);
	newnode->next = (*pplist)->next;
	(*pplist)->next = newnode;
}


void SListPopBack(SListNode** pplist) {
	assert((*pplist)->next);
	
	SListNode* tmp = *pplist;
	while (tmp->next->next) {
		tmp = tmp->next;
	}

	free(tmp->next);
	tmp->next = NULL;
}


void SListPopFront(SListNode** pplist) {
	assert(pplist);
	assert((*pplist)->next);

	SListNode* tmp = (*pplist)->next;
	(*pplist)->next = (*pplist)->next->next;
	free(tmp);
	tmp = NULL;
}


SListNode* SListFind(SListNode* plist, SLTDateType x) {
	for (SListNode* tmp = plist->next; tmp; tmp = tmp->next) {
		if (tmp->data == x) {
			return tmp;
		}
	}
	return NULL;
}


void SListInsertAfter(SListNode* pos, SLTDateType x) {
	assert(pos);

	SListNode* newnode = BuySListNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}


void SListEraseAfter(SListNode* pos) {
	assert(pos);
	assert(pos->next);

	SListNode* erasenode = pos->next;
	pos->next = pos->next->next;
	free(erasenode);
	erasenode = NULL;
}


void SListDestroy(SListNode* plist) {
	SListNode* tmp = plist;
	for (SListNode* cur = plist->next; cur; cur = cur->next) {
		free(tmp);
		tmp = cur;
	}
}
