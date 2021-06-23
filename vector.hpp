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
		_size(0), _capacity(0), _alloc(alloc), _vector(NULL) {}

		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()) :
						 _alloc(alloc), _capacity(n), _size(0)
		{
			_vector = _alloc.allocate(n);
			insert(begin(), n, val);
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type())
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

		}

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

		/* Modifiers */

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
			while(_size + n >= cap)
				cap *= 2;
			reserve(cap * 2);
			size_type i = 0;
			while (_vector + i != &(*position)) i++;
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
			size_type size = last - first;
			size_type cap = _capacity ? _capacity : size;
			while(_size + size >= cap)
				cap *= 2;
			reserve(cap * 2);
			size_type i = 0;
			while (_vector + i != &(*position)) i++;
			for (size_type j = _size - 1; j > i + 1; j++)
				new(&_vector[i + j + size]) value_type(_vector[j - 1]);
			for (size_type j = 0; j < size; j++)
				new(&_vector[i + j]) value_type(*first++);
			_size += size;
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
}
#endif //FT_CONTAINERS_VECTOR_HPP
