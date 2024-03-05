#define _CRT_SECURE_NO_WARNINGS 1
#include "sort.h"

void PrintArr(int* a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
}

void InsertSort(int* a, int n) {
	for (int i = 1; i < n; i++) {
		int end = i - 1;
		int tmp = a[i];
		while (end >= 0) {
			if (tmp < a[end]) {
				a[end + 1] = a[end];
				end--;
			} 
			else break;
		}
		a[end + 1] = tmp;
	}
}
void insertSort(int* nums, int n) {
	int i, j;
	for (i = 1; i < n; i++) {
		int tmp = nums[i];
		for (j = i - 1; j >= 0 && nums[j] > tmp; j--) {
			nums[j + 1] = nums[j];
		}
		nums[j + 1] = tmp;
	}
}

void ShellSort(int* a, int n) {
	int gap = n;
	while (gap > 1) {
		gap /= 2;   //或者 gap /= 3 + 1
		for (int i = 0; i < n - gap; i++) {
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0) {
				if (a[end] > tmp) {
					a[end + gap] = a[end];
					end -= gap;
				} 
				else break;
			}
			a[end + gap] = tmp;
		}
	}
	
}
void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void SelectSort(int* a, int n) {
	int left = 0, right = n - 1;
	while (left < right) {
		int mini = left, maxi = left;
		for (int i = left + 1; i <= right; i++) {
			if (a[mini] > a[i]) mini = i;
			if (a[maxi] < a[i]) maxi = i;
		}
		Swap(&a[maxi], &a[right]);
		//如果right与mini重叠，需要修正
		if (right == mini) {
			mini = maxi;
		}
		Swap(&a[mini], &a[left]);
		left++;
		right--;
	}
}

void AdjustDown(int* a, int n, int root) {
	int child = root * 2 + 1;
	while (child < n) {
		if (child + 1 < n && a[child] < a[child + 1]) {
			child += 1;
		}
		if (a[child] > a[root]) {
			Swap(&a[child], &a[root]);
			root = child;
			child = root * 2 + 1;
		} else {
			break;
		}
	}

}
void HeapSort(int* a, int n) {
	for (int i = (n-1-1) / 2; i >= 0; i--) {
		AdjustDown(a, n, i);
	}

	for (int i = n - 1; i > 0; i--) {
		Swap(&a[i], &a[0]);   //交换第一个与最后一个位置
		AdjustDown(a, i, 0);    //剩余 i 个数进行向下调整
	}
}

void BubbleSort(int* a, int n) {
	for (int i = 0; i < n - 1; i++) {
		bool flag = false;   
		for (int j = 0; j < n - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				Swap(&a[j], &a[j + 1]);
				flag = true;
			}
		}
		if (!flag) break;   //如果一趟没有交换，说明已经有序
	}
}

// 快速排序hoare版本
void PartSort1(int* a, int left, int right) {
	if (left >= right) return; 

	int begin = left;
	int end = right;
	int keyi = begin;
	while (begin < end) {
		while (begin < end && a[end] >= a[keyi]) end--;
		while (begin < end && a[begin] <= a[keyi]) begin++;

		Swap(&a[begin], &a[end]);
	}
	Swap(&a[keyi], &a[begin]);
	PartSort1(a, left, begin - 1);
	PartSort1(a, begin + 1, right);
}

 //快速排序挖坑法
void PartSort2(int* a, int left, int right) {
	if (left >= right) return;
	int tmp = a[left];
	int hole = left;
	int begin = left, end = right;
	while (begin < end) {
		while (begin < end && a[end] > tmp) end--;
		a[hole] = a[end];
		hole = end;

		while (begin < end && a[begin] < tmp) begin++;
		a[hole] = a[begin];
		hole = begin;
	}
	a[hole] = tmp;

	PartSort2(a, left, hole - 1);
	PartSort2(a, hole + 1, right);
}

// 快速排序前后指针法
void PartSort3(int* a, int left, int right) {
	if (left >= right) return;
	int cur = left + 1, pre = left;
	int keyi = left;
	while (cur <= right) {
		if (a[cur] <= a[keyi] && ++pre != cur) {
			Swap(&a[cur], &a[pre]);
		}  
		cur++;
	}
	Swap(&a[keyi], &a[pre]);
	PartSort3(a, left, pre - 1);
	PartSort3(a, pre + 1, right);
}

void QuickSort(int* a, int left, int right) {
	//PartSort1(a, left, right);
	//PartSort2(a, left, right);
	PartSort3(a, left, right);


}

// 快速排序 非递归实现
void QuickSortNonR(int* a, int left, int right) {
	stack<int> st;
	st.push(right);
	st.push(left);

	while (!st.empty()) {
		int begin = st.top();
		st.pop();
		int end = st.top();
		st.pop();
		left = begin, right = end;   //保存区间的头尾的位置
		int keyi = begin;   

		while (begin < end) {
			while (begin < end && a[end] >= a[keyi]) end--;
			while (begin < end && a[begin] <= a[keyi]) begin++;
			 
			Swap(&a[begin], &a[end]);   
		}
		                                        
		Swap(&a[keyi], &a[begin]);   //“处理根节点”

		if (right - (begin + 1) > 0) {    //“递归左区间”
			st.push(right);
			st.push(begin + 1);
		}
		if ((begin - 1) - left > 0) {     //“递归右区间”
			st.push(begin - 1);
			st.push(left);
		}
	}
}

void _MergeSort(int* a, int left, int right, int* tmp) {
	if (left >= right) return;

	int mid = (right + left) / 2;
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);

	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int i = left;
	while (begin1 <= end1 && begin2 <= end2) {
		if (a[begin1] < a[begin2]) {
			tmp[i++] = a[begin1++];
		} else {
			tmp[i++] = a[begin2++];
		}
	}
	while (begin1 <= end1) {
		tmp[i++] = a[begin1++];
	}
	while (begin2 <= end2) {
		tmp[i++] = a[begin2++];
	}

	memcpy(a + left, tmp + left, sizeof(int) * (right - left + 1));
}

void MergeSort(int* a, int n) {
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL) {
		perror("malloc fail");
		return;
	}
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
}

//重点！！！
void MergeSortNonR(int* a, int n) {
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL) {
		perror("malloc fail");
		return;
	}
	int gap = 1;
	while (gap < n) {
		for (int i = 0; i < n; i += 2 * gap) {
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;

			//修正边界
			if (end1 >= n || begin2 >= n) {
				break;
			} else if (end2 >= n) {
				end2 = n - 1;
			}

			int j = begin1;
			while (begin1 <= end1 && begin2 <= end2) {
				if (a[begin1] > a[begin2]) {
					tmp[j++] = a[begin2++];
				} else {
					tmp[j++] = a[begin1++];
				}
			}
			while (begin1 <= end1) {
				tmp[j++] = a[begin1++];
			}
			while (begin2 <= end2) {
				tmp[j++] = a[begin2++];
			}
			memcpy(a+i, tmp+i, sizeof(int) * (end2 - i + 1));
		}
		gap *= 2;
	}
}

void CountSort(int* a, int n) {
	int mn = INT_MAX, mx = INT_MIN;
	for (int i = 0; i < n; i++) {
		mn = min(mn, a[i]);
		mx = max(mx, a[i]);
	}
	int* count = (int*)calloc((mx - mn + 1), sizeof(int));

	for (int i = 0; i < n; i++) {
		count[a[i] - mn]++;
	}

	int j = 0;
	for (int i = 0; i <= (mx - mn); i++) {
		while (count[i]--) {
			a[j++] = i + mn;
		}
	}
	free(count);
}


queue<int> que[RADIX];
int GetKNum(int value, int k) {
	int ret = 0;
	while (k >= 0) {
		ret = value % 10;
		value /= 10;
		k--;
	}
	return ret;
}
void Distribute(int* a, int n, int k) {
	for (int i = 0; i < n; i++) {
		int index = GetKNum(a[i], k);
		que[index].push(a[i]);
	}
}
void Collect(int* a) {
	int j = 0;
	for (int i = 0; i < RADIX; i++) {
		while (!que[i].empty()) {
			a[j++] = que[i].front();
			que[i].pop();
		}
	}
}
void RadixSort(int* a,int n) {
	for (int i = 0; i < K; i++) {
		Distribute(a, n, i);
		Collect(a);
	}
}