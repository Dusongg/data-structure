#pragma once
namespace mystack {
	template<class T, class Container = std::list<T>>
	class queue {
	public:
		void push(const T& x) {
			ct.push_back(x);
		}
		void pop() {
			ct.pop_front();
		}
		T& front() {
			return ct.front();
		}
		T& back() {
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