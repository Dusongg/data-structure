#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int STDataType;

typedef struct Stack {
	int* a;
	int top;
	int capacity;
}ST;

void STInit(ST* ps);
void STDestroy(ST* ps);
void STPush(ST* ps, STDataType x);
void STPop(ST* ps);
int STSize(ST* ps);
bool STEmpty(ST* ps);
STDataType STTop(ST* ps);