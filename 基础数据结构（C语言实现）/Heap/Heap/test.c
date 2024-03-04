#define _CRT_SECURE_NO_WARNINGS 1
#include "heap.h"

int main() {
	srand(time(0));
	//Heap hp;
	//HeapInit(&hp);
	//HeapPush(&hp, 4);
	//HeapPush(&hp, 2);
	//HeapPush(&hp, 42);
	//HeapPush(&hp, 18);
	//HeapPush(&hp, 3);
	//HeapPush(&hp, 12);

	//while (!HeapEmpty(&hp)) {
	//	printf("%d", HeapTop(&hp));
	//	HeapPop(&hp);
	//}
	TestTopk();
	return 0;
}