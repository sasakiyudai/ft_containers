#include "list.hpp"
#include <list>
#include <iostream>

int main()
{
	ft::list<int> li(1,1);

	ft::list_iterator<int> it;

	std::list<int> ls;

	ls.insert(ls.begin(), 42);

	std::cout << *ls.begin() << std::endl;

}
