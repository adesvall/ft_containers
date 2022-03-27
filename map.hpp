#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "utils.hpp"
# include "RB_tree.hpp"
# include "map_iterator.hpp"

namespace	ft
{

template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator< RB_node<pair<const Key,T> > >    // map::allocator_type
           >
class map
{
public:
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef pair<const key_type, mapped_type>			value_type;
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

	explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
	_size(0), A(alloc), comp(comp), tree(comp)
	{
		
	}
			  
	template <class InputIterator>
	map(InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type());
		
	map(const map& x);
	virtual ~map();

	map& operator=(const map& x);

// CAPACITY
	bool empty() const	{
		return _size == 0;
	}
	size_type size() const	{
		return _size;
	}
	size_type max_size() const	{
		try	{
			return A.max_size();
		}
		catch(const std::exception& e)	{
			std::cerr << e.what() << '\n';
		}
		return -1;
	}

// ACCESS
	mapped_type& operator[] (const key_type& k)	{
		return (*((insert(make_pair(k, mapped_type()))).first)).second;
	}

// MODIFIERS
	pair<iterator,bool> insert (const value_type& val)	{
		node_type **dst = root;
		node_type *parent = NULL;

		while (*dst != LEAF && (*dst)->value.first != n->value.first)	{
			parent = *dst;
			if (comp(n->value.first , (*dst)->value))
				dst = &(*dst)->less;
			else
				dst = &(*dst)->more;
		}
		if (*dst != LEAF)
			return make_pair(iterator(*dst), false);
		node_type *new_node = A.allocate(1);
		A.construct(new_node, node_type(val));
		tree.insert(parent, *dst, new_node);
		_size++;
		return make_pair(iterator(new_node), true);
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
		tree.delete_node(del);
		A.destroy(del);
		A.deallocate(del, 1);
		size--;
	}
	size_type erase (const key_type& k)	{
		node_type *node = tree.get_node(k);
		if (node == LEAF)
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
		swap(_size, x._size);
		swap(tree, x.tree);
		swap(A, x.A);
		swap(comp, x.comp);
	}

	void clear()	{
		erase(begin(), end());
	}

// OBSERVERS
	key_compare key_comp() const	{
		return comp;
	}

	value_compare	value_comp() const{
		return value_compare(comp);
	}

	allocator_type	get_allocator() const	{
		return A;
	}

private:
	typedef	RB_node<value_type>	node_type;
	typedef	RB_tree<key_type, mapped_type>	rb_tree;

	size_type		_size;
	rb_tree			tree;
	allocator_type	A;
	key_compare		comp;
	// RB_node			leaf;

	node_type *get_node(key_type& key)	{
		node_type	*n = root;

		while (n != LEAF && n->value.first != key)	{
			if (comp(n->value.first, key))
				n = n->more;
			else
				n = n->less;
		}
		return (n);
	}

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
	}

};

}

#endif