#pragma once
#include "reverse_iterator.h"
namespace my_priority_queue {
	template<class T>
	class Less {
	public:
		bool operator()(const T& x, const T& y) {
			return x < y;
		}
	};
	template<class T>
	class Greater {
	public:
		bool operator()(const T& x, const T& y) {
			return x > y;
		}
	};
	template<class T, class Container = vector<T>, class Compare = Less<T>>
	class priority_queue {
	private:
		void AdjustDown(int parent) {
			size_t n = ct.size(), child = parent * 2 + 1;
			while (child < n) {
				if (child + 1 < n && com(ct[child], ct[child + 1])) {
					child++;
				}
				if (com(ct[parent], ct[child])) {
					swap(ct[child], ct[parent]);
					parent = child;
					child = parent * 2 + 1;
				} else {
					break;
				}
			}
		}
		void AdjustUp(int child) {
			int parent = (child - 1) / 2;
			while (child > 0) {  //�״��
	 			if (com(ct[parent], ct[child])) {
					swap(ct[child], ct[parent]);
					child = parent;
					parent = (child - 1) / 2;
				} else {
					break;
				}
			}
		}
	public:
		template<class InputIterater> 
		priority_queue(InputIterater begin, InputIterater end) {
			for (auto it = begin; it != end; it++) {
				ct.push_back(*it);
			}
			for (int i = (ct.size() - 2) / 2; i >= 0; i--) {
				AdjustDown(i);
			}
		}
		//�������û����ʾ���幹�캯������C++���������Զ�����һ���޲ε�Ĭ�Ϲ��캯����
		//һ����ʽ���壬���������������ɡ�
		priority_queue() {};

		const T& top() {
			return ct[0];
		}
		void pop() {
			swap(ct[0], ct[ct.size() - 1]);
			ct.pop_back();
			AdjustDown(0);
		} 
		void push(const T& x) {
			ct.push_back(x);
			AdjustUp(ct.size() - 1);
		}
		bool empty() {
			return ct.empty();
		}
		size_t size() {
			return ct.size();
		}
	private:
		Compare com;
		Container ct;
	};
}