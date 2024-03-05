#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <queue>
#include <stdbool.h>
#include <stack>

using namespace std;

#define RADIX 10
#define K 3

void PrintArr(int* a, int n);

// 插入排序
void InsertSort(int* a, int n);

// 希尔排序
void ShellSort(int* a, int n);

// 选择排序
void SelectSort(int* a, int n);

// 堆排序
void AdjustDn(int* a, int n, int root);
void HeapSort(int* a, int n);

// 冒泡排序
void BubbleSort(int* a, int n);

// 快速排序递归实现
// 快速排序hoare版本
void PartSort1(int* a, int left, int right);
// 快速排序挖坑法
void PartSort2(int* a, int left, int right);
// 快速排序前后指针法
void PartSort3(int* a, int left, int right);
void QuickSort(int* a, int left, int right);

// 快速排序 非递归实现
void QuickSortNonR(int* a, int left, int right);

void MergeSort(int* a, int n);
void MergeSortNonR(int* a, int n);

void CountSort(int* a, int n);   //计数排序

void RadixSort(int* a, int n);  //基数排序