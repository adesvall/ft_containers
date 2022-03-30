/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 23:46:38 by adesvall          #+#    #+#             */
/*   Updated: 2022/03/30 18:43:27 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T> >

class stack
{
public:
	typedef T			value_type;
	typedef Container	container_type;
	typedef size_t		size_type;

	explicit stack (const container_type& ctnr = container_type())	: c(ctnr)	{}
	virtual ~stack()	{}

	bool		empty()	const	{
		return c.empty();
	}

	size_type	size()	const	{
		return c.size();
	}

	void		push(const value_type& val)	{
		return c.push_back(val);
	}

	void		pop()	{
		c.pop_back();
	}
	
	value_type& top()	{
		return c.back();
	}
	const value_type& top() const	{
		return c.back();
	}

	friend
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.c == rhs.c;
	}
	friend
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.c != rhs.c;
	}
	friend
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.c < rhs.c;
	}
	friend
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.c <= rhs.c;
	}
	friend
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.c > rhs.c;
	}
	friend
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.c >= rhs.c;
	}

protected:
	container_type 	c;
};

}

#endif
