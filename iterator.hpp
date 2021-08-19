#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iostream>
#include <iterator>
#include "rbt.hpp"

namespace ft
{
	struct	input_iterator_tag {};

	struct	output_iterator_tag {};

	struct	forward_iterator_tag : public input_iterator_tag, public output_iterator_tag{};

	struct	bidirectional_iterator_tag : public forward_iterator_tag {};

	struct	random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct	iterator {
		typedef T										value_type;
		typedef Distance								difference_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef Category								iterator_category;
	};

	template <class Iterator>
	struct	iterator_traits {
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct	iterator_traits<T*> {
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef random_access_iterator_tag				iterator_category;
	};

	template <class T>
	struct	iterator_traits<const T*> {
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef random_access_iterator_tag				iterator_category;
	};

	template <class T>
	struct	check_const {
		T	_n;
		typedef T type;
		check_const() {std::cout << "NOT CONST" << std::endl;}
		check_const(T n) : _n(n) {}
	};

	template <class T>
	struct	check_const<const T> {
		T	_n;
		typedef T type;
		check_const() {std::cout << "CONST" << std::endl;}
		check_const(T n) : _n(n) {}
	};

	template <class T>
	struct	check_const<T*> {
		typedef T* type;
		check_const() {std::cout << 2 << std::endl;}
	};

	template <class T>
	struct	check_const<const T*> {
		typedef T* type;
		check_const() {std::cout << 3 << std::endl;}
	};

	template <class Iterator>
	typename iterator_traits<Iterator>::iterator_category	iterator_category(Iterator iter) {
		return typename iterator_traits<Iterator>::iterator_category();
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last) {
		typename iterator_traits<Iterator>::difference_type	dist = 0;
		while (first != last) {
			first++;
			dist++;
		}
		return dist;
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, input_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, forward_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, bidirectional_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, random_access_iterator_tag) {
		return last - first;
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, std::input_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, std::forward_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, std::bidirectional_iterator_tag) {
		return ft::distance(first, last);
	}

	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type	distance(Iterator first, Iterator last, std::random_access_iterator_tag) {
		return last - first;
	}

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
		It operator+(int n) {_ptr +=n; return *this;}
		It operator-(int n) {_ptr -=n; return *this;}
		It &operator+=(std::ptrdiff_t n) {_ptr +=n; return *this;}
		It &operator-=(std::ptrdiff_t n) {_ptr -=n; return *this;}
		It &operator++() {_ptr++; return *this;}
		It &operator--() {_ptr--; return *this;}
		It operator++(int) {It tmp(*this); ++_ptr; return tmp;}
		It operator--(int) {It tmp(*this); --_ptr; return tmp;}
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

    template<class Pair>
    class it_map
    {
	private:
		typedef typename Pair::first_type			key_type;
		typedef typename Pair::second_type			mapped_type;
		typedef ft::node_rbt<key_type, mapped_type>	node;
		typedef ft::rbt<key_type, mapped_type>		rb_tree;
		typedef Pair								pair;
		node*										_base;
		rb_tree										_tree;
	public:
		typedef Pair								value_type;
		typedef ptrdiff_t							difference_type;
		typedef value_type*							pointer;
		typedef value_type&							reference;
		typedef bidirectional_iterator_tag			iterator_category;

		it_map() : _base(NULL) {}
		explicit it_map(node* pointer) : _base(pointer) {}
		it_map(const it_map& iter) : _base(iter.base()) {}
		~it_map() {}
		node	*base() const {return this->_base;}
		reference	operator*() const {return this->_base->pair;}
		pointer	operator->() const {return &(this->_base->pair);}

		it_map&	operator++() {
			this->_base = this->_tree.min_to_max(this->_base);
			return *this;
		}

		it_map	operator++(int n) {
			static_cast<void>(n);
			it_map<pair>	tmp(*this);
			this->_base = this->_tree.min_to_max(this->_base);
			return tmp;
		}

		it_map&	operator--() {
			this->_base = this->_tree.max_to_min(this->_base);
			return *this;
		}

		it_map	operator--(int n) {
			static_cast<void>(n);
			it_map<pair>	tmp(*this);
			this->_base = this->_tree.max_to_min(this->_base);
			return tmp;
		}
    };

	template <class Iterator>
	bool	operator==(const it_map<Iterator>& A, const it_map<Iterator>& B) {
		return A.base() == B.base();
	}

	template <class Iterator1, class Iterator2>
	bool	operator==(const it_map<Iterator1>& A, const it_map<Iterator2>& B) {
		return A.base() == B.base();
	}

	template <class Iterator>
	bool	operator!=(const it_map<Iterator>& A, const it_map<Iterator>& B) {
		return !(A == B);
	}

	template <class Iterator1, class Iterator2>
	bool	operator!=(const it_map<Iterator1>& A, const it_map<Iterator2>& B) {
		return !(A == B);
	}

    template<class Iterator>
    class reverse_it_map
    {
	private:
		Iterator											_base;
		typedef iterator_traits<Iterator>					_traits_type;
	public:
		typedef Iterator iterator_type;
		typedef typename _traits_type::value_type			value_type;
		typedef typename _traits_type::difference_type		difference_type;
		typedef typename _traits_type::pointer				pointer;
		typedef typename _traits_type::reference			reference;
		typedef typename _traits_type::iterator_category	iterator_category;

		reverse_it_map() : _base(Iterator()) {}
		explicit reverse_it_map(const Iterator& iter) : _base(iter) {}
		reverse_it_map(const reverse_it_map& iter) : _base(iter.base()) {}
		~reverse_it_map() {}
		iterator_type	base() const {return this->_base;}
		reference	operator*() const {return *(this->_base);}
		pointer	operator->() const {return &(*this->_base);}

		reverse_it_map&	operator++() {
			--this->_base;
			return *this;
		}

		reverse_it_map	operator++(int n) {
			static_cast<void>(n);
			reverse_it_map<Iterator>	tmp(*this);
			--this->_base;
			return tmp;
		}

		reverse_it_map	operator+(difference_type n) const {
			return reverse_it_map<Iterator>(this->_base - n);
		}

		reverse_it_map&	operator+=(difference_type n) {
			this->_base -= n;
			return *this;
		}


		reverse_it_map&	operator--() {
			++this->_base;
			return *this;
		}

		reverse_it_map	operator--(int n) {
			static_cast<void>(n);
			reverse_it_map<Iterator>	tmp(*this);
			++this->_base;
			return tmp;
		}

		reverse_it_map operator-(difference_type n) const {return reverse_it_map<Iterator>(this->_base + n);}

		reverse_it_map&	operator-=(difference_type n) {
			this->_base += n;
			return *this;
		}

		reference		operator[](difference_type n) const {return *(*this + n);}
    };

	template <class Iterator>
	bool	operator==(const reverse_it_map<Iterator>& A, const reverse_it_map<Iterator>& B) {
		return A.base() == B.base();
	}

	template <class Iterator1, class Iterator2>
	bool	operator==(const reverse_it_map<Iterator1>& A, const reverse_it_map<Iterator2>& B) {
		return *(A.base()) == *(B.base());
	}

	template <class Iterator>
	bool	operator!=(const reverse_it_map<Iterator>& A, const reverse_it_map<Iterator>& B) {
		return !(A == B);
	}

	template <class Iterator1, class Iterator2>
	bool	operator!=(const reverse_it_map<Iterator1>& A, const reverse_it_map<Iterator2>& B) {
		return !(A == B);
	}

	template <class Iterator>
	bool	operator<(const reverse_it_map<Iterator>& A, const reverse_it_map<Iterator>& B) {
		return A.base() > B.base();
	}

	template <class Iterator1, class Iterator2>
	bool	operator<(const reverse_it_map<Iterator1>& A, const reverse_it_map<Iterator2>& B) {
		return *(A.base()) > *(B.base());
	}

	template <class Iterator>
	bool	operator<=(const reverse_it_map<Iterator>& A, const reverse_it_map<Iterator>& B) {
		return A < B || A == B;
	}

	template <class Iterator1, class Iterator2>
	bool	operator<=(const reverse_it_map<Iterator1>& A, const reverse_it_map<Iterator2>& B) {
		return A < B || A == B;
	}

	template <class Iterator>
	bool	operator>(const reverse_it_map<Iterator>& A, const reverse_it_map<Iterator>& B) {
		return A.base() < B.base();
	}

	template <class Iterator1, class Iterator2>
	bool	operator>(const reverse_it_map<Iterator1>& A, const reverse_it_map<Iterator2>& B) {
		return *(A.base()) < *(B.base());
	}

	template <class Iterator>
	bool	operator>=(const reverse_it_map<Iterator>& A, const reverse_it_map<Iterator>& B) {
		return A > B || A == B;
	}

	template <class Iterator1, class Iterator2>
	bool	operator>=(const reverse_it_map<Iterator1>& A, const reverse_it_map<Iterator2>& B) {
		return A > B || A == B;
	}

	template <class Iterator>
	reverse_it_map<Iterator>	operator+(typename reverse_it_map<Iterator>::difference_type n, const reverse_it_map<Iterator>& it) {
		return reverse_it_map<Iterator>(it - n);
	}

	template <class Iterator>
	typename reverse_it_map<Iterator>::difference_type	operator-(const reverse_it_map<Iterator>& first, const reverse_it_map<Iterator>& second) {
		return first.base() - second.base();
	}
}

template <typename T>
void	swap(T &x, T &y)
{
	T tmp = x;
	x = y;
	y = tmp;
};
#endif