/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:45:35 by upeyret           #+#    #+#             */
/*   Updated: 2022/05/18 22:04:36 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "stack.hpp"
// #include "vector.hpp"
// #include "AVL_tree.hpp"
#include <iostream>
// #include <vector>

#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
    #define mytype "FT"
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
    #define mytype "FT"
#endif

#include <stdlib.h>
#include <time.h>
#define COUNT 1000

int main(void)
{
  try
  {
    std::cout << "Version: " << mytype << std::endl;
    std::cout << "Nb of items to insert: " << COUNT << std::endl; 
    std::cout << "#### TESTS MAP ####" << std::endl;
	
	srand(10000);
	
	ft::map<int, int> map_int;
	ft::map<int, int> map_int2;
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(i, rand()));
		map_int2.insert(ft::make_pair(i, rand()));
	}
	std::cout << "map_int[0]: " << map_int[0] << std::endl;
	std::cout << "map_int2[0]: " << map_int2[0] << std::endl;
	
    std::cout << "SWAP" << std::endl;
	map_int2.swap(map_int);
	std::cout << "map_int[0]: " << map_int[0] << std::endl;
	std::cout << "map_int2[0]: " << map_int2[0] << std::endl;
	map_int2.clear();

    
    std::cout << "#### TESTS VECTOR ####" << std::endl;
	ft::vector<int> first;
    ft::vector<int> second((size_t)5, 100);

    std::cout << "INSERT" << std::endl;
	ft::vector<int> vct2;
	std::cout << &(*vct2.end()) << std::endl;
	vct2.insert(vct2.begin(), 2, 21);
	std::cout << &(*vct2.end()) << std::endl;
	vct2.insert(vct2.begin(), 42);
	vct2.clear();
	
    std::cout << "SWAP" << std::endl;
    std::cout << &first << std::endl;
    std::cout << &second << std::endl;
    first.swap(second);
    std::cout << &first << std::endl;
    std::cout << &second << std::endl;
    std::cout << first.size() << std::endl;
    std::cout << "capacity: " << first.capacity() << std::endl;
    std::cout << first[0] << std::endl;
    std::cout << first[4] << std::endl;
    std::cout << second.size() << std::endl;
    std::cout << "capacity: "<< second.capacity() << std::endl;
    
    std::cout << "OPERATOR EGAL AND CLEAR" << std::endl;
    first = second;
    std::cout << first.size() << std::endl;
    std::cout << "capacity: "<< first.capacity() << std::endl;
    std::cout << first[0] << std::endl;
    std::cout << first[4] << std::endl;
    first.clear();
    std::cout << first.size() << std::endl;
    std::cout << "capacity: "<< first.capacity() << std::endl;
    std::cout << first[0] << std::endl;
    std::cout << first[4] << std::endl;

    std::cout << "ASSIGN" << std::endl;
    ft::vector<int> test((size_t)5, 100);
    std::cout << test[0] << std::endl;
    test.assign((size_t)5, 200);
    
    test.assign((size_t)6, 300);
    std::cout << test[5] << std::endl;
    
    test.assign((size_t)4, 400);
    std::cout << test.size() << std::endl;
    std::cout << "capacity: " << test.capacity() << std::endl;
    std::cout << test[0] << std::endl;
    std::cout << test[1] << std::endl;
    std::cout << test[2] << std::endl;
    std::cout << test[3] << std::endl;
    std::cout << test[4] << std::endl;
    std::cout << test[5] << std::endl;

    
    std::cout << "SIZE" << std::endl;
    std::cout << first.size() << std::endl;
    std::cout << second.size() << std::endl;
    
    std::cout << "MAX_SIZE" << std::endl;
    std::cout << first.max_size() << std::endl;
    std::cout << second.max_size() << std::endl;
    
    std::cout << "CAPACITY" << std::endl;
    std::cout << "capacity: "<< first.capacity() << std::endl;
    std::cout << "capacity: "<< second.capacity() << std::endl;
    
    std::cout << "EMPTY" << std::endl;
    std::cout << first.empty() << std::endl;
    std::cout << second.empty() << std::endl;
    
    std::cout << "RESERVE" << std::endl;
    first.reserve(0);
    std::cout << "capacity: "<< first.capacity() << std::endl;
    first.reserve(1);
    std::cout << "capacity: "<< first.capacity() << std::endl;
    first.reserve((size_t)100000);
    std::cout << "capacity: "<< first.capacity() << std::endl;
    
    std::cout << "RESIZE" << std::endl;
    first.resize(0);
    std::cout << first.size() << std::endl;
    std::cout << "capacity: "<< first.capacity() << std::endl;
    second.resize(10);
    std::cout << second.size() << std::endl;
    std::cout << "capacity: "<< second.capacity() << std::endl;
    std::cout << second[0] << std::endl;
    second.resize(11);
    std::cout << second.size() << std::endl;
    std::cout << "capacity: "<< second.capacity() << std::endl;
    std::cout << second[10] << std::endl;
    second.resize(12, -1);
    std::cout << second.size() << std::endl;
    std::cout << "capacity: "<< second.capacity() << std::endl;
    std::cout << second[10] << std::endl;
    std::cout << second[11] << std::endl;
    std::cout << second.at(11) << std::endl;


    std::cout << "FRONT / BACK " << std::endl;
    ft::vector<int> third;
    ft::vector<int> second2(second);
    std::cout << second2.front() << std::endl;
    std::cout << second2.back() << std::endl;

    std::cout << "GET ALLOCATOR " << std::endl;
    std::cout << (third.get_allocator().max_size()) << std::endl;
    
    first.reserve(1);
    std::cout << "capacity: " << first.capacity() << std::endl;
    first.reserve((size_t)100000);
    std::cout << "capacity: " << first.capacity() << std::endl;
    
  }
  catch(const std::exception& e)
  {
      std::cerr << e.what() << '\n';
  }


    ft::stack<int> mstack;
    ft::stack<int> mstack2;
    mstack.push(5);
    mstack.push(5);
    std::cout << mstack.top() << std::endl;
    mstack.pop();
    std::cout << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);

    ft::stack<int> mstack3(mstack);
    mstack2.push(17);
    std::cout << "Hello " << (mstack == mstack3) << std::endl;
    std::cout << (mstack == mstack2) << std::endl;
    std::cout << (mstack != mstack2) << std::endl;
    std::cout << (mstack < mstack2) << std::endl;
    std::cout << (mstack <= mstack2) << std::endl;
    std::cout << (mstack > mstack2) << std::endl;
    std::cout << (mstack >= mstack2) << std::endl;
    mstack2 = mstack;
    std::cout << (mstack == mstack2) << std::endl;    
    return 0;
}