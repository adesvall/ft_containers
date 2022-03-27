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

	map_iterator() : _node(NULL)	{}
	map_iterator(const tree_node *node) : _node(node)	{}
	map_iterator(const map_iterator &rit) : _node(rit._node)	{}
	~map_iterator()	{}

	operator map_iterator<true, T> () const {return (map_iterator<true, T>(this->_node)); }

	map_iterator	&operator=(const map_iterator	&rit)	{
		_node = rit._node;
		return *this;
	}

	map_iterator	&operator++()	{
		if (_node->more != LEAF)	{
			_node = _node->more->min_node();
			return *this;
		}
		while (_node->parent && _node == _node->parent->more)
			_node = _node->parent;
		if (_node->parent == NULL)
			_node = LEAF;
		_node = _node->parent;
		return *this;
	}

	map_iterator operator++(int)	{
		map_iterator it(*this);
		++(*this);
		return it;
	}

	map_iterator	&operator--()	{
		if (_node == LEAF)	{
			_node = _node->less->max_node();
			return *this;
		}
		if (_node->less != LEAF)	{
			_node = _node->less->max_node();
			return *this;
		}
		while (_node->parent && _node == _node->parent->less)
			_node = _node->parent;
		if (_node->parent == NULL)
			_node = LEAF;
		_node = _node->parent;
		return *this;
	}

	map_iterator operator--(int)	{
		map_iterator it(*this);
		--(*this);
		return it;
	}

	reference	operator*() const	{
		return _node->value;
	}

	pointer		operator->() const	{
		return &_node->value;
	}

	friend
	bool	operator==(const map_iterator &lhs, const map_iterator &rhs)	{
		return lhs._node == rhs._node;
	}
	friend
	bool	operator!=(const map_iterator &lhs, const map_iterator &rhs)	{
		return lhs._node != rhs._node;
	}

	tree_node	*node()	const	{
		return _node;
	}

private:
	tree_node	*_node;
};

}

#endif
