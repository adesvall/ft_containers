#ifndef RB_TREE_HPP
# define RB_TREE_HPP

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

	RB_tree() : root(LEAF)	{}
	~RB_tree()	{}

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
		node_type *x, y;

		y = z;
		int y_original_color = y->color;
		if (z->less == LEAF) {
			x = z->more;
			transplant(z, z->more);
		} else if (z->more == LEAF) {
			x = z->less;
			transplant(z, z->less);
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
		delete z;
		if (y_original_color == 0) {
			delete_fix_tree(x);
		}
	}

	node_type	*max_node()	{
		return root->max_node();
	}
	node_type	*min_node()	{
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
		else if (x->oncle()->color == RED)	{
			x->parent->color = BLACK;
			x->oncle()->color = BLACK;
			
			node_type *g = x->grandparent();
			g->color = RED;
			insertion_fix_tree(g);
		}
		else	{
			node_type *g = x->grandparent();
			node_type *n;

			if (this == g->gauche->droit) {
				rotate_left(x->parent);
				n = n->gauche;
			}
			else if (this == g->droit->gauche) {
				rotate_right(x->parent);
				n = n->droit; 
			}

			node_type *p = n->parent;
			*g = n->grandparent();

			if (n == p->gauche)
				rotate_right(g);
			else
				rotate_left(g);
			
			p->color = BLACK;
			g->color = RED;
		}
	}

	void delete_fix_tree(node_type *x) {
		node_type *s;
		while (x->parent != NULL && x->color == 0) { // color
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					rotate_left(x->parent->rotate);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				} else {
					if (s->right->color == 0) {
						s->left->color = 0;
						s->color = 1;
						rotate_right(s);
						s = x->parent->right;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					rotate_left(x->parent);
					x = root;
				}
			} else {
				s = x->parent->left;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					rotate_right(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				} else {
					if (s->left->color == 0) {
						s->right->color = 0;
						s->color = 1;
						rotate_left(s);
						s = x->parent->left;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rotate_right(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}

};

}

#endif