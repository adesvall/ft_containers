#ifndef RB_TREE_HPP
# define RB_TREE_HPP

	#include <iostream>

#include <string>
#include "RB_node.hpp"

namespace	ft
{

template <typename T>
struct RB_tree
{
public:
	typedef T							value_type;
	typedef	RB_node<value_type>			node_type;

	node_type		*root;
	node_type		*LEAF;

	RB_tree()	{
		LEAF = new node_type(NULL, *this);
		LEAF->color = BLACK;
		LEAF->less = NULL;
		LEAF->more = NULL;
		LEAF->LEAF = LEAF;
		root = LEAF;
	}
	~RB_tree()	{
		delete LEAF;
	}

	void	insert(node_type *parent, node_type *&side_ref, node_type *n) {
		side_ref = n;

		n->parent = parent;
		n->less = LEAF; // NIL
		n->more = LEAF; // NIL
		n->color = RED;
		insert_fix_tree(n);

		root = n->root();
	}

	void delete_node(node_type *z) {
		// printMap();
		node_type *x, *y;

		y = z;
		int y_original_color = y->color;
		if (z->less == LEAF) {
			x = z->more;
			transplant(z, x);
		} else if (z->more == LEAF) {
			x = z->less;
			transplant(z, x);
		} else {
			y = z->more->min_node();
			y_original_color = y->color;
			x = y->more;
			if (y->parent == z) {
				x->parent = y;
			} else {
				transplant(y, y->more);
				y->more = z->more;
				y->more->parent = y;
			}
			transplant(z, y);
			y->less = z->less;
			y->less->parent = y;
			y->color = z->color;
		}
		if (y_original_color == BLACK) {
			delete_fix_tree(x);
		}
	}

	node_type	*max_node()	const {
		return root->max_node();
	}

	node_type	*min_node()	const {
		return root->min_node();
	}


private:

	void rotate_left(node_type* x) {
		node_type* y = x->more;
		//le fils more de x devient le fils less de y
		x->more = y->less;
		if (y->less != LEAF)
			y->less->parent = x;

		transplant(x, y);

		//On attache x à less de y
		y->less = x;
		x->parent = y;
	}

	void rotate_right(node_type* x) {
		node_type* y = x->less;

		x->less = y->more;
		if (y->more != LEAF)
			y->more->parent = x;

		transplant(x, y);

		y->more = x;
		x->parent = y;
	}

	void transplant(node_type *u, node_type *v) {
		if (u->parent == NULL) {
			root = v;
		}
		else if (u == u->parent->less) {
			u->parent->less = v;
		}
		else {
			u->parent->more = v;
		}
		v->parent = u->parent;
	}

	void insert_fix_tree(node_type *x) {
		if (x->parent == NULL) // n est a la racine
			x->color = BLACK;
		else if (x->parent->color == BLACK) // on laisse n rouge et c'est bon
			return ;
		else if (x->oncle() != LEAF && x->oncle()->color == RED)	{
			x->parent->color = BLACK;
			x->oncle()->color = BLACK;
			
			node_type *g = x->grandparent();
			g->color = RED;
			insert_fix_tree(g);
		}
		else	{
			node_type *g = x->grandparent();

			if (g->less != LEAF && x == g->less->more) {
				rotate_left(x->parent);
				x = x->less;
			}
			else if (g->more != LEAF && x == g->more->less) {
				rotate_right(x->parent);
				x = x->more; 
			}

			node_type *p = x->parent;
			node_type *gr = x->grandparent();

			if (x == p->less)
				rotate_right(gr);
			else
				rotate_left(gr);
			
			p->color = BLACK;
			gr->color = RED;
		}
	}

	void delete_fix_tree(node_type *x) {
		node_type *s;
		while (x != root && x->color == BLACK) {
			if (x == x->parent->less) {
				s = x->parent->more;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					rotate_left(x->parent);
					s = x->parent->more;
				}

				if (s->less->color == BLACK && s->more->color == BLACK) {
					s->color = RED;
					x = x->parent;
				} else {
					if (s->more->color == BLACK) {
						s->less->color = BLACK;
						s->color = RED;
						rotate_right(s);
						s = x->parent->more;
					}

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->more->color = BLACK;
					rotate_left(x->parent);
					x = root;
				}
			} else {
				s = x->parent->less;
				if (s->color == RED) {
					s->color = BLACK;
					x->parent->color = RED;
					rotate_right(x->parent);
					s = x->parent->less;
				}

				if (s->more->color == BLACK && s->more->color == BLACK) {
					s->color = RED;
					x = x->parent;
				} else {
					if (s->less->color == BLACK) {
						s->more->color = BLACK;
						s->color = RED;
						rotate_left(s);
						s = x->parent->less;
					}

					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->less->color = BLACK;
					rotate_right(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}

};

}

#endif