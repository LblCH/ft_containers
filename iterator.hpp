#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iostream>
#include <iterator>
#include "map.hpp"

namespace ft
{
	template<typename T>
	class It{
	private:
		T* _ptr;
	public:
		It() {}
		It(T* ptr): _ptr(ptr) {}
		It(const It& copy) : _ptr(copy._ptr) {}
		~It() {}

		T& operator*() const {return *_ptr;}
		T* operator->() const {return _ptr;}

		virtual T& operator[](size_t i) const {return _ptr[i];}
		bool operator==(const It<T> &rhs) const {return _ptr == rhs._ptr;}
		bool operator!=(const It<T> &rhs) const {return _ptr != rhs._ptr;}
		bool operator<(const It<T> &rhs) const {return _ptr < rhs._ptr;}
		bool operator<=(const It<T> &rhs) const {return _ptr <= rhs._ptr;}
		bool operator>(const It<T> &rhs) const {return _ptr > rhs._ptr;}
		bool operator>=(const It<T> &rhs) const {return _ptr >= rhs._ptr;}
		It &operator=(const T &rhs) const {_ptr = rhs; return *this;}
		virtual It operator+(int n) {_ptr +=n; return *this;}
		virtual It operator-(int n) {_ptr -=n; return *this;}
		virtual It &operator+=(std::ptrdiff_t n) {_ptr +=n; return *this;}
		virtual It &operator-=(std::ptrdiff_t n) {_ptr -=n; return *this;}
		virtual It &operator++() {_ptr++; return *this;}
		virtual It &operator--() {_ptr--; return *this;}
		virtual It operator++(int) {It tmp(*this); ++_ptr; return tmp;}
		virtual It operator--(int) {It tmp(*this); --_ptr; return tmp;}
	};

	template<typename T>
	class Rev_It : public ft::It<T>
	{
	private:
		T* _ptr;
	public:
		Rev_It() {}
		Rev_It(T* ptr): _ptr(ptr) {}
		Rev_It(const Rev_It& copy) : _ptr(copy._ptr) {}
		~Rev_It() {}

		T& operator[](size_t i) const {return _ptr[-i];}
		Rev_It operator+(int n) {_ptr -=n; return *this;}
		Rev_It operator-(int n) {_ptr +=n; return *this;}
		Rev_It &operator+=(std::ptrdiff_t n) {_ptr -=n; return *this;}
		Rev_It &operator-=(std::ptrdiff_t n) {_ptr +=n; return *this;}
		Rev_It &operator++() {_ptr--; return *this;}
		Rev_It &operator--() {_ptr++; return *this;}
		Rev_It operator++(int) {Rev_It tmp(*this); --_ptr; return tmp;}
		Rev_It operator--(int) {Rev_It tmp(*this); ++_ptr; return tmp;}
	};

    template<typename Key, typename T>
    class it_map
    {
    private:
        typedef node_map<Key, T>*	node;
    public:
        node	_ptr;
        it_map() : _ptr(0) {};
        it_map(node n) : _ptr(n) {};
        ~it_map() {};
        std::pair<const Key, T> & operator*() const {return *_ptr->pair;}
        std::pair<const Key, T> * operator->() const {return *_ptr->pair;}
        bool operator==(const it_map<Key, T> &rhs) const {return this->_ptr == rhs._ptr;}
        bool operator!=(const it_map<Key, T> &rhs) const {return this->_ptr != rhs._ptr;}
        it_map& operator++() {
            if (_ptr->right) {
                _ptr = _ptr->right;
                while (_ptr->left)
                    _ptr = _ptr->left;
            }
            else {
                while (_ptr->parent && _ptr->parent->pair->first < _ptr->pair->first)
                    _ptr = _ptr->parent;
                _ptr = _ptr->parent;
            }
            return *this;
        }
        it_map operator++(int) {
            it_map<Key, T> tmp(*this);
            operator++();
            return tmp;
        }
        it_map& operator--() {
            if (_ptr->left) {
                _ptr = _ptr->left;
                while (_ptr->right)
                    _ptr = _ptr->right;
            }
            else {
                while (_ptr->parent && _ptr->parent->pair->first > _ptr->pair->first)
                    _ptr = _ptr->parent;
                _ptr = _ptr->parent;
            }
            return *this;
        }
        it_map operator--(int) {
            it_map<Key, T> tmp(*this);
            operator--();
            return tmp;
        }
        it_map& operator=(const node_map<Key, T>& rhs) {_ptr = rhs; return *this;}
    };

    template<typename Key, typename T>
    class reverse_it_map
    {
    private:
        typedef node_map<Key, T>*	node;
    public:
        node	_ptr;
        reverse_it_map() : _ptr(0) {};
        reverse_it_map(node n) : _ptr(n) {};
        ~reverse_it_map() {};
        std::pair<const Key, T>& operator*() const {return *_ptr->pair;}
        std::pair<const Key, T>* operator->() const {return *_ptr->pair;}
        bool operator==(const reverse_it_map<Key, T> &obj) const {return this->_ptr == obj._ptr;}
        bool operator!=(const reverse_it_map<Key, T> &obj) const {return this->_ptr != obj._ptr;}
        reverse_it_map& operator--() {
            if (_ptr->right) {
                _ptr = _ptr->right;
                while (_ptr->left)
                    _ptr = _ptr->left;
            }
            else {
                while (_ptr->parent && _ptr->parent->pair->first < _ptr->pair->first)
                    _ptr = _ptr->parent;
                _ptr = _ptr->parent;
            }
            return *this;
        }
        reverse_it_map operator--(int) {
            reverse_it_map<Key, T> tmp(*this);
            operator--();
            return tmp;
        }
        reverse_it_map& operator++() {
            if (_ptr->left) {
                _ptr = _ptr->left;
                while (_ptr->right)
                    _ptr = _ptr->right;
            }
            else {
                while (_ptr->parent && _ptr->parent->pair->first > _ptr->pair->first)
                    _ptr = _ptr->parent;
                _ptr = _ptr->parent;
            }
            return *this;
        }
        reverse_it_map operator++(int) {
            reverse_it_map<Key, T> tmp(*this);
            operator++();
            return tmp;}
        reverse_it_map& operator=(const node_map<Key, T>& element) {_ptr = element; return *this;}
    };
}

template <typename T>
void	swap(T &x, T &y)
{
	T tmp = x;
	x = y;
	y = tmp;
};
#endif