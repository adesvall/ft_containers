/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:36:33 by adesvall          #+#    #+#             */
/*   Updated: 2022/03/16 20:19:47 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <memory>
#include <iterator>

namespace ft {

template<class T, class Alloc = std::allocator<T> >
class vector
{
	typedef T							value_type;
	typedef Alloc						allocator_type;
	typedef allocator_type::reference			reference;
	typedef allocator_type::const_reference		const_reference;
	typedef allocator_type::pointer				pointer;
	typedef allocator_type::const_pointer		const_pointer;
	typedef std::iterator<T>				iterator;
	typedef	std::const_iterator<T>			const_iterator;
	typedef std::reverse_iterator<iterator>			reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t	size_type;

public:
	explicit vector(const allocator_type& alloc = allocator_type()) : tab(NULL), A(alloc)	{
		
	}
	explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
	{
		tab = alloc.allocate(n);
		size = n;
		A = alloc;
	}

	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
 			const allocator_type& alloc = allocator_type()) {
		tab = alloc.allocate(n);
	}
	vector(const vector& v)	{}
	~vector();



	iterator begin() {
		return iterator(tab);
	}

	iterator end() {
		return iterator(tab) + size;
	}

	T* rbegin() {
		
	}

private:
	T				*tab;
	size_t			size;
	allocator_type	A;
};

}

#endif
