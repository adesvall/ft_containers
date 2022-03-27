#ifndef RB_NODE_HPP
# define RB_NODE_HPP

#include "pair.hpp"

#define LEAF NULL

namespace ft
{

enum	color	{
	RED,
	BLACK,
};

template <typename T>
struct RB_node
{
	typedef T	value_type;

	value_type		value;
	color			color;
	RB_node			*less;
	RB_node			*more;
	RB_node 		*parent;

	RB_node(value_type	&val) : value(val), color(RED), less(LEAF), more(LEAF), parent(NULL)	{}
	~RB_node();

	RB_node	*&parent()	{
		return parent;
	}
	RB_node	*grandparent() const	{
		if (parent == NULL)
			return NULL;
		return parent->parent;
	}
	RB_node	*frere() const	{
		if (parent == NULL)
			return NULL;
		if (this == parent->less)
			return parent->more;
		else
			return parent->less;
	}
	RB_node	*oncle() const {
		RB_node	*g = grandparent();
		if (g == NULL)
			return NULL;
		return parent->frere();
	}
	
	RB_node	*max_node()	const {
		if (more != LEAF)
			return more->max_node();
		return this;
	}
	RB_node	*min_node()	const {
		if (less != LEAF)
			return less->min_node();
		return this;
	}
	RB_node	*root()	const {
		if (parent == NULL)
			return this;
		return parent->root();
	}

private:
};

}

#endif