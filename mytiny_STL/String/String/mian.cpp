#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>;
#include<string>
#include<vector>
using namespace std;

#include "string.h"


namespace test {
	class string {
	public:
		//���캯��
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_size + 1];
			memcpy(_str, str, _size + 1);
		}
		//��������
		string(const string& s) {   //����ΪʲôҪ�� const �� ����
			_str = new char[s._capacity + 1];
			memcpy(_str, s._str, s._size + 1);
			_size = s._size;
			_capacity = s._capacity;
		}
		//��������
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

	test::string s1("for_test");  //���ù��캯��
	test::string s2(s1);   //���ÿ�������



	////���󣺶�Ӧ���캯��Ϊexplicit���εĵ��ι��캯������ֹ����ת��
	//vector<int> arr1 = 10;

	//��ȷ��ֱ�ӳ�ʼ��
	vector<int> arr2(10);

	vector<int> arr3 = { 1, 2, 3 };
	bit::string ss = "abc";
	bit::string sss = "aaaa";
	ss = sss;


	return 0;
}