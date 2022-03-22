#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{

template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator										iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;

	reverse_iterator()	{}
	explicit reverse_iterator(iterator_type ite) : _base(ite)	{}
	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it) : _base(rev_it.base())	{}
	~reverse_iterator()	{}
	
	iterator_type base() const	{
		return _base;
	}

	// reverse_iterator	&operator=(const reverse_iterator	&rit)	{
	// 	ptr = rit.ptr;
	// 	return *this;
	// }

	value_type	&operator*()	{
		return *_base;
	}

	const value_type	&operator*() const	{
		return *_base;
	}

	reverse_iterator	operator+(difference_type n) const	{
		return reverse_iterator(_base - n);
	}

	reverse_iterator	&operator++()	{
		_base--;
		return *this;
	}

	reverse_iterator operator++(int)	{
		reverse_iterator it(*this);
		_base--;
		return it;
	}

	reverse_iterator	&operator+=(difference_type n)	{
		_base -= n;
		return *this;
	}

	reverse_iterator	operator-(difference_type n) const	{
		return reverse_iterator(_base + n);
	}

	reverse_iterator	&operator--()	{
		_base++;
		return *this;
	}

	reverse_iterator operator--(int)	{
		reverse_iterator it(*this);
		_base++;
		return it;
	}

	reverse_iterator	&operator-=(int n)	{
		_base += n;
		return *this;
	}

	value_type	*operator->()	{
		return &(operator*());
	}
	const value_type	*operator->() const	{
		return &(operator*());
	}

	value_type	&operator[](int n)	{
		return _base[-n - 1];
	}

	const value_type	&operator[](int n) const	{
		return _base[-n - 1];
	}

// NON MEMBERS FUNCTIONS

	friend
	reverse_iterator	operator+(difference_type n, const reverse_iterator &rit)	{
		return rit + n;
	}


private:
	iterator_type _base;
};

template <typename I_L, typename I_R>
bool operator== (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() == rhs.base();
}
template <typename I_L, typename I_R>
bool operator!= (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() != rhs.base();
}
template <typename I_L, typename I_R>
bool operator<  (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() > rhs.base();
}
template <typename I_L, typename I_R>
bool operator<= (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() >= rhs.base();
}
template <typename I_L, typename I_R>
bool operator>  (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() < rhs.base();
}
template <typename I_L, typename I_R>
bool operator>= (const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R>& rhs)	{
	return lhs.base() <= rhs.base();
}

template <typename I_L, typename I_R>
typename reverse_iterator<I_L>::difference_type		operator-(const reverse_iterator<I_L>& lhs, const reverse_iterator<I_R> &rhs)	{
	return rhs.base() - lhs.base();
}

}

#endif