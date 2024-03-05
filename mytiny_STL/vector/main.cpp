#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include "string_for_test_with_move.h"
using namespace std;

#include "vector.h"

int main() {

	//报错，会走迭代器构造（有多个选择会选更适合的），因为第一个参数是无符号，test::vector<int> arr(4u, 4)无报错
	//test::vector<int> arr(4, 4);

	//arr.insert(arr.begin(), 100);
	//test::vector<int>::iterator pos = arr.begin() + 3;
	//arr.insert(pos, 300);

	//vs强制检查， erase后迭代器失效， linux下不会, erase返回删除的下一个位置
	/*auto pos = arr.begin() + 2;
	pos = arr.erase(pos);
	cout << *pos << endl;*/

	//arr.resize(10, 10);

	/*test::vector<int> arr2 = arr;

	////arr2.resize(10, 10);
	////arr = arr2;
	////test::vector<int> arr3 = {arr2.begin(), arr2.end()};
	////for (size_t i = 0; i < arr3.size(); i++) cout << arr3[i] << ' ';*/
	////test::vector<int> arr = { 1, 2, 3 };
	////test::vector<int> v = move(arr);
	////for (auto x : v) {
	////	cout << x << ' ';
	////}
	////cout << endl;
	////test::vector<int> v2 = arr;
	////for (auto x : v2) {
	////	cout << x << ' ';
	////}
	////cout << endl;

	myVctor::vector<myString::string> v;
	myString::string s = "dfag";
	v.emplace_back(s);
	puts("-------------");
	v.push_back("sdgag");
	return 0;

}