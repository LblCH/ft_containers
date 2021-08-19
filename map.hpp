#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <utility>
#include "iterator.hpp"
#include "rbt.hpp"

namespace ft {
    template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map {
	private:
		typedef node_rbt<Key, T>*     					                       		node;
		typedef rbt<Key, T> 														rbt;
		typedef ft::pair<Key, T> 													pair;

		rbt																			_tree;
		node*																		_root;
		node*																		_end;
		Alloc			                                                      		_alloc;
		Compare																		_k_comp;
		ft::less<ft::pair<const Key, T>>											_v_comp;
		size_t		                                                           		_size;

	public:
        typedef Key                                                         		key_type;
        typedef T                                                           		mapped_type;
        typedef ft::pair<const typename check_const<key_type>::type, mapped_type>	value_type;
        typedef Compare                                                     		key_compare;
        typedef ft::less<ft::pair<const Key, T>>                            		value_compare;
        typedef Alloc                                                       		allocator_type;
        typedef typename allocator_type::reference                          		reference;
        typedef typename allocator_type::const_reference                    		const_reference;
        typedef typename allocator_type::pointer                            		pointer;
        typedef typename allocator_type::const_pointer                      		const_pointer;
        typedef typename ft::it_map<ft::pair<Key, T>>                				iterator;
    	typedef typename ft::it_map<const ft::pair<Key, T>>		    				const_iterator;
    	typedef typename ft::reverse_it_map<iterator>	    						reverse_iterator;
    	typedef typename ft::reverse_it_map<const_iterator>  						const_reverse_iterator;
    	typedef ptrdiff_t															difference_type;
    	typedef size_t   															size_type;

		explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _k_comp(comp),
				_alloc(alloc), _root(NULL), _end(NULL), _size(0) {
			this->_end = this->_tree.create_node(ft::make_pair(key_type(), mapped_type()), NULL);
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(),
				char (*)[sizeof(*first)] = NULL) : _k_comp(comp),
				_alloc(alloc), _root(NULL), _end(NULL), _size(0) {
			this->_end = this->_tree.create_node(ft::make_pair(key_type(), mapped_type()), NULL);
			this->insert(first, last);
		}

		map (const map& x) : _root(NULL), _end(NULL), _size(0) {
			this->_end = this->_tree.create_node(ft::make_pair(key_type(), mapped_type()), NULL);
			*this = x;
		}

		~map() {
			this->_tree.clear(&this->_root, this->_end);
		}

		map&	operator=(const map& rhs) {
			this->_k_comp = rhs._k_comp;
			this->_v_comp = rhs._v_comp;
			this->clear();
			this->_alloc = rhs._alloc;
			this->insert(rhs.begin(), rhs.end());
			this->_size = rhs._size;
			return *this;
		}

		/* Iterators */

		iterator begin() {
			if (!this->_root)
				return iterator(this->_end);
			return iterator(this->_tree.min_node(this->_root));
		}

		const_iterator begin() const {
			if (!this->_root)
				return const_iterator(this->_end);
			return const_iterator(this->_tree.min_node(this->_root));
		}

		iterator end() {
			return iterator(this->_end);
		}

		const_iterator end() const {
			return const_iterator(this->_end);
		}

		reverse_iterator rbegin() {
			if (!this->_root)
				return reverse_iterator(iterator(this->_end));
			return reverse_iterator(iterator(this->_tree.max_node(this->_root)));
		}

		const_reverse_iterator rbegin() const {
			if (!this->_root)
				return const_reverse_iterator(const_iterator(this->_end));
			return const_reverse_iterator(const_iterator(this->_tree.max_node(this->_root)));
		}

		reverse_iterator rend() {
			return reverse_iterator(iterator(this->_end));
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(const_iterator(this->_end));
		}

		/* Capacity */

		bool empty() const {
			return _size == 0;
		}

		size_type size() const {
			return this->_size;
		}

		size_type max_size() const {
			return this->_tree.max_size();
		}

		/* Element access */

		mapped_type& operator[] (const key_type& k) {
			this->_tree.insert(&this->_root, this->_tree.create_node(ft::make_pair(k, mapped_type()), this->_end));
			return this->_tree.find_node(&this->_root, k)->pair.second;
		}

		/* Modifiers */

		ft::pair<iterator, bool>	insert(const value_type& val) {
			bool	ret = this->_tree.insert(&this->_root, this->_tree.create_node(val, this->_end));
			if (ret)
				++this->_size;
			node*	n = this->_tree.find_node(&this->_root, val.first);
			if (n)
				return ft::pair<iterator, bool>(iterator(n), ret);
			return ft::pair<iterator, bool>(iterator(this->_end), ret);
		}
		iterator insert (iterator position, const value_type& val) {
			bool	ret = this->_tree.insert(&this->_root, this->_tree.create_node(val, this->_end));
			if (ret)
				++this->_size;
			node*	n = this->_tree.find_node(&this->_root, val.first);
			if (n)
				return iterator(n);
			return iterator(this->_end);
		}
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
			for (; first != last; ++first)
				this->insert(*first);
		}

		void erase (iterator position) {
			bool	ret = this->_tree.erase(&this->_root, position->first);
			if (ret)
				--this->_size;
		}
		size_type erase (const key_type& k) {
			bool	ret = this->_tree.erase(&this->_root, k);
			if (ret)
				--this->_size;
			return static_cast<size_type>(ret);
		}
		void erase (iterator first, iterator last) {
			for (; first != last;)
				this->erase(first++);
		}

		void	swap(map& x) {
			map	tmp = *this;
			*this = x;
			x = tmp;
		}

		void clear() {
			this->_tree.clear(&this->_root);
			this->_size = 0;
		}
    };
}



#endif //FT_CONTAINERS_MAP_HPP
