#pragma once
namespace mystack {
	template<class T, class Container = std::list<T>>
	class stack {
	public:
		void push(const T& x) {
			ct.push_back(x);
		}
		void pop() {
			ct.pop_back();
		}
		T& top() {
			return ct.back();
		}
		size_t size() {
			ct.size();
		}
		bool empty() {
			return ct.empty();
		}
	private:
		Container ct;
	};
}