#define _CRT_SECURE_NO_WARNINGS 1
#include <assert.h>
#include "reverse_iterator.h"
namespace mylist {
	template <class T>
	struct list_node {
		list_node<T>* _pre;
		list_node<T>* _next;
		T _val;
		list_node(const T& val = T()) :_pre(nullptr), _next(nullptr), _val(val) {};
	};

	template <class T, class Ref, class Ptr>
	struct __list_iterator {
		typedef list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> self;
		Node* _node;

		__list_iterator(Node* node) : _node(node) {};
		//ǰ��++
		self& operator++() {
			_node = _node->_next;
			return *this;
		}
		//����++
		self operator++(int) {
			self tmp = *this;  //ǳ����
			_node = _node->_next;
			return tmp;
		}
		self& operator--() {
			_node = _node->_pre;
			return *this;
		}
		self operator--(int) {
			self tmp = *this;  //ǳ����
			_node = _node->_pre;
			return tmp;
		}
		Ref operator*() {
			return _node->_val;
		}
		Ptr operator->() {    //ΪT* ����һ��ģ����� ����Ϊ��const T*   --> Ptr
			return &(_node->_val);
		}
		//�ر�ע�⣺it != l1.end() 
		//end()��ֵ���أ����г��ԣ������const
		bool operator!=(const self& it) {   
			return _node != it._node;
		} 
		bool operator==(const self& it) {
			return _node == it._node;
		}
	};
	template <class T>
	class list {
		typedef list_node<T> Node;  //����ʹ�ã�����Ϊ˽��
	public:
		typedef __list_iterator<T, T&, T*> iterator;    //����ʹ�ã���������Ϊ˽��
		//typedef const __list_iterator<T> const_iterator  ���������趨const�������� ������ void* const ptr;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		typedef Reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef Reverse_iterator<iterator, const T&, const T*> const_reverse_iterator;

		void empty_init() {
			dummy = new Node;
			dummy->_next = dummy;
			dummy->_pre = dummy;
			_size = 0;
		}
		list(){
			empty_init();
		}
		list(const list<T>& lt) {  
			empty_init();
			for (auto& x : lt) {
				push_back(x); 
			}
		}
		void swap(const list<T>& lt) {
			std::swap(dummy, lt.dummy);
			std::swap(_size, lt._size);
		}
		//��������͸�ֵ��������ص�д�����﷨��Ҳ���ԣ�lsit& operator=(list lt);
		list<T>& operator=(list<T> lt) {   
			swap(lt);
			return *this;
		}
		~list() {
			clear();
			delete dummy;
			dummy = nullptr;
		}
		void clear() {
			for (iterator it = begin(); it != end(); ) {
				it = erase(it);
			}
		}
		void push_back(const T& val) {
			insert(end(), val);
		}
		void push_front(const T& val) {
			insert(begin(), val);
		}
		void pop_front() {
			erase(begin());
		}
		void pop_back() {
			erase(--end());
			//erase(dummy->_pre); 
		}
		iterator insert(iterator pos, const T& x) {
			Node* newnode = new Node(x);
			Node* cur = pos._node;
			cur->_pre->_next = newnode;
			newnode->_pre = cur->_pre;
			newnode->_next = cur;
			cur->_pre = newnode;

			_size++;
			return newnode;
		}
		iterator erase(iterator pos) {
			assert(pos != dummy);

			Node* cur = pos._node;
			iterator ret = cur->_next;
			cur->_next->_pre = cur->_pre;
			cur->_pre->_next = cur->_next;
			delete cur;

			_size--;
			return ret;
		}
		iterator begin() {
			return dummy->_next;
		}
		iterator end() {
			return dummy;
		}
		const_iterator begin() const {
			return dummy->_next;
		}
		const_iterator end() const {
			return dummy;
		}
		reverse_iterator rbegin() {
			return end();
		}
		reverse_iterator rend() {
			return begin();
		}
		const_reverse_iterator rbegin() const {
			return end();
		}
		const_reverse_iterator rend() const {
			return begin();
		}
		size_t size() {
			return _size;
		}
	private:
		Node* dummy;
		size_t _size;
	};
}