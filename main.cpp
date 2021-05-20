#include "list.hpp"
#include <list>
#include <iostream>

int main()
{
	std::list<int> ls;
	std::cout << *ls.begin() << std::endl;
	ls.insert(ls.begin(), 42);
	std::cout << *ls.begin() << std::endl;

	ft::list<int> li;
	std::cout << *li.begin() << std::endl;
	li.insert(li.begin(), 42);
	std::cout << *li.begin() << std::endl;
}
