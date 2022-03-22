#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{

template <bool, class IsTrue = void>
struct enable_if;

template <class IsTrue>
struct enable_if<true, IsTrue> {
	typedef IsTrue type;
};


template <bool flag, class IsTrue, class IsFalse>
struct choose;

template <class IsTrue, class IsFalse>
struct choose<true, IsTrue, IsFalse> {
   typedef IsTrue type;
};

template <class IsTrue, class IsFalse>
struct choose<false, IsTrue, IsFalse> {
   typedef IsFalse type;
};


template <typename I>
typename I::diference_type	distance(I first, I last)	{
	typename I::diference_type dist = 0;

	while (first != last)
	{
		first++;
		dist++;
	}
	return dist;
}

}

#endif
