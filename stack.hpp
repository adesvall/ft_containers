/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 23:46:38 by adesvall          #+#    #+#             */
/*   Updated: 2022/03/23 23:52:32 by adesvall         ###   ########.fr       */
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

	explicit stack (const container_type& ctnr = container_type())	: head(ctnr)	{}
	virtual ~stack()	{}

	bool		empty()	const	{
		return head.empty();
	}

	size_type	size()	const	{
		return head.size();
	}

	void		push(const value_type& val)	{
		return head.push_back(val);
	}

	void		pop()	{
		head.pop_back();
	}
	
	value_type& top()	{
		return head.back();
	}
	const value_type& top() const	{
		return head.back();
	}

	friend
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.head == rhs.head;
	}
	friend
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.head != rhs.head;
	}
	friend
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.head < rhs.head;
	}
	friend
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.head <= rhs.head;
	}
	friend
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.head > rhs.head;
	}
	friend
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{
		return lhs.head >= rhs.head;
	}

protected:
	container_type 	head;
};

}

#endif
