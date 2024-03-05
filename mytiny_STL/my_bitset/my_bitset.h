#pragma once
#include <vector>
using namespace std;
template<size_t N>
class bitset {
public:
	bitset() { s.resize(N / 32 + N % 32); }

	void set(size_t index) { s[index / 32] |= 1 << (index % 32); }
	void reset(size_t index) { s[index / 32] &= ~(1 << (index % 32)); }
	bool test(size_t index) { return s[index / 32] & (1 << (index % 32)); }

private:
	vector<int> s;
};