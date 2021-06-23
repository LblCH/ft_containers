#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iostream>
#include <iterator>

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
}

#endif