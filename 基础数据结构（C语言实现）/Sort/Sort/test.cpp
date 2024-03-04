#define _CRT_SECURE_NO_WARNINGS 1

#include "sort.h"

void TestSort() {
	//int a[20] = { 1,22,8,-4,10,9,4,61,81,33,-1,6,80,31,45,-5,3,-9,77,37 };
	//int a[10] = { 100, 22, 89, 32, 1, 543, 23, 543, 23, 65 };    //»ùÊýÅÅÐò
	//int n = sizeof(a) / sizeof(a[0]);

	//InsertSort(a, n);
	//ShellSort(a, n);
	//SelectSort(a, n);
	//HeapSort(a, n);
	//BubbleSort(a, n);
	//QuickSort(a, 0, n - 1);
	//QuickSortNonR(a, 0, n - 1);
	//MergeSort(a, n);
	//MergeSortNonR(a, n);
	//CountSort(a, n);
	int a[10] = { 10,9,8,7,6,5,4,3,2,1 };
	InsertSort(a, 10);
	PrintArr(a, 10);

}

int main() {
	TestSort();
	return 0;
}