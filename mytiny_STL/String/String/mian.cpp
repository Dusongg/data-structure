#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>;
#include<string>
#include<vector>
using namespace std;

#include "string.h"


namespace test {
	class string {
	public:
		//构造函数
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_size + 1];
			memcpy(_str, str, _size + 1);
		}
		//拷贝构造
		string(const string& s) {   //考虑为什么要加 const 与 引用
			_str = new char[s._capacity + 1];
			memcpy(_str, s._str, s._size + 1);
			_size = s._size;
			_capacity = s._capacity;
		}
		//析构函数
		~string() {
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
	private:
		size_t _capacity;
		size_t _size;
		char* _str;
	};
}
int main() {

	test::string s1("for_test");  //调用构造函数
	test::string s2(s1);   //调用拷贝构造



	////错误：对应构造函数为explicit修饰的单参构造函数，禁止类型转换
	//vector<int> arr1 = 10;

	//正确：直接初始化
	vector<int> arr2(10);

	vector<int> arr3 = { 1, 2, 3 };
	bit::string ss = "abc";
	bit::string sss = "aaaa";
	ss = sss;


	return 0;
}