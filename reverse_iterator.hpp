#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{

template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator										iterator_type;
	typedef iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef iterator_traits<Iterator>::value_type			value_type;
	typedef iterator_traits<Iterator>::difference_type		difference_type;
	typedef iterator_traits<Iterator>::pointer				pointer;
	typedef iterator_traits<Iterator>::reference			reference;

	reverse_iterator()	{}
	explicit reverse_iterator(iterator_type ite) : _base(ite)	{}
	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it) : _base(rev_it.it)	{}
	~reverse_iterator();
	
	iterator_type base() const	{
		return _base;
	}

	// reverse_iterator	&operator=(const reverse_iterator	&rit)	{
	// 	ptr = rit.ptr;
	// 	return *this;
	// }

	T	&operator*()	{
		return *_base;
	}

	const T		&operator*() const	{
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

	T	*operator->()	{
		return &(operator*());
	}
	const T	*operator->() const	{
		return &(operator*());
	}

	T	&operator[](int n)	{
		return _base[-n - 1];
	}

	const T	&operator[](int n) const	{
		return _base[-n - 1];
	}

// NON MEMBERS FUNCTIONS
	friend
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)	{
		return 
	}

	friend
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)	{
		
	}

	friend
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)	{
		
	}

	friend
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)	{
		
	}

	friend
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)	{
		
	}

	friend
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)	{

	}

/*
	friend
	bool	operator==(const reverse_iterator &rit) const	{
		return ptr == rit;
	}

	bool	operator!=(const reverse_iterator &rit) const	{
		return ptr != rit.ptr;
	}

	friend
	reverse_iterator	operator+(int n, reverse_iterator &rit)	{
		return rit + n;
	}

	difference_type		operator-(const reverse_iterator &rit) const	{
		return ptr - rit.ptr;
	}


*/


private:
	Iterator base;
};

}

#endif