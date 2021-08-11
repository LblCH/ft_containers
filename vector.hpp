#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T                                           value_type;
		typedef Alloc										allocator_type;
		typedef std::ptrdiff_t                              difference_type;
		typedef size_t                                      size_type;

		typedef T&                                          reference;
		typedef const T&                                    const_reference;
		typedef T*                                          pointer;
		typedef const T*                                    const_pointer;

		typedef typename ft::It<T>							iterator;
		typedef typename ft::It<const T>					const_iterator;
		typedef typename ft::Rev_It<T>						reverse_iterator;
		typedef typename ft::Rev_It<const T>				const_reverse_iterator;

	private:

		Alloc				_alloc;
		pointer				_vector;
		size_type			_size;
		size_type			_capacity;

	public:

	/* Member functions */

		explicit vector (const allocator_type& alloc = allocator_type()) :
		_alloc(alloc), _vector(NULL), _size(0), _capacity(0) {}

		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()) :
						 _alloc(alloc), _size(0), _capacity(n)
		{
			_vector = _alloc.allocate(n);
			insert(begin(), n, val);
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				char (*)[sizeof(*first)] = NULL) :
				_alloc(alloc), _size(0)
		{
			InputIterator it = first;
			size_t n = 0;
			while (it++ != last)
				n++;
			_vector = _alloc.allocate(n);
			_capacity = n;
			insert(begin(), first, last);
		}

		vector (const vector& x) {*this = x;};

		~vector() {clear(); _alloc.deallocate(_vector, _capacity);}

		vector &operator=(const vector &rhs)
		{
			_alloc = rhs._alloc;
			_capacity = rhs._capacity;
			_size = rhs._size;
			_vector = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_vector + i, rhs._vector[i]);
			return *this;
		}

	/* Iterators */

		iterator begin() {return _vector;}
		const_iterator begin() const {return _vector;}
		iterator end() {return _vector + _size;}
		const_iterator end() const {return _vector + _size;}
		reverse_iterator rbegin() {return _vector + _size - 1;}
		const_reverse_iterator rbegin() const {return _vector + _size - 1;}
		reverse_iterator rend() {return  _vector - 1;}
		const_reverse_iterator rend() const {return  _vector - 1;}

	/* Capacity */

		size_type size() const {return _size;}
		size_type max_size() {return _alloc.max_size();}
		void resize(size_type n, value_type val = value_type())
		{
			if (n > max_size())
				throw std::out_of_range("vector");
			else if (!n)
				return;
			else if (n < size())
			{
				for (size_type i = 0; i + n < _size; ++i)
					_alloc.destroy(_vector + n + i);
				_size = n;
			}
			else
				insert(end(), n - _size, val);
		}
		size_type capacity() const {return _capacity;}
		bool empty() const {return _size == 0;}
		void reserve (size_type n)
		{
			if (n < _capacity)
				return;
			pointer new_vector = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(new_vector + i, _vector[i]);
			_alloc.deallocate(_vector, _size);
			_capacity = n;
			_vector = new_vector;
		}

	/* Element access */
		reference operator[] (size_type n) {return _vector[n];}
		const_reference operator[] (size_type n) const {return _vector[n];}
		reference at (size_type n)
		{
			if (n < 0 || n >= _size)
				throw std::out_of_range("vector");
			return _vector[n];
		}
		const_reference at (size_type n) const
		{
			if (n < 0 || n >= _size)
				throw std::out_of_range("vector");
			return _vector[n];
		}
		reference front() {return _vector[0];}
		const_reference front() const {return _vector[0];}
		reference back() {return _vector[_size - 1];}
		const_reference back() const {return _vector[_size - 1];}

	/* Modifiers */

		/* Assign */
			/* range (1) */
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			clear();
			while(first != last)
				push_back(*first++);
		}
			/* fill (2) */
		void assign (size_type n, const value_type& val)
		{
			clear();
			_alloc.deallocate(_vector, _capacity);
			_vector = _alloc.allocate(n);
			_size = n;
			_capacity = n;
			for(size_type i = 0; i < n; ++i)
				_alloc.construct(_vector + i, val);
		}

		void push_back(const value_type& val)
		{
			if (_capacity == 0)
			{
				_vector = _alloc.allocate(2);
				_alloc.construct(_vector, val);
				_size = 1;
				_capacity = 1;
			}
			else
			{
				if (_size + 1 > _capacity)
				{
					pointer new_vector = _alloc.allocate(_capacity * 2);
					for(size_type i = 0; i < _size; ++i)
						_alloc.construct(new_vector + i, _vector[i]);
					_alloc.deallocate(_vector, _capacity);
					_capacity *= 2;
					_vector = new_vector;
				}
				_alloc.construct(_vector + _size, val);
				_size++;
			}
		}

		void pop_back() {
			_alloc.destroy(&this->back());
			_size--;
		}

		/* Insert */
			/* single element (1) */
		iterator insert (iterator position, const value_type& val)
		{
			insert(position, 1, val);
			return ++position;
		}

			/* fill (2) */
		void insert (iterator position, size_type n, const value_type& val)
		{
			iterator it = begin();
			size_type cap = _capacity ? _capacity : n;
			while(_size + n > cap)
				cap *= 2;
			reserve(cap);
			size_type i = 0;
			while (it != &(*position)) {i++; it++;}
			for (size_type j = _size; j >= 1 && j >= i; j--)
				new(&_vector[i + j + n - 1]) value_type(_vector[j - 1]);
			for (size_type j = 0; j < n; j++)
				new(&_vector[i + j]) value_type(val);
			_size += n;
		}

			/* range (3) */
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
		{
			size_type size = 0;
			for(InputIterator it = first; it != last ; ++it)
				size++;
			iterator it = begin();
			size_type cap = _capacity ? _capacity : size;
			while(_size + size > cap)
				cap *= 2;
			reserve(cap);
			size_type i = 0;
			while (it != &(*position)) {i++; it++;}
			for (size_type j = _size - 1; j > i + 1; j++)
				new(&_vector[i + j + size]) value_type(_vector[j - 1]);
			for (size_type j = 0; j < size; j++)
				new(&_vector[i + j]) value_type(*first++);
			_size += size;
		}

		/* Erase */
		iterator erase (iterator position)
		{
			size_type i = 0;
			for(; _vector + i != &(*position); ++i);
			for(size_type j = i; _vector + j != _vector + _size; ++j)
			{
				_alloc.construct(_vector + j, _vector[j + 1]);
				_alloc.destroy(_vector + j + 1);
			}
			_size--;
			return (iterator(_vector + i));
		}
		iterator erase (iterator first, iterator last)
		{
			size_type start = 0;
			for(;_vector + start != &(*first); ++start);
			size_type end = 0;
			for(iterator it = first; it != last; ++end, ++it);
			size_type i = start;
			for(iterator it = first; it != last; ++i, ++it, --_size)
			{
				_alloc.destroy(_vector + i);
				_alloc.construct(_vector + i, _vector[i + end]);
				_alloc.destroy(_vector + i + end);
			}
			return iterator(_vector + start);
		}

		void swap(vector& x)
		{
			allocator_type tmp_alloc = _alloc;
			pointer	tmp_vector = _vector;
			size_type tmp_size = _size;
			size_type tmp_capacity = _capacity;

			_alloc = x._alloc;
			_vector = x._vector;
			_size = x._size;
			_capacity = x._capacity;

			x._alloc = tmp_alloc;
			x._vector = tmp_vector;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
		}

		void clear()
		{
			if (_vector != NULL){
				for(size_type i = 0; i < _size; i++)
					_alloc.destroy(_vector + i);
				_size = 0;
			}
		}
	};

	/* Non-member function overloads */
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename ft::vector<T>::const_iterator first1 = lhs.begin();
		typename ft::vector<T>::const_iterator last1 = lhs.end();
		typename ft::vector<T>::const_iterator first2 = rhs.begin();
		typename ft::vector<T>::const_iterator last2 = rhs.end();

		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{return (!(rhs < lhs));}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{return (rhs < lhs);}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{return (!(lhs < rhs));}

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {swap(x, y);}
}
#endif //FT_CONTAINERS_VECTOR_HPP
