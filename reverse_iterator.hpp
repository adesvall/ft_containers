#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{

template <class Iterator>
class reverse_iterator
{
public:
	typedef iterator_traits<Iterator>::iterator_type		iterator_type;
	typedef iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef iterator_traits<Iterator>::value_type			value_type;
	typedef iterator_traits<Iterator>::difference_type		difference_type;
	typedef iterator_traits<Iterator>::pointer				pointer;
	typedef iterator_traits<Iterator>::reference			reference;

	reverse_iterator()	{}
	explicit reverse_iterator (iterator_type it)	{}
	template <class Iter>
	reverse_iterator (const reverse_iterator<Iter>& rev_it)	{}
	~reverse_iterator();


private:
	Iterator it;
};

}

#endif