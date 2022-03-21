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
	typedef	size_t	difference_type;
	typedef typename choose<isConst, const T, T>::type			value_type;
	typedef typename choose<isConst, const T, T>::type*			pointer;
	typedef typename choose<isConst, const T, T>::type&			reference;
	typedef random_access_iterator_tag							iterator_category;
	typedef random_access_iterator<!isConst, T>					other_type;

	random_access_iterator() : ptr(NULL)	{}
	random_access_iterator(T *ptr) : ptr(ptr)	{}
	random_access_iterator(random_access_iterator &rit) : ptr(rit.ptr)	{}
	~random_access_iterator()	{}

	operator random_access_iterator<true, T> () const {return (random_access_iterator<true, T>(this->ptr)); }
	// random_access_iterator(typename enable_if<!isConst, random_access_iterator<false, T> >::type &rit) : ptr(rit.ptr)	{}

	random_access_iterator	&operator=(random_access_iterator	&rit)	{
		ptr = rit.ptr;
		return *this;
	}

	random_access_iterator	&operator++()	{
		ptr++;
		return *this;
	}

	random_access_iterator &operator++(int)	{
		random_access_iterator it(*this);
		ptr++;
		return it;
	}

	random_access_iterator	&operator--()	{
		ptr--;
		return *this;
	}

	random_access_iterator &operator--(int)	{
		random_access_iterator it(*this);
		ptr--;
		return it;
	}

	bool	operator==(random_access_iterator &rit)	{
		return ptr == rit;
	}

	bool	operator!=(random_access_iterator &rit)	{
		return ptr != rit;
	}

	T	&operator*()	{
		return *ptr;
	}
	const T		&operator*() const	{
		return *ptr;
	}

	T	*operator->()	{
		return ptr;
	}
	const T	*operator->() const	{
		return ptr;
	}

	random_access_iterator	&operator+(int n)	{
		return random_access_iterator(ptr + n);
	}

	random_access_iterator	&operator-(int n)	{
		return random_access_iterator(ptr - n);
	}

	friend
	random_access_iterator	&operator+(int n, random_access_iterator &rit)	{
		return rit + n;
	}

	int		operator-(random_access_iterator &rit)	{
		return ptr - rit.ptr;
	}

	bool	operator<(random_access_iterator &rit)	{
		return ptr < rit.ptr;	}
	bool	operator<=(random_access_iterator &rit)	{
		return ptr <= rit.ptr;	}
	bool	operator>(random_access_iterator &rit)	{
		return ptr > rit.ptr;	}
	bool	operator>=(random_access_iterator &rit)	{
		return ptr >= rit.ptr;	}

	random_access_iterator	&operator+=(int n)	{
		ptr += n;
	}
	random_access_iterator	&operator-=(int n)	{
		ptr -= n;
	}

	T	&operator[](int n)	{
		return ptr[n];
	}

	const T	&operator[](int n) const	{
		return ptr[n];
	}

private:
	T	*ptr;
};

}

#endif
