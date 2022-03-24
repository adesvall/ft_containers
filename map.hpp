#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "RB_node.hpp"
# include "pair.hpp"

namespace	ft
{

template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator<pair<const Key,T> >    // map::allocator_type
           >
class map
{
public:
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef pair<const key_type,mapped_type>			value_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef 			iterator;
	typedef				const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t	size_type;

	explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type());
			  
	template <class InputIterator>
	map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type());
		
	map (const map& x);
	virtual ~map();

	map& operator= (const map& x);

private:
	size_type		_size;
	key_compare		comp;
	allocator_type	A;
	RB_node			*root;
	// RB_node			leaf;
};

}

#endif