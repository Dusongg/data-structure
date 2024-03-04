#pragma once
template<class iterator, class Ref, class Ptr>
class reverse_iterator {
	typedef reverse_iterator<iterator, Ref, Ptr> Self;

	reverse_iterator(iterator it) :_it(it) {}
	Ref operator*() {
		iterator tmp = _it;
		return *(--tmp);
	}

	Ptr operator->() {
		return &(operator*());
	}

	Self& operator++() {
		_it--;
		return *this;
	}
	Self& operator--() {
		_it++;
		return *this;
	}

private:
	iterator _it;
};