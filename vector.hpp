/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:36:33 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/14 01:20:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <memory>
#include <iterator>

namespace ft {

template<class T, class Alloc = std::allocator<T>>
class vector
{

    typedef typename std::iterator<std::iterator::> forward_iterator;
    typedef typename std::iterator<std::> forward_iterator;

private:
	T		*data;
    size_t	size;
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
};

vector::vector() : data(NULL)
{}

vector::~vector()
{
}

}

#endif
