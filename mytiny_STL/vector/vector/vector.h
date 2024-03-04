#pragma once
#include <assert.h>
#include "reverse_iterator.h"
#include <initializer_list>


#define newcapacity capacity() == 0 ? 4 : capacity() * 2
namespace myVctor {
	template<class T> 
	class vector{
	public:
		typedef T* iterator;
		typedef const T* const_iterator; 
		typedef Reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef Reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
		vector() :_start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}

		//test::vector<int> arr(4, 4)报错，会走迭代器构造（有多个选择会选更适合的），因为第一个参数是无符号
		//test::vector<int> arr(4u, 4)无报错
		vector(size_t n, const T& value = T()) {
			resize(n, value);
		}
		//防止上述报错
		vector(int n, const T& value = T()) {
			resize(n, value);
		}

		vector(const initializer_list<T>& il) {
			reserve(il.size());
			for (auto it = il.begin(); it != il.end(); ++it) {
				*_finish++ = *it;
			}
		}

		//用迭代器区间构造
		template<class InputIterator>
		vector(InputIterator first, InputIterator last) {
			for (auto it = first; it != last; it++) {
				push_back(*it);
			}
		}
		//拷贝构造
		vector(const vector<T>& v) {
			puts("const vector<T>& v");

			_start = new T[v.capacity()];
			//自定义类型深拷贝
			//memcpy(_start, v._start, sizeof(T) * v.size());
			for (int i = 0; i < v.size(); i++) {
				_start[i] = v._start[i];
			}
			_finish = _start + v.size();
			_end_of_storage = _start + v.capacity();
		}
		vector(vector<T>&& v) {
			puts("vector(vector<T>&& v)");

			_start = new T[v.capacity()];
			//自定义类型深拷贝
			//memcpy(_start, v._start, sizeof(T) * v.size());
			for (int i = 0; i < v.size(); i++) {
				_start[i] = move(v._start[i]);
			}
			_finish = _start + v.size();
			_end_of_storage = _start + v.capacity();
		}
		//赋值运算符重载
		//vector<T>& operator= (const vector<T>& v) {
		//	if (v.capacity() > capacity()) reserve(v.capacity());

		//	memcpy(_start, v._start, sizeof(T) * v.size());
		//	_finish = _start + v.size();
		//	_end_of_storage = _start + v.capacity();

		//	return *this;
		//}

		vector<T>& operator= (vector<T> v) {   //调用拷贝构造 -> swap
			swap(v);
			return *this;
		}
		~vector() {
			if (_start) {
				delete[] _start; 
				_start = _finish = _end_of_storage = nullptr;
			}
		}
		
		iterator begin() {
			return _start;
		}
		const_iterator begin() const{
			return _start;
		}
		iterator end() {
			return _finish;
		}
		const_iterator end() const {
			return _finish;
		}
		reverse_iterator rbegin() {
			return end();
		}
		reverse_iterator rend() {
			return begin();
		}
		const_reverse_iterator rbegin() const{
			return end();
		}
		const_reverse_iterator rend() const {
			return begin();
		}
		void reserve(size_t n) {
			if (n <= capacity()) return;

			size_t sz = size();
			T* tmp = new T[n];
			if (_start) {

				//!!!自定义类型浅拷贝，报错 ，
				//! 如果是vector<string> , delete会想string先释放掉（tmp自身是深拷贝，但string是浅拷贝）
				/*memcpy(tmp, _start, sizeof(T) * sz);*/
				for (int i = 0; i < sz; i++) {
					tmp[i] = _start[i];    //调用深拷贝
				}
				delete[] _start;
			}
			_start = tmp;
			_finish = _start + sz;
			_end_of_storage = _start + n;
		}
		
		//value缺省值调用其默认构造函数
		void resize(size_t n, const T& value = T()) {
			if (n < size()) {
				_finish = _start + n;
			} else if (n > size()) {
				reserve(n);
				for (auto it = _finish; it < _start + n; it++) {
					*it = value;
				}
				_finish = _start + n;
			}
		}
		template<class ...Args>
		void emplace_back(Args &&...args) { emplace(end(), forward<Args>(args)...); }
		void push_back(const T& x) { insert(end(), x); }
		void pop_back() { erase(end() - 1); }
		iterator insert(iterator pos, const T& x) {
			assert(pos <= _finish && pos >= _start);
			if (_finish == _end_of_storage) {
				size_t index = pos - _start;    //扩容后pos变为空指针（迭代器失效）
				reserve(newcapacity);
				pos = _start + index;
			}
			iterator it = _finish - 1;
			while (it >= pos) {
				*(it + 1) = *it;
				it--;
			}
			*pos = x;
			_finish++;
			return pos;
		}
		template<class... Args>
		iterator emplace(iterator pos, Args &&...args) {
			assert(pos <= _finish && pos >= _start);
			if (_finish == _end_of_storage) {
				size_t index = pos - _start;    //扩容后pos变为空指针（迭代器失效）
				reserve(newcapacity);
				pos = _start + index;
			}
			iterator it = _finish - 1;
			while (it >= pos) {
				*(it + 1) = *it;
				it--;
			}
			*pos = T(args...);
			_finish++;
			return pos;
		}
		void swap(vector<T>& v) {
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}
		iterator erase(iterator pos) {   //注意迭代器失效问题
			assert(pos >= _start && pos < _finish);

			iterator it = pos + 1;
			while (it != _finish) {
				*(it - 1) = *it;
				it++;
			}
			_finish--;
			return pos;
		}

		size_t capacity() const {
			return _end_of_storage - _start;
		}
		size_t size() const {
			return _finish - _start;
		}
		T& operator[](const size_t pos) {
			assert(pos < size());
			return *(_start + pos);
		}
		const T& operator[](const size_t pos) const {
			assert(pos < size());
			return *(_start + pos);
		}

	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _end_of_storage = nullptr;
	};
}