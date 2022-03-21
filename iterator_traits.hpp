#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace ft
{

class input_iterator_tag	{};
class ouput_iterator_tag	{};
class forward_iterator_tag	{};
class bidirectional_iterator_tag	{};
class random_access_iterator_tag	{};


template <typename Iterator>
class iterator_traits
{
public:
	typedef typename Iterator::difference_type	difference_type;
	typedef typename Iterator::value_type		value_type;
	typedef typename Iterator::pointer			pointer;
	typedef typename Iterator::reference		reference;
	typedef typename Iterator::iterator_category	iterator_category;

};

}

#endif