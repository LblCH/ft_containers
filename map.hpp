#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <utility>
#include "iterator.hpp"

#define RED true
#define BLACK false

template<typename Key, typename T>
struct node_map {
public:
    std::pair<const Key, T>*    pair;
    node_map*                   parent;
    node_map*			        left;
    node_map*		        	right;
    bool		        		color;
};

namespace ft {
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
    class map {
    public:
        typedef Key                                                         key_type;
        typedef T                                                           mapped_type;
        typedef std::pair<const Key, T>                                     value_type;
        typedef Compare                                                     key_compare;
        typedef Compare                                                     value_compare;
        typedef Alloc                                                       allocator_type;
        typedef typename allocator_type::reference                          reference;
        typedef typename allocator_type::const_reference                    const_reference;
        typedef typename allocator_type::pointer                            pointer;
        typedef typename allocator_type::const_pointer                      const_pointer;
        typedef typename ft::it_map<key_type, mapped_type>                	iterator;
        typedef typename ft::const_it_map<key_type, mapped_type>		    const_iterator;
    	typedef typename ft::reverse_it_map<key_type, mapped_type>	    	reverse_iterator;
        typedef typename ft::const_reverse_it_map<key_type, mapped_type>  	const_reverse_iterator;
        typedef ptrdiff_t	 											    difference_type;
        typedef size_t                                                      size_type;
    private:
        typedef node_map<key_type, mapped_type>*                            node;
        typedef typename allocator_type::template rebind<node_map<key_type, mapped_type> >::other	alloc_node;

        allocator_type                                                      _alloc;
        alloc_node                                                          _node_alloc;
        node                                                                _map;
        node                                                                _end_node;
        size_type                                                           _size;

        /* map-specific methods */
        node    _create_node(key_type key = key_type(), mapped_type value = mapped_type(), node parent = NULL)
        {
            node new_node = _node_alloc.allocate(1);
			value_type * new_pair = _alloc.allocate(1);
			_alloc.construct(new_pair, std::make_pair(key, value));

			new_node->pair = new_pair;
			new_node->right = 0;
			new_node->left = 0;
			new_node->parent = parent;
			new_node->color = RED;
			++_size;
			return new_node;
        }

        node	_insert(node n, key_type key, mapped_type value)
		{
        	node new_node;
			if (key < n->pair->first)
			{
				if (!n->left)
				{
					n->left = _create_node(key, value, n);
					new_node = n->left;
					_balance(n->left);
					_end();
					return new_node;
				}
				new_node = _insert(n->left, key, value);
				return new_node;
			}
			else if (key > n->pair->first)
			{
				if (!n->right)
				{
					n->right = _create_node(key, value, n);
					new_node = n->right;
					_balance(n->right);
					_end();
					return new_node;
				}
				new_node = _insert(n->right, key, value);
				return new_node;
			}
			return 0;
		}

		node 	_end()
		{
        	_end_node = _map;
			while (_end_node)
				_end_node = _end_node->right;
		}
    };
}



#endif //FT_CONTAINERS_MAP_HPP
