#include "list.hpp"
#include <list>
#include <vector>
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

		fs1 << *ls.begin() << std::endl << std::flush;
		ls.insert(ls.begin(), 42);
		fs1 << *ls.begin() << std::endl << std::flush;

		ft::list<int> li;

		fs2 << *li.begin() << std::endl << std::flush;
		li.insert(li.begin(), 42);
		fs2 << *li.begin() << std::endl << std::flush;
	}

	judge();

	{
		std::list<int> ls;

		fs1 << *ls.end() << std::endl << std::flush;
		ls.insert(ls.end(), 42);
		fs1 << *ls.begin() << std::endl << std::flush;

		ft::list<int> li;

		fs2 << *li.end() << std::endl << std::flush;
		li.insert(li.end(), 42);
		fs2 << *li.begin() << std::endl << std::flush;
	}

	judge();

	{
		std::list<int> mylist;
  		std::list<int>::iterator it;

  		for (int i=1; i<=5; ++i) mylist.push_back(i);
  		it = mylist.begin();
  		++it;
		mylist.insert (it,10);
		mylist.insert (it,2,20);
		--it;
		std::vector<int> myvector (2,30);
		mylist.insert (it,myvector.begin(),myvector.end());
		for (it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it << std::flush;
		fs1 << '\n' << std::flush;

		ft::list<int> mylist_;
  		ft::list<int>::iterator it_;

  		for (int i=1; i<=5; ++i) mylist_.push_back(i);
  		it_ = mylist_.begin();
  		++it_;
		mylist_.insert (it_,10);
		mylist_.insert (it_,2,20);
		--it_;
		std::vector<int> myvector_ (2,30);
		mylist_.insert (it_,myvector_.begin(),myvector_.end());
		for (it_=mylist_.begin(); it_!=mylist_.end(); ++it_)
			fs2 << ' ' << *it_ << std::flush;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist;
		int sum (0);

		for (int i=1;i<=10;++i) mylist.push_back(i);
		while (!mylist.empty())
		{
			sum += mylist.front();
			mylist.pop_front();
		}
		fs1 << "total: " << sum << '\n' << std::flush;

		ft::list<int> mylist_;
		int sum_ (0);

		for (int i=1;i<=10;++i) mylist_.push_back(i);
		while (!mylist_.empty())
		{
			sum_ += mylist_.front();
			mylist_.pop_front();
		}
		fs2 << "total: " << sum_ << '\n' << std::flush;
	}

	judge();


	std::cout << std::endl;
	fs1.close();
	fs2.close();
	// system("rm 1 2");
	system("leaks a.out | grep leaked");
    return(EXIT_SUCCESS);
}
