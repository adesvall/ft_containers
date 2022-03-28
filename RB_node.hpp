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

	RB_node(const value_type	&val) : value(val), color(RED), less(LEAF), more(LEAF), parent(NULL)	{}
	~RB_node()	{}

	//operator RB_node<const T> ()	{return RB_node<const T>()}

	RB_node	*grandparent()	{
		if (parent == NULL)
			return NULL;
		return parent->parent;
	}
	RB_node	*frere()	{
		if (parent == NULL)
			return NULL;
		if (this == parent->less)
			return parent->more;
		else
			return parent->less;
	}
	RB_node	*oncle() {
		RB_node	*g = grandparent();
		if (g == NULL)
			return NULL;
		return parent->frere();
	}
	
	RB_node	*max_node() {
		if (more != LEAF)
			return more->max_node();
		return this;
	}
	RB_node	*min_node() {
		if (less != LEAF)
			return less->min_node();
		return this;
	}
	RB_node	*root()	{
		if (parent == NULL)
			return this;
		return parent->root();
	}

private:
};

}

#endif