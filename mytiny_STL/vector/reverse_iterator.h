#pragma once
template<class iterator, class Ref, class Ptr>
struct Reverse_iterator {
	typedef Reverse_iterator<iterator, Ref, Ptr> Self;

	Reverse_iterator(iterator it) :_it(it) {}
	Ref operator*() {
		iterator tmp = _it;
		return *(--tmp);
	}

	Ptr operator->() {
		return &(operator*());
	}

	Self& operator++() {
		--_it;
		return *this;
	}
	Self& operator--() {
		++_it;
		return *this;
	}
	bool operator!=(const Self& it) {
		return _it != it._it;
	}

private:
	iterator _it;
};