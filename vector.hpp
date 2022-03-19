/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:36:33 by adesvall          #+#    #+#             */
/*   Updated: 2022/03/19 18:59:46 by adesvall         ###   ########.fr       */
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
public:
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

	explicit vector(const allocator_type& alloc = allocator_type())
	: tab(NULL), A(alloc)	{
		
	}
	explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
	{
		tab = alloc.allocate(n);
		size = n;
		capacity = n;
		A = alloc;
	}

	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
 			const allocator_type& alloc = allocator_type()) {
		tab = alloc.allocate(n);
	}
	vector(const vector& v)	{
		//
	}
	~vector()	{
		for (int i = 0; i < size; i++)	{
			A.destroy(&tab[i]);
		}
		A.deallocate(tab, capacity);
	}


// ITERATOR
	iterator begin() {
		return iterator(tab);
	}
	const_iterator begin() const	{
		return const_iterator(tab);
	}

	iterator end() {
		return iterator(tab) + size;
	}
	const_iterator end() const	{
		return const_iterator(tab) + size;
	}

	reverse_iterator rbegin() {
		return reverse_iterator(tab);
	}
	const_reverse_iterator rbegin() {
		return const_reverse_iterator(tab);
	}

	reverse_iterator rend() {
		return reverse_iterator(tab) + size;
	}
	const_reverse_iterator rend() {
		return const_reverse_iterator(tab) + size;
	}

// CAPACITY
	size_type	size()	const	{
		return size;
	}

	size_type	max_size() const	{
		size_type t();
		try	{
			return A.max_size();
		}
		catch(const std::exception& e)	{
			std::cerr << e.what() << '\n';
		}
		return -1;
	}
	
	void	resize (size_type n, value_type val = value_type())	{
		if (n <= size)	{
			for (int i = n; i < size; i++)
				A.destroy(&tab[i]);
			return;
		}
		reserve(n);
		for (int i = size; i < n; i++)
			A.construct(&tab[i], val);
		size = n;
	}

	size_type	capacity() const	{
		return capacity;
	}

	bool	empty() const	{
		return size == 0;
	}

	void	reserve(size_type n)	{
		if (n <= capacity)
			return ;
		new_capacity = capacity;
		while (new_capacity <= n)
			new_capacity *= 2;
		n = new_capacity;
		value_type* new_tab = A.allocate(n);
		for (int i = 0; i < size; i++)	{
			A.construct(&new_tab[i], tab[i]);
			// truc[i] = tab[i];
			A.destroy(&tab[i]);
		}
		A.deallocate(tab, capacity);
		capacity = n;
		tab = new_tab;
	}

// ELEMENT ACCESS
	reference	operator[](size_type i)	{
		return tab[i];
	}
	const_reference	operator[](size_type i) const	{
		return tab[i];
	}

	reference		at(size_type i)	{
		if (i >= size)
			throw std::out_of_range();
		return tab[i];}
	const_reference	at(size_type i) const	{
		if (i >= size)
			throw std::out_of_range();
		return tab[i];}
	
	reference 		front()	{
		return tab[0];}
	const_reference front() const	{
		return tab[0];}
	
	reference 		back()	{
		return tab[size - 1];}
	const_reference back() const	{
		return tab[size - 1];}

// MODIFIERS
	template <class InputIterator>
	void assign (InputIterator first, InputIterator last)	{
		for (int i = 0; i < size; i++)
			A.destroy(&tab[i]);
		size = 0;
		reserve(std::distance(first, last));
		for (int i = 0; first != last; ++first && ++i)
			A.construct(&tab[i], *first)
		size = i;
	}
	void assign (size_type n, const value_type& val)	{
		for (int i = 0; i < size; i++)
			A.destroy(&tab[i]);
		reserve(n);
		for (int i = 0; i < n; i++)
			A.construct(&tab[i], val);
		size = n;
	}

	void	push_back(const value_type& val)	{
		reserve(size + 1);
		A.construct(&tab[size], val);
		size++;
	}

	void	pop_back()	{
		size--;
		A.destroy(&tab[size]);
	}

	iterator insert (iterator position, const value_type& val)	{
		;
	}

    void insert (iterator position, size_type n, const value_type& val)	{
		;
	}
	
	template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last)	{
		;
	}

	

private:
	value_type		*tab;
	size_type		size;
	size_type		capacity;
	allocator_type	A;

	void	destroy_content(int begin = 0, int end = size)	{
		for (int i = begin; i < end; i++)
			A.destroy(&tab[i]);
	}
};

}

#endif
