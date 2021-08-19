#ifndef FT_CONTAINERS_RBT_HPP
#define FT_CONTAINERS_RBT_HPP

#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>


#define RED true
#define BLACK false

namespace ft {
	template<class Key, class Value>
	class pair {
	public:
		typedef Key first_type;
		typedef Value second_type;
		first_type first;
		second_type second;
	public:
		pair() : first(first_type()), second(second_type()) {}

		template<class U, class V>
		pair(const pair<U, V> &pr) : first(static_cast<U>(pr.first)), second(static_cast<V>(pr.second)) {}

		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		pair &operator=(const pair &pr) {
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}
	};

	template<class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return !(lhs == rhs);
	}

	template<class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return !(rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return rhs < lhs;
	}

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return !(lhs < rhs);
	}

	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y) {
		return ft::pair<T1, T2>(x, y);
	}

	template<class T>
	struct less : std::binary_function<T, T, bool> {
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;

		bool operator()(const T &x, const T &y) const {
			return x < y;
		}
	};

	template<class T>
	struct less<ft::pair<T, class Value> > : std::binary_function<T, T, bool> {
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;

		bool operator()(const T &x, const T &y) const {
			return x.first < y.first;
		}
	};

	template<class Key, class T, class Alloc = std::allocator<ft::pair<Key, T> > >
	class node_rbt {
	public:
		ft::pair<const Key, T>*    	pair;
		node_rbt*                   parent;
		node_rbt*			        left;
		node_rbt*		        	right;
		node_rbt*					end;
		bool		        		color;

		node_rbt() : parent(NULL), left(NULL), right(NULL), end(NULL), color(RED) {}
		node_rbt(ft::pair<Key, T>& p_pair) : pair(p_pair), parent(NULL), left(NULL), right(NULL), end(NULL), color(RED_COLOR) {}
		node_rbt& operator=(const node_rbt& node)
		{
			this->pair = node.pair;
			this->parent = node.parent;
			this->left = node.left;
			this->right = node.right;
			this->end = node.end;
			this->color = node.color;
			return *this;
		}
	};

	template<class Key, class T, class Node_Alloc = std::allocator <node_rbt<Key, T>> >
	class rbt {
	private:
		Node_Alloc									_alloc;
	public:
		typedef Key 								first_type;
		typedef T 									second_type;
		typedef node_rbt <first_type, second_type> 	node;
		typedef ft::pair<first_type, second_type> 	pair;
		typedef Node_Alloc 							allocator_type;

		node *create_node(pair new_pair, node *end) {
			node *new_node = _alloc.allocate(1);
			_alloc.construct(new_node, node(new_pair));
			new_node->end = end;
			return new_node;
		}

		bool insert(node **root, node *new_node) {
			if (*root == NULL) {
				*root = new_node;
				new_node->end->parent = *root;
				new_node->color = BLACK;
			} else {
				node *tmp = *root;
				while (tmp) {
					if (tmp->pair.first == new_node->pair.first) {
						if (tmp != new_node)
							delete_node(new_node);
						return false;
					} else if (new_node->pair.first > tmp->pair.first) {
						if (tmp->right)
							tmp = tmp->right;
						else {
							tmp->right = new_node;
							new_node->parent = tmp;
							break;
						}
					} else {
						if (tmp->left)
							tmp = tmp->left;
						else {
							tmp->left = new_node;
							new_node->parent = tmp;
							break;
						}
					}
				}
			}
			insert_balance(root, new_node);
			return true;
		}

		node *min_node(node *n, bool root = true) const {
			if (n) {
				if (root) {
					while (n->parent)
						n = n->parent;
				}
				while (n->left)
					n = n->left;
			}
			return n;
		}

		node *max_node(node *n, bool root = true) const {
			if (n) {
				if (root) {
					while (n->parent)
						n = n->parent;
				}
				while (n->right) {
					n = n->right;
				}
			}
			return n;
		}

		node *find_node(node **root, first_type key) const {
			node *tmp = *root;
			while (tmp) {
				if (tmp->pair.first == key)
					return tmp;
				else if (key > tmp->pair.first) {
					if (tmp->right)
						tmp = tmp->right;
					else
						break;
				} else {
					if (tmp->left)
						tmp = tmp->left;
					else
						break;
				}
			}
			return NULL;
		}

		node *find_lower_node(node **root, first_type key) const {
			node *tmp = *root;
			while (tmp) {
				if (tmp->pair.first == key)
					return tmp;
				else if (key > tmp->pair.first) {
					if (tmp->right)
						tmp = tmp->right;
					else
						return NULL;
				} else {
					if (tmp->left)
						tmp = tmp->left;
					else
						return tmp;
				}
			}
			return NULL;
		}

		node *find_upper_node(node **root, first_type key) const {
			node *tmp = *root;
			while (tmp) {
				if (tmp->pair.first == key) {
					if (tmp->right)
						return tmp->right;
					return NULL;
				} else if (key > tmp->pair.first) {
					if (tmp->right)
						tmp = tmp->right;
					else
						return NULL;
				} else {
					if (tmp->left)
						tmp = tmp->left;
					else
						return tmp;
				}
			}
			return NULL;
		}

		bool erase(node **root, first_type key) {
			node *remove = find_node(root, key);
			if (remove) {
				node *replace = NULL;
				if (remove->left)
					replace = erase_left(remove, root);
				else if (remove->right)
					replace = erase_right(remove, root);
				else
					replace = erase_not_child(remove, root);
				if (replace) {
					remove->pair.first = replace->pair.first;
					remove->pair.second = replace->pair.second;
				} else
					replace = remove;
				if (replace == remove && remove == *root) {
					*root = NULL;
					if (replace->end)
						replace->end->parent = NULL;
				}
				delete_node(replace);
				return true;
			}
			return false;
		}

		node *min_to_max(node *n) const {
			if (n) {
				if (!n->end && !n->parent)
					n = n;
				else if (!n->end)
					n = min_node(n->parent);
				else if (n == max_node(n))
					n = n->end;
				else if (n->right) {
					n = min_node(n->right, false);
				} else if (n->parent) {
					while (n->parent->right == n)
						n = n->parent;
					n = n->parent;
				}
			}
			return n;
		}

		node *max_to_min(node *n) const {
			if (n) {
				if (!n->end && !n->parent)
					n = n;
				else if (!n->end)
					n = max_node(n->parent);
				else if (n == min_node(n))
					n = n->end;
				else if (n->left)
					n = max_node(n->left, false);
				else if (n->parent) {
					while (n->parent->left == n)
						n = n->parent;
					n = n->parent;
				}
			}
			return n;
		}

		void clear(node **n, node *end = NULL, bool root = true) {
			node *tmp = *n;
			if (tmp && tmp->end) {
				if (root) {
					while (tmp->parent)
						tmp = tmp->parent;
				}
				while (tmp)
					erase(&tmp, tmp->pair.first);
			}
			delete_node(end);
			*n = NULL;
		}

		size_t max_size() const {
			return _alloc.max_size();
		}

	private:
		node *erase_left(node *n, node **root) {
			node *replace = max_node(n->left, false);
			if (replace) {
				if (replace == n->left) {
					n->left = replace->left;
					if (replace->left)
						replace->left->parent = n;
				} else {
					replace->parent->right = replace->left;
					if (replace->left)
						replace->left->parent = replace->parent;
				}
				if (replace->color == BLACK_COLOR) {
					if (replace->left && replace->left->color == RED_COLOR)
						replace->left->color = BLACK_COLOR;
					erase_balance(root, replace->parent);
				}
			}
			return replace;
		}

		node *erase_right(node *n, node **root) {
			if (n->pair.first == 761)
				std::cout << n->right->pair.first << std::endl;
			node *replace = min_node(n->right, false);
			if (replace) {
				if (replace == n->right) {
					n->right = replace->right;
					if (replace->right)
						replace->right->parent = n;
				} else {
					replace->parent->left = replace->right;
					if (replace->right)
						replace->right->parent = replace->parent;
				}
				if (replace->color == BLACK_COLOR) {
					if (replace->right && replace->right->color == RED_COLOR)
						replace->right->color = BLACK_COLOR;
					erase_balance(root, replace->parent);
				}
			}
			return replace;
		}

		node *erase_not_child(node *n, node **root) {
			node *replace = n;
			if (replace && replace->parent) {
				if (replace->parent->right == replace)
					replace->parent->right = NULL;
				else
					replace->parent->left = NULL;
				if (replace->color == BLACK_COLOR) {
					if (replace->right && replace->right->color == RED_COLOR)
						replace->right->color = BLACK_COLOR;
					erase_balance(root, replace->parent);
				}
			}
			return replace;
		}

		void erase_balance(node **root, node *n) {
			node *right;
			node *left;
			node *child;
			while (n) {
				child = n->right;
				if (child) {
					right = child->right;
					left = child->left;
					if ((right || left) && (!right || right->color == BLACK_COLOR) &&
						(!left || left->color == BLACK_COLOR)) {
						if (child->color == BLACK_COLOR) {
							child->color = RED_COLOR;
							n->color = BLACK_COLOR;
						}
						if (child->color == RED_COLOR)
							rotate_left(n, root);
						else
							n = n->parent;
					} else if (right && child->color == BLACK_COLOR) {
						if (left && left->color == RED_COLOR && right->color == BLACK_COLOR) {
							rotate_right(child, root);
							right = child;
							child = left;
						}
						if (right->color == RED_COLOR && (!left || left->color == BLACK_COLOR || !n->left))
							rotate_left(n, root);
						else
							n = n->parent;
					} else if (child->color == BLACK_COLOR && n->color == RED_COLOR) {
						n->color = BLACK_COLOR;
						child->color = RED_COLOR;
						n = n->parent;
					} else
						n = n->parent;
				} else
					n = n->parent;
				if (*root)
					(*root)->color = BLACK_COLOR;
			}
		}

		void delete_node(node *n) {
			if (n) {
				_alloc.destroy(n);
				_alloc.deallocate(n, 1);
			}
		}

		void insert_balance(node **root, node *n) {
			node *parent;
			node *grand;
			node *tmp;
			while (n) {
				parent = n->parent;
				grand = NULL;
				tmp = parent;
				if (parent) {
					grand = parent->parent;
					if (n->color == RED) {
						if (parent->color == BLACK)
							n = parent;
						else if (grand) {
							if (grand->left && grand->left->color == RED && grand->right &&
								grand->right->color == RED) {
								swap_color(grand);
								n = grand;
							} else if (grand->right == parent) {
								if (parent->left == n) {
									rotate_right(parent, root);
									parent = n;
								}
								if (parent->right == n)
									rotate_left(grand, root);
								n = parent->parent;
							} else {
								if (parent->right == n) {
									rotate_left(parent, root);
									parent = n;
								}
								if (parent->left == n)
									rotate_right(grand, root);
								n = parent->parent;
							}
						}
					} else
						n = parent;
				} else {
					n->color = BLACK;
					n = n->parent;
				}
			}
		}

		void rotate_left(node *n, node **root) {
			node *right = n->right;
			right->parent = n->parent;
			if (right->parent) {
				if (right->parent->right == n)
					right->parent->right = right;
				else
					right->parent->left = right;
			}
			n->parent = right;
			n->right = right->left;
			if (n->right) {
				if (n->right->parent == right)
					n->right->parent = n;
				else
					n->right->parent = n;
			}
			right->left = n;
			bool color = n->color;
			n->color = right->color;
			right->color = color;
			if (!right->parent)
				*root = right;
		}

		void rotate_right(node *n, node **root) {
			node *left = n->left;
			left->parent = n->parent;
			if (left->parent) {
				if (left->parent->left == n)
					left->parent->left = left;
				else
					left->parent->right = left;
			}
			n->parent = left;
			n->left = left->right;
			if (n->left) {
				if (n->left->parent == left)
					n->left->parent = n;
				else
					n->left->parent = n;
			}
			left->right = n;
			n->color = RED_COLOR;
			left->color = BLACK_COLOR;
			if (!left->parent)
				*root = left;
		}

		void swap_color(node *n) {
			bool color = n->color;
			n->color = n->right->color;
			n->right->color = color;
			n->left->color = color;
		}
	};
}

#endif //FT_CONTAINERS_RBT_HPP
