#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "utils.hpp"
# include "RB_tree.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"

# include <iostream>

namespace	ft
{

template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator< pair<const Key,T> >    // map::allocator_type
           >
class map
{
public:

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const key_type, mapped_type>		value_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef map_iterator<false, value_type>				iterator;
	typedef	map_iterator<true, value_type>				const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t	size_type;
	typedef	RB_node<value_type>	node_type;
	typedef	RB_tree<value_type>	rb_tree;
	class value_compare
	{
		friend class map;
	protected:
		key_compare comp;
		value_compare (key_compare c) : comp(c) {}
	public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};


	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: _size(0), tree(new rb_tree()), A(alloc), comp(comp)
	{}
			  
	template <class InputIterator>
	map(InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
	:_size(0), tree(new rb_tree()), A(alloc), comp(comp)
	{
		insert(first, last);
	}
		
	map(const map& x)	
	:_size(0), tree(new rb_tree()), A(x.A), comp(x.comp)
	{
		insert(x.begin(), x.end());
	}
	virtual ~map()	{
		clear();
		delete tree;
	}

	map& operator=(const map& x)	{
		clear();
		_size = 0;
		A = x.A;
		comp = x.comp;
		insert(x.begin(), x.end());
		return *this;
	}

	void printMap(void) // A SUPPRIMER
	{
		node_type * r = tree->root;
		if (r == tree->LEAF)
			std::cout << "RIEN DANS LARBRE !\n";
		std::cout << "HEAD: " << r->value->first << " - n:" << r << " - p:" << r->parent << " - l:" << r->less << " - r:" << r->more << "\n"; // 6
		print2D(r, 1);
	}

	void print2D(node_type *r, int space)	{
		if (r == tree->LEAF) // Base case  1
			return;
		space += 2; // Increase distance between levels   2
		print2D(r->more, space); // Process right child first 3 
		std::cout << std::endl;
		for (int i = 1; i < space; i++) // 5 
		{
			std::cout << "    "; // 5.1
		}
		std::cout << r->value->first << " - col:";
		if (r->color)
			std::cout << "BLACK";
		else
			std::cout << "\e[0;31mRED\e[0m";
		std::cout << " - n:" << r << " - p:" << r->parent << " - l:" << r->less << " - r:" << r->more << "\n"; // 6
		print2D(r->less, space); // Process left child  7
	}

// ITERATORS
	iterator begin()	{
		return iterator(tree->min_node());
	}
	const_iterator begin() const	{
		return const_iterator(tree->min_node());
	}
	iterator end()	{
		return iterator(tree->LEAF);
	}
	const_iterator end() const	{
		return const_iterator(tree->LEAF);
	}
	reverse_iterator rbegin()	{
		return reverse_iterator(tree->LEAF);
	}
	const_reverse_iterator rbegin() const	{
		return const_reverse_iterator(tree->LEAF);
	}
	reverse_iterator rend()	{
		return reverse_iterator(tree->min_node());
	}
	const_reverse_iterator rend() const	{
		return const_reverse_iterator(tree->min_node());
	}

// CAPACITY
	bool empty() const	{
		return _size == 0;
	}
	size_type size() const	{
		return _size;
	}
	size_type max_size() const	{
		try	{
			return node_A.max_size();
		}
		catch(const std::exception& e)	{
			std::cerr << e.what() << '\n';
		}
		return -1;
	}

// ACCESS
	mapped_type& operator[] (const key_type& k)	{
		return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
	}

// MODIFIERS
	pair<iterator,bool> insert (const value_type& val)	{
		node_type **dst = &tree->root;
		node_type *parent = NULL;

		while (*dst != tree->LEAF)	{
			parent = *dst;
			if (comp(val.first, (*dst)->value->first))
				dst = &(*dst)->less;
			else if (comp((*dst)->value->first, val.first))
				dst = &(*dst)->more;
			else
				return ft::make_pair(iterator(*dst), false);
		}
		value_type *new_val = A.allocate(1);
		A.construct(new_val, val);
		node_type *new_node = node_A.allocate(1);
		node_A.construct(new_node, node_type(new_val, *tree));
		tree->insert(parent, *dst, new_node);
		_size++;
		return ft::make_pair(iterator(new_node), true);
	}

	iterator insert (iterator position, const value_type& val)	{
		(void) position;
		return insert(val).first;
	}
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)	{
		for (; first != last; first++)
			insert(*first);
	}

	void erase (iterator position)	{
		node_type	*del = position.node();
		tree->delete_node(del);

		A.destroy(del->value);
		A.deallocate(del->value, 1);
		node_A.destroy(del);
		node_A.deallocate(del, 1);
		_size--;
	}
	size_type erase (const key_type& k)	{
		node_type *node = get_node(k);
		if (node == tree->LEAF)
			return 0;
		erase(iterator(node));
		return 1;
	}
	void erase (iterator first, iterator last)	{
		iterator tmp = first;

		while (tmp != last)	{
			erase(tmp++);
		}		
	}

	void swap (map& x)	{
		ft::swap(_size, x._size);
		ft::swap(tree, x.tree);
		ft::swap(A, x.A);
		ft::swap(comp, x.comp);
	}

	friend
	void swap (map& x, map &y)	{
		x.swap(y);
	}

	void clear()	{
		erase(begin(), end());
	}

// OBSERVERS
	key_compare key_comp() const	{
		return comp;
	}

	value_compare	value_comp() const	{
		return value_compare(comp);
	}

	allocator_type	get_allocator() const	{
		return A;
	}

// OPERATIONS
	iterator find (const key_type& k)	{
		node_type	*node = get_node(k);
		if (node == tree->LEAF)
			return end();
		return iterator(node);
	}
	const_iterator find (const key_type& k) const	{
		node_type	*node = get_node(k);
		if (node == tree->LEAF)
			return end();
		return const_iterator(node);
	}
	
	size_type count (const key_type& k) const	{
		node_type	*node = get_node(k);
		if (node == tree->LEAF)
			return 0;
		return 1;
	}

	iterator 	lower_bound(const key_type& k)	{
		pair<node_type*, node_type*> res = get_node_parent(k);
		if (res.first != tree->LEAF)
			return iterator(res.first);
		if (res.second == NULL)
			return end();
		if (!comp(res.second->value->first, k))
			return iterator(res.second);
		return ++iterator(res.second);
	}
	const_iterator lower_bound(const key_type& k) const	{
		pair<node_type*, node_type*> res = get_node_parent(k);
		if (res.first != tree->LEAF)
			return const_iterator(res.first);
		if (res.second == NULL)
			return end();
		if (!comp(res.second->value->first, k))
			return const_iterator(res.second);
		return ++const_iterator(res.second);
	}

	iterator upper_bound (const key_type& k)	{
		pair<node_type*, node_type*> res = get_node_parent(k);
		if (res.first != tree->LEAF)
			return ++iterator(res.first);
		if (res.second == NULL)
			return end();
		if (comp(k, res.second->value->first))
			return iterator(res.second);
		return ++iterator(res.second);
	}
	const_iterator upper_bound (const key_type& k) const	{
		pair<node_type*, node_type*> res = get_node_parent(k);
		if (res.first != tree->LEAF)
			return const_iterator(res.first->successor());
		if (res.second == NULL)
			return end();
		if (comp(k, res.second->value->first))
			return const_iterator(res.second);
		return ++const_iterator(res.second);
	}

	pair<const_iterator,const_iterator> equal_range (const key_type& k) const	{
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}
	pair<iterator,iterator>             equal_range (const key_type& k)	{
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}

// REL. OPERATORS
	friend
	bool operator== (const map& lhs, const map& rhs)	{
		if (lhs._size != rhs._size)
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	friend
	bool operator!= (const map& lhs, const map& rhs)	{
		return !(lhs == rhs);
	}
	
	friend
	bool operator<  (const map& lhs, const map& rhs)	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	friend
	bool operator<= (const map& lhs, const map& rhs)	{
		return !(rhs < lhs);
	}

	friend
	bool operator>  (const map& lhs, const map& rhs)	{
		return rhs < lhs;
	}

	friend
	bool operator>= (const map& lhs, const map& rhs)	{
		return !(lhs < rhs);
	}


private:
	size_type		_size;
	rb_tree			*tree;
	allocator_type	A;
	key_compare		comp;
	std::allocator<node_type>	node_A;



	node_type *get_node(const key_type& key) const	{
		node_type	*n = tree->root;

		while (n != tree->LEAF)	{
			if (comp(n->value->first, key))
				n = n->more;
			else if (comp(key, n->value->first))
				n = n->less;
			else
				return n;
		}
		return (n);
	}

	pair<node_type*, node_type*>	get_node_parent(const key_type& key) const	{
		node_type	*n = tree->root;
		node_type	*parent = NULL;
	
		while (n != tree->LEAF)	{
			if (comp(n->value->first, key))	{
				parent = n;
				n = n->more;
			}
			else if (comp(key, n->value->first))	{
				parent = n;
				n = n->less;
			}
			else
				return ft::make_pair(n, parent);
		}
		return (ft::make_pair(n, parent));
	}

};

}

#endif