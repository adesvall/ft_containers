/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:36:33 by adesvall          #+#    #+#             */
/*   Updated: 2022/03/21 05:07:40 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <memory>
#include <iterator>
#include "random_access_iterator.hpp"
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
	typedef random_access_iterator<false, T>					iterator;
	typedef	random_access_iterator<true, T>				const_iterator;
	typedef std::reverse_iterator<iterator>				reverse_iterator;
	typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t	size_type;

	explicit vector(const allocator_type& alloc = allocator_type())
	: tab(NULL), A(alloc), _size(0), _capacity(1)
	{
		tab = alloc.allocate(1);	
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
		tab = A.allocate(1);
		_capacity = 1;
		_size = 0;
		assign(first, last);
	}
	vector(const vector& v)	{
		_size = v._size;
		_capacity = v._capacity;
		A = v.A;
		tab = A.allocate(v._capacity);
		for (int i = 0; i < _size; i++)	{
			A.construct(&tab[i], v.tab[i]);
		}
	}
	~vector()	{
		for (int i = 0; i < _size; i++)	{
			A.destroy(&tab[i]);
		}
		A.deallocate(tab, _capacity);
	}

	vector	operator=(const vector& v)	{
		destroy_content();
		A.deallocate(tab, _capacity);
		A = v.A;
		_size = v._size;
		_capacity = v._capacity;
		tab = A.allocate(v._capacity);
		for (int i = 0; i < _size; i++)	{
			A.construct(&tab[i], v.tab[i]);
		}
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
		return const_iterator(tab) + _size;
	}

	reverse_iterator rbegin() {
		return reverse_iterator(tab);
	}
	const_reverse_iterator rbegin() const	{
		return const_reverse_iterator(tab);
	}

	reverse_iterator rend() {
		return reverse_iterator(tab + _size);
	}
	const_reverse_iterator rend() const	{
		return const_reverse_iterator(tab + _size);
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
		size_type new_capacity = _capacity;
		while (new_capacity <= n)
			new_capacity *= 2;
		n = new_capacity;
		value_type* new_tab = A.allocate(n);
		for (int i = 0; i < _size; i++)	{
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
	// void assign (typename enable_if<!std::numeric_limits<InputIterator>::is_integer,
	void assign (InputIterator first, InputIterator last)	{
		destroy_content();
		reserve(std::distance(first, last));
		int i = 0;
		for (; first != last; ++first && ++i)
			A.construct(&tab[i], *first);
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
		reserve(_size + 1);
		iterator it;
		for (it = rend(); it != position; it++)
		{
			A.construct(it, *(it + 1));
			A.destruct(it);
		}
		A.construct(it, val);
		_size++;
		return position;
	}

    void insert (iterator position, size_type n, const value_type& val)	{
		difference_type i = std::distance(begin(), position);
		reserve(_size + n);
		position = begin() + i;
		for (iterator it = end() + n - 1; it != position + n - 1; it--)
		{
			A.construct(it, *(it + 1));
			A.destruct(it);
		}
		for (size_type i = 0; i < n; i++)
			A.construct(position++, val);
		_size += n;
	}
	
	template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last)	{
		typename InputIterator::difference_type n = std::distance(first, last);
		difference_type i = std::distance(begin(), position);
		reserve(_size + n);
		position = begin() + i;
		for (iterator it = end() + n - 1; it != position + n - 1; it--)
		{
			A.construct(it, *(it + 1));
			A.destruct(it);
		}
		for (;first != last; ++first)
			A.construct(position++, *first);
		_size += n;
	}

	iterator erase (iterator position)	{
		A.destruct(position);
		for (; position != end(); position++)	{
			A.construct(position, *(position + 1));
			A.destruct(position + 1);
		}
		_size--;
		return position;
	}
	iterator erase (iterator first, iterator last)	{
		iterator ret = first;
		iterator tmp = first;
		difference_type i = std::distance(first, last);

		for (; tmp != last; tmp++)
			A.destruct(tmp);
		for (; tmp != end(); tmp++)	{
			A.construct(first, *tmp);
			A.destruct(tmp);
			first++;
		}
		_size -= i;
		return ret;
	}

	void swap(vector& x)	{
		swap(tab, x.tab);
		swap(_size, x._size);
		swap(_capacity, x._capacity);
		swap(A, x.A);
	}
	
	void	clear()	{
		destroy_content();
	}

// ALLOCATOR
	allocator_type get_allocator() const	{
		return A;
	}

// REL. OPERATORS
	template <class T2, class Alloc2>
	friend
	bool operator== (const vector<T2,Alloc2>& lhs, const vector<T2,Alloc2>& rhs)	{
		if (lhs._size != rhs._size)
			return false;
		for (int i = 0; i < rhs._size; i++)
			if (lhs.tab[i] != rhs.tab[i])
				return false;
		return true;
	}

	template <class T2, class Alloc2>
	friend
	bool operator!= (const vector<T2,Alloc2>& lhs, const vector<T2,Alloc2>& rhs)	{
		return !(lhs == rhs);
	}

	template <class T2, class Alloc2>
	friend
	bool operator<  (const vector<T2,Alloc2>& lhs, const vector<T2,Alloc2>& rhs)	{
		if (lhs._size != rhs._size)
			return lhs.size < rhs._size;
		for (int i = 0; i < rhs._size; i++)
			if (lhs.tab[i] != rhs.tab[i])
				return lhs.tab[i] < rhs.tab[i];
		return false;
	}

	template <class T2, class Alloc2>
	friend
	bool operator<= (const vector<T2,Alloc2>& lhs, const vector<T2,Alloc2>& rhs)	{
		return !(rhs < lhs);
	}

	template <class T2, class Alloc2>
	friend
	bool operator>  (const vector<T2,Alloc2>& lhs, const vector<T2,Alloc2>& rhs)	{
		return rhs < lhs;
	}

	template <class T2, class Alloc2>
	friend
	bool operator>= (const vector<T2,Alloc2>& lhs, const vector<T2,Alloc2>& rhs)	{
		return !(lhs < rhs);
	}

	template <class T2, class Alloc2>
	friend
	void swap (vector<T2,Alloc2>& x, vector<T2,Alloc2>& y)	{
		x.swap(y);
	}

private:
	value_type		*tab;
	size_type		_size;
	size_type		_capacity;
	allocator_type	A;

	void	copy_content(){}

	void	destroy_content(int begin = 0)	{
		for (int i = begin; i < _size; i++)
			A.destroy(&tab[i]);
		_size = 0;
	}

	template <typename T2>
	void	swap(T2& a, T2& b)	{
		T2 tmp;

		tmp = a;
		a = b;
		b = tmp;
	}
};

}

#endif
