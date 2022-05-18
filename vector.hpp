/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:36:33 by adesvall          #+#    #+#             */
/*   Updated: 2022/05/18 22:29:44 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <memory>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

#include <iterator>
#include "utils.hpp"
#include <limits>

namespace ft {

template<class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef random_access_iterator<false, T>			iterator;
	typedef	random_access_iterator<true, T>				const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t	size_type;

	explicit vector(const allocator_type& alloc = allocator_type())
	: tab(NULL), _size(0), _capacity(0), A(alloc)
	{
		// tab = A.allocate(1);	
	}
	
	explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
	{
		A = alloc;
		tab = A.allocate(n);
		_capacity = n;
		_size = 0;
		assign(n, val);
	}

	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
 			const allocator_type& alloc = allocator_type()) {
		A = alloc;
		tab = NULL;
		_capacity = 0;
		_size = 0;
		assign(first, last);
	}
	vector(const vector& v)	{
		_size = v._size;
		_capacity = v._capacity;
		A = v.A;
		tab = A.allocate(v._capacity);
		for (size_type i = 0; i < _size; i++)	{
			A.construct(&tab[i], v.tab[i]);
		}
	}
	~vector()	{
		for (size_type i = 0; i < _size; i++)	{
			A.destroy(&tab[i]);
		}
		A.deallocate(tab, _capacity);
	}

	vector	&operator=(const vector& v)	{
		reserve(v.size());
		
		destroy_content();
		for (size_type i = 0; i < v._size; i++)	{
			A.construct(&tab[i], v.tab[i]);
		}
		_size = v._size;
		return *this;
	}



// ITERATOR
	iterator begin() {
		return iterator(tab);
	}
	const_iterator begin() const	{
		return const_iterator(tab);
	}

	iterator end() {
		return iterator(tab) + _size;
	}
	const_iterator end() const	{
		return (const_iterator(tab) + _size);
	}

	reverse_iterator rbegin() {
		return reverse_iterator(tab + _size);
	}
	const_reverse_iterator rbegin() const	{
		return const_reverse_iterator(tab + _size);
	}

	reverse_iterator rend() {
		return reverse_iterator(tab);
	}
	const_reverse_iterator rend() const	{
		return const_reverse_iterator(tab);
	}

// CAPACITY
	size_type	size()	const	{
		return _size;
	}

	size_type	max_size() const	{
		try	{
			return A.max_size();
		}
		catch(const std::exception& e)	{
			std::cerr << e.what() << '\n';
		}
		return -1;
	}
	
	void	resize (size_type n, value_type val = value_type())	{
		if (n <= _size)	{
			destroy_content(n);
			return;
		}
		reserve(n);
		for (size_type i = _size; i < n; i++)
			A.construct(&tab[i], val);
		_size = n;
	}

	size_type	capacity() const	{
		return _capacity;
	}

	bool	empty() const	{
		return _size == 0;
	}

	void	reserve(size_type n)	{
		if (n <= _capacity)
			return ;
		if (tab == NULL)
		{
			tab = A.allocate(n);
			_capacity = n;
			return ;
		}
		size_type new_capacity = _capacity + 1;
		while (new_capacity < n)
			new_capacity *= 2;
		n = new_capacity;
		value_type* new_tab = A.allocate(n);
		for (size_type i = 0; i < _size; i++)	{
			A.construct(&new_tab[i], tab[i]);
			A.destroy(&tab[i]);
		}
		A.deallocate(tab, _capacity);
		_capacity = n;
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
		if (i >= _size)
			throw std::out_of_range("Error : argument out of range\n");
		return tab[i];}
	const_reference	at(size_type i) const	{
		if (i >= _size)
			throw std::out_of_range("Error : argument out of range\n");
		return tab[i];}
	
	reference 		front()	{
		return tab[0];}
	const_reference front() const	{
		return tab[0];}
	
	reference 		back()	{
		return tab[_size - 1];}
	const_reference back() const	{
		return tab[_size - 1];}

// MODIFIERS
	template <class InputIterator>
	void assign (typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last)
	// void assign (InputIterator first, InputIterator last)
	{
		destroy_content();
		reserve(ft::distance(first, last));
		int i = 0;
		for (; first != last; ++first)	{
			A.construct(&tab[i], *first);
			i++;
		}
		_size = i;
	}
	void assign (size_type n, const value_type& val)	{
		destroy_content();
		reserve(n);
		for (size_type i = 0; i < n; i++)
			A.construct(&tab[i], val);
		_size = n;
	}

	void	push_back(const value_type& val)	{
		reserve(_size + 1);
		A.construct(&tab[_size], val);
		_size++;
	}

	void	pop_back()	{
		_size--;
		A.destroy(&tab[_size]);
	}

	iterator insert (iterator position, const value_type& val)	{
		difference_type i = ft::distance(begin(), position);
		reserve(_size + 1);
		position = begin() + i;
		iterator it = end();
		for (; it != position; it--)
		{
			A.construct(&(*it), *(it - 1));
			// std::cout << *it;
			A.destroy(&(*(it - 1)));
		}
		A.construct(&(*it), val);
		_size++;
		return position;
	}

    void insert (iterator position, size_type n, const value_type& val)	{
		if (n == 0)
			return ;
		difference_type i = ft::distance(begin(), position);
		reserve(_size + n);
		position = begin() + i;
		for (iterator it = end() - 1; it != position - 1; it--)
		{
			A.construct(&(*(it + n)), *it);
			A.destroy(&(*it));
		}
		for (size_type i = 0; i < n; i++)	{
			A.construct(&(*position), val);
			position++;
		}
		_size += n;
	}
	
	template <class InputIterator>
    void insert (iterator position, typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first,
									InputIterator last)	{
		typename InputIterator::difference_type n = ft::distance(first, last);
		difference_type i = distance(begin(), position);
		reserve(_size + n);
		position = begin() + i;
		for (iterator it = end() - 1; it != position - 1; it--)
		{
			A.construct(&(*(it + n)), *it);
			A.destroy(&(*it));
		}
		for (;first != last; ++first)
			A.construct(&(*position++), *first);
		_size += n;
	}

	iterator erase (iterator position)	{
		iterator ret = position;
		A.destroy(&(*position));
		iterator end = this->end() - 1;
		for (; position != end; position++)	{
			A.construct(&(*position), *(position + 1));
			A.destroy(&(*(position + 1)));
		}
		_size--;
		return ret;
	}
	iterator erase (iterator first, iterator last)	{
		iterator ret = first;
		iterator tmp = first;
		difference_type i = distance(first, last);

		for (; tmp != last; tmp++)
			A.destroy(&(*tmp));
		for (; tmp != end(); tmp++)	{
			A.construct(&(*first), *tmp);
			A.destroy(&(*tmp));
			first++;
		}
		_size -= i;
		return ret;
	}

	void swap(vector& x)	{
		ft::swap(tab, x.tab);
		ft::swap(_size, x._size);
		ft::swap(_capacity, x._capacity);
		ft::swap(A, x.A);
	}
	
	void	clear()	{
		destroy_content();
	}

// ALLOCATOR
	allocator_type get_allocator() const	{
		return A;
	}

// REL. OPERATORS
	friend
	bool operator== (const vector& lhs, const vector& rhs)	{
		if (lhs._size != rhs._size)
			return false;
		for (size_type i = 0; i < rhs._size; i++)
			if (lhs.tab[i] != rhs.tab[i])
				return false;
		return true;
	}

	friend
	bool operator!= (const vector& lhs, const vector& rhs)	{
		return !(lhs == rhs);
	}
	
	friend
	bool operator<  (const vector& lhs, const vector& rhs)	{
		for (size_type i = 0; i < rhs._size; i++)
		{
			if (i == lhs._size)
				return true;
			if (lhs.tab[i] != rhs.tab[i])
				return lhs.tab[i] < rhs.tab[i];
		}
		return false;
	}

	friend
	bool operator<= (const vector& lhs, const vector& rhs)	{
		return !(rhs < lhs);
	}

	friend
	bool operator>  (const vector& lhs, const vector& rhs)	{
		return rhs < lhs;
	}

	friend
	bool operator>= (const vector& lhs, const vector& rhs)	{
		return !(lhs < rhs);
	}

	friend
	void swap (vector& x, vector& y)	{
		x.swap(y);
	}

private:
	value_type		*tab;
	size_type		_size;
	size_type		_capacity;
	allocator_type	A;

	void	copy_content(){}

	void	destroy_content(int begin = 0)	{
		for (size_type i = begin; i < _size; i++)
			A.destroy(&tab[i]);
		_size = begin;
	}
};

}

#endif
