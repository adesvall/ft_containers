#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

template <class T>
class	random_access_iterator
{
public:
	random_access_iterator() : ptr(NULL)	{}
	random_access_iterator(T *ptr) : ptr(ptr)	{}
	random_access_iterator(random_access_iterator &rit) : ptr(rit.ptr)	{}
	~random_access_iterator()	{}

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
	const T		&operator*()	{
		return *ptr;
	}

	T	*operator->()	{
		return ptr;
	}
	const T	*operator->()	{
		return ptr;
	}

	random_access_iterator	&operator+(int n)	{
		return random_access_iterator(ptr + n);
	}

	random_access_iterator	&operator-(int n)	{
		return random_access_iterator(ptr - n);
	}

	friend
	random_access_iterator	&operator+(int n, random_access_operator &rit)	{
		return random_access_iterator(ptr + n);
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

private:
	T	*ptr;
}

#endif
