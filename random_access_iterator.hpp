#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "utils.hpp"

namespace	ft
{

template <bool isConst, class T>
class	random_access_iterator
{
public:
	typedef	long int	difference_type;
	typedef typename choose<isConst, const T, T>::type			value_type;
	typedef value_type*											pointer;
	typedef value_type&											reference;
	typedef random_access_iterator_tag							iterator_category;
	// typedef random_access_iterator<!isConst, T>					other_type;

	random_access_iterator() : ptr(NULL)	{}
	random_access_iterator(value_type *ptr) : ptr(ptr)	{}
	random_access_iterator(const random_access_iterator &rit) : ptr(rit.ptr)	{}
	~random_access_iterator()	{}

	operator random_access_iterator<true, T> () const {return (random_access_iterator<true, T>(this->ptr)); }
	// random_access_iterator(typename enable_if<!isConst, random_access_iterator<false, T> >::type &rit) : ptr(rit.ptr)	{}

	random_access_iterator	&operator=(const random_access_iterator	&rit)	{
		ptr = rit.ptr;
		return *this;
	}

	random_access_iterator	&operator++()	{
		ptr++;
		return *this;
	}

	random_access_iterator operator++(int)	{
		random_access_iterator it(*this);
		ptr++;
		return it;
	}

	random_access_iterator	&operator--()	{
		ptr--;
		return *this;
	}

	random_access_iterator operator--(int)	{
		random_access_iterator it(*this);
		ptr--;
		return it;
	}

	reference	operator*() const	{
		return *ptr;
	}

	pointer		operator->() const	{
		return ptr;
	}

	random_access_iterator	operator+(int n) const	{
		return random_access_iterator(ptr + n);
	}

	random_access_iterator	operator-(int n) const	{
		return random_access_iterator(ptr - n);
	}

	random_access_iterator	&operator+=(int n)	{
		ptr += n;
		return *this;
	}
	random_access_iterator	&operator-=(int n)	{
		ptr -= n;
		return *this;
	}

	reference	operator[](int n) const	{
		return ptr[n];
	}

	friend
	random_access_iterator	operator+(int n, random_access_iterator &rit)	{
		return rit + n;
	}

	difference_type		operator-(const random_access_iterator &rit) const	{
		return ptr - &(*rit);
	}

	friend
	bool	operator==(const random_access_iterator &lhs, const random_access_iterator &rhs)	{
		return lhs.ptr == rhs.ptr;
	}
	friend
	bool	operator!=(const random_access_iterator &lhs, const random_access_iterator &rhs)	{
		return lhs.ptr != rhs.ptr;
	}
	friend
	bool	operator<(const random_access_iterator &lhs, const random_access_iterator &rhs)	{
		return lhs.ptr < rhs.ptr;
	}
	friend
	bool	operator<=(const random_access_iterator &lhs, const random_access_iterator &rhs)	{
		return lhs.ptr <= rhs.ptr;
	}
	friend
	bool	operator>(const random_access_iterator &lhs, const random_access_iterator &rhs)	{
		return lhs.ptr > rhs.ptr;
	}
	friend
	bool	operator>=(const random_access_iterator &lhs, const random_access_iterator &rhs)	{
		return lhs.ptr >= rhs.ptr;
	}

	friend
	difference_type	distance(const random_access_iterator& first, const random_access_iterator& last)	{
		return &(*last) - &(*first);
	}

private:
	pointer	ptr;
};

}

#endif
