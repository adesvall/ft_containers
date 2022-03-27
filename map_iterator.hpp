#ifndef MAP_ITERATOR_HPP_HPP
# define MAP_ITERATOR_HPP_HPP

#include "iterator_traits.hpp"
#include "utils.hpp"
#include "map.hpp"
#include "RB_node.hpp"

namespace	ft
{

template <bool isConst, class T>
class	map_iterator
{
public:
	typedef	long int	difference_type;
	typedef typename choose<isConst, const T, T>::type			value_type;
	typedef	RB_node<value_type>									tree_node;
	typedef value_type*											pointer;
	typedef value_type&											reference;
	typedef bidirectional_iterator_tag							iterator_category;

	map_iterator() : node(NULL)	{}
	map_iterator(tree_node *node) : node(node)	{}
	map_iterator(const map_iterator &rit) : node(rit.node)	{}
	~map_iterator()	{}

	operator map_iterator<true, T> () const {return (map_iterator<true, T>(this->node)); }

	map_iterator	&operator=(const map_iterator	&rit)	{
		node = rit.node;
		return *this;
	}

	map_iterator	&operator++()	{
		if (node->more != LEAF)
			node = node->more->min_node();
			return *this;
		while (node->parent() && node == node->parent()->more)
			node = node->parent();
		if (node->parent() == NULL)
			node = LEAF;
		node = node->parent();
		return *this;
	}

	map_iterator operator++(int)	{
		map_iterator it(*this);
		++(*this);
		return it;
	}

	map_iterator	&operator--()	{
		if (node == LEAF)
			; // ????
		if (node->less != LEAF)
			node = node->less->max_node();
			return *this;
		while (node->parent() && node == node->parent()->less)
			node = node->parent();
		if (node->parent() == NULL)
			node = LEAF;
		node = node->parent();
		return *this;
	}

	map_iterator operator--(int)	{
		map_iterator it(*this);
		--(*this);
		return it;
	}

	reference	operator*() const	{
		return node->value;
	}

	pointer		operator->() const	{
		return &node->value;
	}

	friend
	bool	operator==(const map_iterator &lhs, const map_iterator &rhs)	{
		return lhs.node == rhs.node;
	}
	friend
	bool	operator!=(const map_iterator &lhs, const map_iterator &rhs)	{
		return lhs.node != rhs.node;
	}

	tree_node	*node()	const	{
		return node;
	}

	

private:
	tree_node	*node;
};

}

#endif
