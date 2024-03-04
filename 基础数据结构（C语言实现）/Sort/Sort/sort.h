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

// ��������
void InsertSort(int* a, int n);

// ϣ������
void ShellSort(int* a, int n);

// ѡ������
void SelectSort(int* a, int n);

// ������
void AdjustDn(int* a, int n, int root);
void HeapSort(int* a, int n);

// ð������
void BubbleSort(int* a, int n);

// ��������ݹ�ʵ��
// ��������hoare�汾
void PartSort1(int* a, int left, int right);
// ���������ڿӷ�
void PartSort2(int* a, int left, int right);
// ��������ǰ��ָ�뷨
void PartSort3(int* a, int left, int right);
void QuickSort(int* a, int left, int right);

// �������� �ǵݹ�ʵ��
void QuickSortNonR(int* a, int left, int right);

void MergeSort(int* a, int n);
void MergeSortNonR(int* a, int n);

void CountSort(int* a, int n);   //��������

void RadixSort(int* a, int n);  //��������