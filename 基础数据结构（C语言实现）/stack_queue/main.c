#define _CRT_SECURE_NO_WARNINGS 1
#include "stack.h"

void test_stack() {
	ST st;
	STInit(&st);

	STPush(&st, 1);
	STPush(&st, 2);
	STPush(&st, 3);
	STPush(&st, 4);
	STPush(&st, 5);

	while (!STEmpty(&st)) {
		printf("%d", STTop(&st));
		STPop(&st);
	}
}

int main() {

	test_stack();
	return 0;
}