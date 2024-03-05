#define _CRT_SECURE_NO_WARNINGS 1
#include<list>
#include <vector>
#include <iostream>
using namespace std;

#include "stack.h"
#include "queue.h"
#include "priority_queue.h"

int main() {
	/*mystack::stack<int> st;
	
	st.push(1);
	st.push(1);
	st.push(1);
	st.push(1);
	while (!st.empty()) {
		cout << st.top() << endl;
		st.pop();
	}*/
	//vector<int> v = { 1, 2,65, 767,3, 8, 2 };
	//my_priority_queue::priority_queue<int> pq = { v.begin(), v.end() };
	//while (!pq.empty()) {
	//	cout << pq.top() << ' ';
	//	pq.pop();
	//}

	my_priority_queue::priority_queue<int> pq2;
	pq2.push(1);
	pq2.push(6);
	pq2.push(2);
	//pq2.pop();
	pq2.push(9);
	while (!pq2.empty()) {
		cout << pq2.top() << ' ';
		pq2.pop();
	}
	return 0;
}