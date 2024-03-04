#define _CRT_SECURE_NO_WARNINGS 1
#include "heap.h"
// 堆的初始化
void HeapInit(Heap* hp) {
	assert(hp);

	hp->a = (HPDataType*)malloc(sizeof(HPDataType) * 10);
	if (hp->a == NULL) {
		perror("malloc fail");    
		return;
	}
	hp->capacity = 10;
	hp->size = 0;
	return;

}

// 堆的销毁
void HeapDestory(Heap* hp) {
	assert(hp);
	free(hp->a);
	hp->a = NULL;
	hp->capacity = hp->size = 0;
}

void Swap(HPDataType* x, HPDataType* y) {
	HPDataType tmp = *x;
	*x = *y;
	*y = tmp;
}

//向上调整 -> 除了最后一个数据，其余都是大堆/小堆·
void AdjustUp(HPDataType* a, int child) {
	int parent = (child - 1) / 2;

	while (child > 0 && a[parent] < a[child]) {   //大顶堆
		Swap(&a[parent], &a[child]);
		child = parent;
		parent = (child - 1) / 2;
	}
}

// 堆的插入
void HeapPush(Heap* hp, HPDataType x) {
	assert(hp);
	if (hp->size == hp->capacity) {
		HPDataType* tmp = (HPDataType*)realloc(hp->a, sizeof(HPDataType) * (hp->capacity * 4));
		if (tmp == NULL) {
			perror("realloc fail");
			return;
		}
		hp->a = tmp;
		hp->capacity *= 4;
	}

	hp->a[hp->size++] = x;

	AdjustUp(hp->a, hp->size - 1);

}

//向下调整 -> 左右子树都是大堆/小堆
void AdjustDown(HPDataType* a, int parent, int n) {
	int child = parent * 2 + 1;

	while (child < n) {
		if (child + 1 < n && a[child] > a[child + 1]) {
			child++;
		}

		if (a[child] < a[parent]) {
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else break;
	}
}

// 堆的删除 -> 删除根
void HeapPop(Heap* hp) {
	assert(hp);
	assert(!HeapEmpty(hp));

	Swap(&hp->a[0], &hp->a[hp->size - 1]);
	hp->size--;

	AdjustDown(hp->a, 0, hp->size - 1);
}

// 取堆顶的数据
HPDataType HeapTop(Heap* hp) {
	assert(hp);
	return hp->a[0];
}

// 堆的数据个数
int HeapSize(Heap* hp) {
	assert(hp);
	return hp->size - 1;
}
// 堆的判空
bool HeapEmpty(Heap* hp) {
	assert(hp);
	return hp->size == 0;
}


void HeapSort(int* a, int n) {
	//向上调整建堆 —— O(N*logN )
	/*for (int i = 1; i < n; i++) {
		AdjustUp(a, i);
	}*/

	//向下调整建堆 —— O(N)
	for (int i = (n - 2) / 2; i >= 0; i--) {
		AdjustDown(a, i, n);
	}

	for (int j = n - 1; j > 0; j--) {
		Swap(&a[0], &a[j]);
		AdjustDown(a, 0, j);
	}
}
// TopK问题：找出N个数里面最大/最小的前K个问题。
// 比如：未央区排名前10的泡馍，西安交通大学王者荣耀排名前10的韩信，全国排名前10的李白。等等问题都是Topk问题，
// 需要注意：
// 找最大的前K个，建立K个数的小堆
// 找最小的前K个，建立K个数的大堆
void PrintTopK(const char* file, int k) {
	int* topK = (int*)malloc(sizeof(int) * k);
	assert(topK);

	FILE* fout = fopen(file, "r");
	for (int i = 0; i < k; i++) {
		fscanf(fout, "%d", &topK[i]);
	}

	for (int j = (k - 2) / 2; j >= 0; j--) {
		AdjustDown(topK, j, k);
	}

	int n = 0;
	int ret = fscanf(fout, "%d", &n);
	while (ret != EOF) {
		if (n > topK[0]) {
			topK[0] = n;
			AdjustDown(topK, 0, k);
		}
		ret = fscanf(fout, "%d", &n);
	}

	for (int i = 0; i < k; i++) {
		printf("%d ", topK[i]);
	}

}
void TestTopk() {
	/*int n = 100000;
	const char* file = "data.txt";
	FILE* fin = fopen(file, "w");
	if (fin == NULL) {
		perror("fopen error");
		return;
	}

	for (int i = 0; i < n; i++) {
		int x = rand() % n;
		fprintf(fin, "%d\n", x);
	}
	fclose(fin);*/

	PrintTopK("data.txt", 10);
}
