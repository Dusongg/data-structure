#pragma once
#include <assert.h>
#include <string.h>

namespace myString {
    class string {
    public:
        typedef char* iterator;
        typedef const char* const_iterator;

    public:
        string(const char* str = "")
        {  
        {  
            _size = strlen(str);
            _capacity = _size;
            _str = new char[_size + 1];
            memcpy(_str, str, _size + 1);
        }
        //创建一个新对象(拷贝构造)
        string(const string& s) :_str(nullptr) {
            string tmp(s._str);
            std::swap(tmp._str, _str);
            std::swap(tmp._size, _size);
            std::swap(tmp._capacity, _capacity);
           /* _str = new char[s._capacity + 1];
            memcpy(_str, s._str, s._size + 1);
            _size = s._size;
            _capacity = s._capacity;*/
        }
        //两个已经存在的对象赋值（深拷贝）
        string& operator=(string tmp) {   //调用拷贝构造 string tmp = s;
            std::swap(tmp._str, _str);
            std::swap(tmp._size, _size);
            std::swap(tmp._capacity, _capacity);
            return *this;
        }
        /*string& operator=(const string& s) {
            if (this == &s) return *this;

            char* tmp = new char[s._capacity + 1];
            memcpy(tmp, s._str, s._capacity + 1);
            delete[] _str;
            _size = s._size;
            _capacity = s._capacity;
            _str = tmp;
            return *this;
        }*/
        ~string() {
            delete[] _str;
            _str = nullptr;
            _size = _capacity = 0;
        }


        iterator begin() {
            return _str;
        }
        const_iterator begin() const {
            return _str;
        }
        iterator end() {
            return _str + _size;
        }
        const_iterator end() const {
            return _str + _size;
        }


        void push_back(char c) {
            if (_size == _capacity) {
                reserve(_capacity == 0 ? 4 : _capacity * 2);
            }
            _str[_size++] = c;
            _str[_size] = '\0';
        }

        string& operator+=(char c) {
            push_back(c);
            return *this;     
        }
        void append(const char* str) {
            int sz = strlen(str);
            if (_size + sz > _capacity) {
                reserve(_size + sz);
            }
            memcpy(_str + _size, str, sz + 1);
            _size += sz;
        }
        string& operator+=(const char* str) {
            append(str);
            return *this;
        }
        void clear() {
            _size = 0;
            _str[_size] = '\0';
        }
        void swap(string& s) {
            std::swap(_str, s._str);
            std::swap(_size, s._size);
            std::swap(_capacity, s._capacity);
        }

        const char* c_str() const {
            return _str;
        }

        size_t size()const {
            return _size;
        }
        size_t capacity()const {
            return _capacity;
        }
        bool empty()const {
            return _size == 0;
        }
        void resize(size_t n, char c = '\0') {
            if (n > _size) {
                reserve(n);
                for (size_t i = _size; i < n; i++) {
                    _str[i] = c;
                }
            }
            _str[n] = '\0';
            _size = n;
        }

        void reserve(size_t n) {
            if (n <= _capacity) return;

            char* tmp = new char[n + 1];
            memcpy(tmp, _str, _size + 1);
            delete[] _str;
            _str = tmp;
            _capacity = n;
        }


        char& operator[](size_t index) {
            assert(index < _size);
            return _str[index];
        }
        const char& operator[](size_t index)const {
            assert(index < _size);
            return _str[index];
        }


        bool operator<(const string& s) {
            size_t i = 0, j = 0;
            while (i < _size && j < s.size()) {
                if (_str[i] < s[j]) return true;
                else if (_str[i] > s[j]) return false;
                i++;
                j++;
            }
            if (i < _size) return false;
            if (j < s._size) return true;
            return false;
        }
        bool operator<=(const string& s) {
            return *this < s && *this == s;
        }
        bool operator>(const string& s) {
            int ret = memcmp(_str, s._str, _size < s._size ? _size : s._size);
            return ret == 0 ? _size > s._size : (ret > 0);
        }
        bool operator>=(const string& s) {
            return *this > s && *this == s;
        }
        bool operator==(const string& s) {
            return _size == s.size() &&  memcmp(_str, s.c_str(), _size) == 0;
        }
        bool operator!=(const string& s) {
            return !(*this == s);
        }
        // 返回c在string中第一次出现的位置
        size_t find(char c, size_t pos = 0) const {
            for (int i = 0; i < _size; i++) {
                if (_str[i] = c) return i;
            }
            return npos;
        }
        // 返回子串s在string中第一次出现的位置
        size_t find(const char* s, size_t pos = 0) const {
            const char* ret = strstr(_str, s);
            return ret == nullptr ? npos : ret - _str;
        }
        // 在pos位置上插入字符c/字符串str，并返回该字符的位置
        string& insert(size_t pos, size_t n,  char c) {
            assert(pos <= _size);
            if (_size + n > _capacity) reserve(_size + n);
            
            int end = _size;
            while (end >= pos && end != npos) {
                _str[end + n] = _str[end];
                end--;
            }
            for (int i = pos; i < pos + n; i++) {
                _str[i] = c;
            }
            _size += n;
            return *this;
        }
        string& insert(size_t pos, const char* str) {
            assert(pos <= _size);
            int n = strlen(str);
            if (_size + n > _capacity) reserve(_size + n);

            int end = _size;
            while (end >= pos && end != npos) {
                _str[end + n] = _str[end];
                end--;
            }
            for (int i = pos; i < pos + n; i++) {
                _str[i] = str[i-pos];
            }
            _size += n;
            return *this;
        }
        // 删除pos位置上的元素，并返回该元素的下一个位置
        string& erase(size_t pos, size_t len = npos) {
            assert(pos < _size);
            if (pos + len >= _size || pos == npos) {
                _str[pos] = '\0';
                _size = pos;
            }
            int i = pos + len;
            while (i < _size) {
                _str[i - len] = _str[i];
                i++;
            }
            _size -= len;
            _str[_size] = '\0';
            return *this;
        }
        string substr(size_t pos, size_t len = npos) {
            assert(pos < _size);

            if (len == npos || pos + len > _size) len = _size - pos;

            string tmp;
            tmp.reserve(len);
            for (size_t i = pos; i < len + pos; i++) {
                tmp += _str[i];
            }
            return tmp;
        }
    private:
        size_t _capacity;
        size_t _size;
        char* _str;
        static const size_t npos;
    };
    const size_t string::npos = -1;
    ostream& operator<<(ostream& _cout, const string& s) {
        for (auto c : s) {
            _cout << c;
        }
        return _cout;
    }
    istream& operator>>(istream& _cin, string& s) {
        s.clear();
        char c = _cin.get();
        while (c == ' ' || c == '\0') 
            c = cin.get();
        char buff[128];
        int i = 0;
        while (c != ' ' && c != '\0') {
            buff[i++] = c;
            if (i == 127) {
                buff[i] = '\0';
                s += buff;
                i = 0;
            }
            c = _cin.get();
        }
        buff[i] = '\0';
        s += buff;
        return _cin;
    }
};


