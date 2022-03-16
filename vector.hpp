/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:36:33 by adesvall          #+#    #+#             */
/*   Updated: 2022/03/16 17:56:07 by adesvall         ###   ########.fr       */
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
	typedef 
	typedef typename std::iterator<std::iterator::> forward_iterator;
	typedef typename std::iterator<std::> forward_iterator;

public:
	vector(/* args */);
	~vector();

	forward_iterator begin() {
		return iterator<;
	}

	backward_iterator end() {
		return data + size;
	}

	T* rbegin() {
		
	}

private:
	T		*data;
	size_t	size;
};

vector::vector() : data(NULL)
{}

vector::~vector()
{
}

}

#endif
