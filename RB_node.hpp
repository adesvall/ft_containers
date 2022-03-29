#ifndef RB_NODE_HPP
# define RB_NODE_HPP

# include "pair.hpp"
# include "RB_tree.hpp"

namespace ft
{
template <typename T>
struct RB_tree;

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
	RB_node			**root_p;
	RB_node			*LEAF;

	RB_node(const value_type	&val, RB_tree<T> &tree)
	: value(val), color(RED), less(tree.LEAF), more(tree.LEAF), parent(NULL), root_p(&tree.root), LEAF(tree.LEAF)	{}
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
	
	RB_node	*successor()	{
		if (this == LEAF)
			return (*root_p)->min_node();
		if (more != LEAF)	
			return more->min_node();
		RB_node *x = this;
		while (x->parent && x == x->parent->more)
			x = x->parent;
		if (x->parent == NULL)
			return x->LEAF;
		else
			return x->parent;
	}

	RB_node	*predecessor()	{
		if (this == LEAF)
			return (*root_p)->max_node();
		if (less != LEAF)	
			return less->max_node();
		RB_node *x = this;
		while (x->parent && x == x->parent->less)
			x = x->parent;
		if (x->parent == NULL)
			return x->LEAF;
		else
			return x->parent;
	}

	RB_node	*max_node() {
		if (this == LEAF)
			return this;
		if (more != LEAF)
			return more->max_node();
		return this;
	}
	RB_node	*min_node() {
		if (this == LEAF)
			return this;
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