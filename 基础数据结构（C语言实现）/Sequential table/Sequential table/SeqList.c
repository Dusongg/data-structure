#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"

void SeqListIncrease(SeqList* ps) {
	SLDateType* tmp = (SLDateType*)realloc(ps->a, sizeof(SLDateType) * (ps->capacity + Increase));
	if (tmp == NULL) {
		perror("realloc fail");
		return;
	}
	ps->a = tmp;
	ps->capacity += Increase;
}

void SeqListInit(SeqList* ps) {
	ps->a = (SLDateType*)malloc(sizeof(SLDateType) * Capacity);
	if (!ps->a) {
		perror("malloc fail");
		return;
	}
	ps->capacity = Capacity;
	ps->size = 0;
}

void SeqListDestroy(SeqList* ps) {
	ps->capacity = ps->size = 0;
	free(ps);
	ps = NULL;
}

void SeqListPrint(SeqList* ps) {
	for (int i = 0; i < ps->size; i++) {
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}

void SeqListPushBack(SeqList* ps, SLDateType x) {
	if (ps->size == ps->capacity) {
		SeqListIncrease(ps);
	}
	ps->a[ps->size++] = x;
}

void SeqListPushFront(SeqList* ps, SLDateType x) {
	if (ps->size == ps->capacity) {
		SeqListIncrease(ps);
	}
	for (int i = ps->size; i >= 1; i++) {
		ps->a[i] = ps->a[i - 1];
	}
	ps->a[0] = x;
	ps->size++;
}

void SeqListPopFront(SeqList* ps) {
	assert(ps->size > 0);

	for (int i = 1; i < ps->size; i++) {
		ps->a[i - 1] = ps->a[i];
	}
	ps->size--;
}

void SeqListPopBack(SeqList* ps) {
	assert(ps->size > 0);

	ps->size--;
}

int SeqListFind(SeqList* ps, SLDateType x) {
	for (int i = 0; i < ps->size; i++) {
		if (ps->a[i] == x) return i;
	}
	return - 1;
}

void SeqListInsert(SeqList* ps, int pos, SLDateType x) {
	if (ps->size == ps->capacity) {
		SeqListIncrease(ps);
	}

	for (int i = ps->size - 1; i >= pos; i--) {
		ps->a[i + 1] = ps->a[i];
	}
	ps->a[pos] = x;
	ps->size++;
}

void SeqListErase(SeqList* ps, int pos) {
	assert(ps->size > 0);

	for (int i = pos + 1; i < ps->size; i++) {
		ps->a[i - 1] = ps->a[i];
	}
	ps->size--;
}
