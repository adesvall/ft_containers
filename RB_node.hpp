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
	RB_node(value_type	&val) : value(val), parent(NULL)	{}
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

	RB_node *insert(RB_node *n) {
		insert_recursif(n);
		n->insert_repare_arbre();
	
		while (n->parent != NULL)
			n = n->parent;
		return n;
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
			if (less != FEUILLE) {
				less->insertion_recursif(n);
				return;
			}
			else
				less = n;
		} 
		else	{
			if (more != FEUILLE) {
				more->insertion_recursif(n);
				return;
			}
			else
				more = n;
		}

		n->parent = this;
		n->less = FEUILLE; // NIL
		n->more = FEUILLE; // NIL
		n->color = ROUGE;
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

};

}

#endif