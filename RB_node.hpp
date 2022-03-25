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
class RB_node
{
public:
	typedef T	value_type;

private:
	value_type		value;
	color			color;
	RB_node			*less;
	RB_node			*more;
	RB_node 		*parent;

public:
	RB_node(value_type	&val) : value(val), color(RED), less(LEAF), more(LEAF), parent(NULL)	{}
	~RB_node();

	RB_node	*parent() const	{
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

	friend
	RB_node *insert(RB_node *root, RB_node *n) {
		if (root == NULL)
			return n;
		insert_recursif(n);
		n->insert_repare_arbre();

		return n->root();
	}
	RB_node *erase()	{
		if (less != LEAF && more != LEAF)	{
			RB_node *del = more->min_node();
			value = del->value;
			return del->erase();
		}
		RB_node *only_child = less;
		if (more != LEAF)
			only_child = more;
		if (color == ROUGE)	{
			if (this == parent->less)
				parent->less = only_child;
			else
				parent->more = only_child;
			if (only_child != LEAF)
				only_child->parent = parent;
			return parent->root();
		}
		else if (only_child != LEAF && only_child->color == ROUGE)	{
			only_child->color = BLACK;
		}
/*
		if (u == NULL) {
		// u is NULL therefore v is leaf
			if (v == root) {
				// v is root, making root null
				root = NULL;
			} else {
				if (uvBlack) {
					// u and v both black
					// v is leaf, fix double black at v
					fixDoubleBlack(v);
				} else {
					// u or v is red
					if (v->sibling() != NULL)
						// sibling is not null, make it red"
						v->sibling()->color = RED;
				}
		
				// delete v from the tree
				if (v->isOnLeft()) {
				parent->left = NULL;
				} else {
				parent->right = NULL;
				}
			}
			return;
		}
	
		if (v->left == NULL or v->right == NULL) {
			// v has 1 child
			if (v == root) {
				// v is root, assign the value of u to v, and delete u
				v->val = u->val;
				v->left = v->right = NULL;
				delete u;
			} else {
				// Detach v from tree and move u up
				if (v->isOnLeft()) {
					parent->left = u;
				} else {
					parent->right = u;
				}
				delete v;
				u->parent = parent;
				if (uvBlack) {
					// u and v both black, fix double black at u
					fixDoubleBlack(u);
				} else {
					// u or v red, color u black
					u->color = BLACK;
				}
			}
			return;
		}*/
		

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
	friend
	void rotation_gauche(RB_node* x) {
		RB_node* y = x->more;
		//le fils more de x devient le fils less de y
		x->more = y->less;
		if (y->less != LEAF)
			y->less->parent = x;

		y->parent = x->parent;
		//Si x est la root, y devient la root
		if (x->parent == NULL)
			x = y;

		//Sinon, on remplace x par y
		else if (x == x->parent->less)
			x->parent->less = y;
		else
			x->parent->more = y;

		//On attache x à less de y
		y->less = x;
		x->parent = y;
	}
	
	friend
	void rotation_droite(RB_node* x) {
		RB_node* y = x->less;

		x->less = y->more;
		if (y->more != LEAF)
			y->more->parent = x;

		y->parent = x->parent;
		
		if (x->parent == NULL)
			x = y;
		else if (x == x->parent->more)
			x->parent->more = y;
		else
			x->parent->less = y;

		y->more = x;
		x->parent = y;
	}

private:
	void insertion_recursif(RB_node *n) {
		// Descente récursive dans l'arbre jusqu'à atteindre une feuille
		if (n->value < value)) {
			if (less != FEUILLE)
				return less->insertion_recursif(n);
			else
				less = n;
		} 
		else	{
			if (more != FEUILLE)
				return more->insertion_recursif(n);
			else
				more = n;
		}

		n->parent = this;
		n->less = LEAF; // NIL
		n->more = LEAF; // NIL
		n->color = RED;
	}
	void insertion_repare_tree() {
		if (parent == NULL) // n est a la racine
			couleur = NOIR;
		else if (parent->couleur == NOIR) // on laisse n rouge et c'est bon
			return ;
		else if (oncle()->couleur == ROUGE)	{
			parent->couleur = NOIR;
			oncle()->couleur = NOIR;
			
			RB_node *g = grandparent();
			g->color = ROUGE;
			g->insertion_repare_tree();
		}
		else	{
			RB_node *g = grandparent();
			RB_node *n;

			if (this == g->gauche->droit) {
				rotation_gauche(parent);
				n = n->gauche;
			}
			else if (this == g->droit->gauche) {
				rotation_droite(parent);
				n = n->droit; 
			}

			struct noeud *p = n->parent;
			struct noeud *g = n->grandparent();

			if (n == p->gauche)
				rotation_droite(g);
			else
				rotation_gauche(g);
			
			p->couleur = NOIR;
			g->couleur = ROUGE;
		}
	}
/*	void fixDoubleBlack(Node *x) {
		if (x == root)
			// Reached root
			return;
	
		Node *sibling = x->sibling(), *parent = x->parent;
		if (sibling == NULL) {
			// No sibiling, double black pushed up
			fixDoubleBlack(parent);
		} else {
			if (sibling->color == RED) {
				// Sibling red
				parent->color = RED;
				sibling->color = BLACK;
				if (sibling->isOnLeft()) {
					// left case
					rightRotate(parent);
				} else {
					// right case
					leftRotate(parent);
				}
				fixDoubleBlack(x);
			} else {
				// Sibling black
				if (sibling->hasRedChild()) {
					// at least 1 red children
					if (sibling->left != NULL and sibling->left->color == RED) {
						if (sibling->isOnLeft()) {
							// left left
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							rightRotate(parent);
						} else {
							// right left
							sibling->left->color = parent->color;
							rightRotate(sibling);
							leftRotate(parent);
						}
					} else {
						if (sibling->isOnLeft()) {
						// left right
						sibling->right->color = parent->color;
						leftRotate(sibling);
						rightRotate(parent);
						} else {
						// right right
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						leftRotate(parent);
						}
					}
					parent->color = BLACK;
				} else {
					// 2 black children
					sibling->color = RED;
					if (parent->color == BLACK)
						fixDoubleBlack(parent);
					else
						parent->color = BLACK;
				}
			}
		}
	}*/
};

}

#endif