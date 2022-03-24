#ifndef RB_NODE_HPP
# define RB_NODE_HPP

#include "pair.hpp"

namespace ft
{

template <typename Key, typename T>
class RB_node
{
private:
	pair<Key, T>	value;
	int		color;
	RB_node	*less;
	RB_node	*more;

public:
	RB_node(/* args */);
	~RB_node();
};

}

#endif