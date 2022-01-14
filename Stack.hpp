/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 23:46:38 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/14 00:36:25 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

#include <stack>

namespace ft {
// template <class T, class Container = Cell<T> > class stack;

	template<class T,  class Container = Cell<T>>
	class Stack
	{
	private:
		size_t		size;
		Container* 	head;

	public:
		Stack();
		~Stack();

		bool		empty();
		size_t		size();
		void		push(T truc);
		T			pop();
	
	};

	Stack::Stack() : head(NULL), size(0)
	{}

	Stack::~Stack()
	{}

	
	template<class T>
	class Cell 
	{
	private:
		T value;
		Cell *next;

	public:
		Cell();
		~Cell();
		empty
	
	Cell::Cell() : next(NULL)
	{
		
	}

	Cell::~Cell()
	{
		
	}
	}

}

#endif
