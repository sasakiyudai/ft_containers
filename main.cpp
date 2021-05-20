#include "list.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <stdlib.h>

void judge()
{
	if (system("diff 1 2") == 0)
		std::cout << "\033[32m[OK] \033[m";
	else
		std::cout << "\033[31m[KO] \033[m";
}

int main()
{
	std::ofstream fs1;
    std::ofstream fs2;
	fs1.open("1");
	fs2.open("2");

	std::cout << "=== LIST ===" << std::endl;
	{
		std::list<int> ls;
		fs1 << *ls.begin() << std::endl;
		ls.insert(ls.begin(), 42);
		fs1 << *ls.begin() << std::endl;

		ft::list<int> li;
		fs2 << *li.begin() << std::endl;
		li.insert(li.begin(), 42);
		fs2 << *li.begin() << std::endl;
	}
	judge();
	{
		std::list<int> ls;
		fs1 << *ls.begin() << std::endl;
		ls.insert(ls.begin(), 42);
		fs1 << *ls.begin() << std::endl;

		ft::list<int> li;
		fs2 << *li.begin() << std::endl;
		li.insert(li.begin(), 42);
		fs2 << *li.begin() << std::endl;
	}
	judge();

	std::cout << std::endl;
	fs1.close();
	fs2.close();
	// system("rm 1 2");
	system("leaks a.out | grep leaked");
    return(EXIT_SUCCESS);
}
