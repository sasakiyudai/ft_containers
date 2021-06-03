#include "list.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include <cmath>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <fstream>
#include <stdlib.h>

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
bool operator() (const int& value) { return (value%2)==1; }
};

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

// compare only integral part:
bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

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
	fs1 << "=== LIST ===" << std::endl;
	fs2 << "=== LIST ===" << std::endl;
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

	{
		// constructors used in the same order as described above:
		std::list<int> first;                                // empty list of ints
		std::list<int> second (4,100);                       // four ints with value 100
		std::list<int> third (second.begin(),second.end());  // iterating through second
		std::list<int> fourth (third);                       // a copy of third

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		std::list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		fs1 << "The contents of first are\n" << std::flush;
		for (std::list<int>::iterator it = first.begin(); it != first.end(); it++)
			fs1 << *it << ' ' << std::flush;
		fs1 << "The contents of second are\n" << std::flush;
		for (std::list<int>::iterator it = second.begin(); it != second.end(); it++)
			fs1 << *it << ' ' << std::flush;
		fs1 << "The contents of third are\n" << std::flush;
		for (std::list<int>::iterator it = third.begin(); it != third.end(); it++)
			fs1 << *it << ' ' << std::flush;
		fs1 << "The contents of fourth are\n" << std::flush;
		for (std::list<int>::iterator it = fourth.begin(); it != fourth.end(); it++)
			fs1 << *it << ' ' << std::flush;
		fs1 << "The contents of fifth are\n" << std::flush;
		for (std::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
			fs1 << *it << ' ' << std::flush;

		
		// constructors used in the same order as described above:
		ft::list<int> first_;                                // empty list of ints
		ft::list<int> second_ (4,100);                       // four ints with value 100
		ft::list<int> third_ (second_.begin(),second_.end());  // iterating through second_
		ft::list<int> fourth_ (third_);                       // a copy of third_

		// the iterator constructor can also be used to construct from arrays:
		int myints_[] = {16,2,77,29};
		ft::list<int> fifth_ (myints_, myints_ + sizeof(myints_) / sizeof(int) );

		fs2 << "The contents of first are\n" << std::flush;
		for (ft::list<int>::iterator it = first_.begin(); it != first_.end(); it++)
			fs2 << *it << ' ' << std::flush;
		fs2 << "The contents of second are\n" << std::flush;
		for (ft::list<int>::iterator it = second_.begin(); it != second_.end(); it++)
			fs2 << *it << ' ' << std::flush;
		fs2 << "The contents of third are\n" << std::flush;
		for (ft::list<int>::iterator it = third_.begin(); it != third_.end(); it++)
			fs2 << *it << ' ' << std::flush;
		fs2 << "The contents of fourth are\n" << std::flush;
		for (ft::list<int>::iterator it = fourth_.begin(); it != fourth_.end(); it++)
			fs2 << *it << ' ' << std::flush;
		fs2 << "The contents of fifth are\n" << std::flush;
		for (ft::list<int>::iterator it = fifth_.begin(); it != fifth_.end(); it++)
			fs2 << *it << ' ' << std::flush;
	}

	judge();

	{
		std::list<int> first (3);      // list of 3 zero-initialized ints
		std::list<int> second (5);     // list of 5 zero-initialized ints

		second = first;
		first = std::list<int>();

		fs1 << "Size of first: " << int (first.size()) << '\n';
		fs1 << "Size of second: " << int (second.size()) << '\n' << std::flush;

		ft::list<int> first_ (3);      // list of 3 zero-initialized ints
		ft::list<int> second_ (5);     // list of 5 zero-initialized ints

		second_ = first_;
		first_ = ft::list<int>();

		fs2 << "Size of first: " << int (first_.size()) << '\n';
		fs2 << "Size of second: " << int (second_.size()) << '\n' << std::flush;
	}

	judge();

	{
		int myints[] = {75,23,65,42,13};
		std::list<int> mylist (myints,myints+5);

		fs1 << "mylist contains:";
		for (std::list<int>::iterator it=mylist.begin(); it != mylist.end(); ++it)
			fs1 << ' ' << *it;

		fs1 << '\n' << std::flush;


		int myints_[] = {75,23,65,42,13};
		ft::list<int> mylist_ (myints_,myints_+5);

		fs2 << "mylist contains:";
		for (ft::list<int>::iterator it=mylist_.begin(); it != mylist_.end(); ++it)
			fs2 << ' ' << *it;

		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist;
		for (int i=1; i<=5; ++i) mylist.push_back(i);

		fs1 << "mylist backwards:";
		for (std::list<int>::reverse_iterator rit=mylist.rbegin(); rit!=mylist.rend(); ++rit)
			fs1 << ' ' << *rit;

		fs1 << '\n' << std::flush;


		ft::list<int> mylist_;
		for (int i=1; i<=5; ++i) mylist_.push_back(i);

		fs2 << "mylist backwards:";
		for (ft::list<int>::reverse_iterator rit=mylist_.rbegin(); rit!=mylist_.rend(); ++rit)
			fs2 << ' ' << *rit;

		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> myints;
		fs1 << "0. size: " << myints.size() << '\n';
		for (int i=0; i<10; i++) myints.push_back(i);
		fs1 << "1. size: " << myints.size() << '\n';
		myints.insert (myints.begin(),10,100);
		fs1 << "2. size: " << myints.size() << '\n';
		myints.pop_back();
		fs1 << "3. size: " << myints.size() << '\n' << std::flush;


		ft::list<int> myints_;
		fs2 << "0. size: " << myints_.size() << '\n';
		for (int i=0; i<10; i++) myints_.push_back(i);
		fs2 << "1. size: " << myints_.size() << '\n';
		myints_.insert (myints_.begin(),10,100);
		fs2 << "2. size: " << myints_.size() << '\n';
		myints_.pop_back();
		fs2 << "3. size: " << myints_.size() << '\n'<< std::flush;
	}

	judge();

	{
		const int i = 42;
		std::list<int> mylist;

		fs1 << "Enter number of elements: ";

		if (i<mylist.max_size()) mylist.resize(i);
		else fs1 << "That size exceeds the limit.\n" << std::flush;

		fs1 << mylist.size() << std::flush;


		const int i_ = 42;
		ft::list<int> mylist_;

		fs2 << "Enter number of elements: ";

		if (i_<mylist_.max_size()) mylist_.resize(i_);
		else fs2 << "That size exceeds the limit.\n" << std::flush;

		fs2 << mylist_.size() << std::flush;
	}

	judge();

	{
		std::list<int> mylist;

		mylist.push_back(77);
		mylist.push_back(22);

		// now front equals 77, and back 22

		mylist.front() -= mylist.back();

		fs1 << "mylist.front() is now " << mylist.front() << '\n' << std::flush;


		ft::list<int> mylist_;

		mylist_.push_back(77);
		mylist_.push_back(22);

		// now front equals 77, and back 22

		mylist_.front() -= mylist_.back();

		fs2 << "mylist.front() is now " << mylist_.front() << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist;

		mylist.push_back(10);
		while (mylist.back() != 0)
		{
			mylist.push_back ( mylist.back() -1 );
		}
		fs1 << "mylist contains:";
		for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end() ; ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::list<int> mylist_;

		mylist_.push_back(10);
		while (mylist_.back() != 0)
		{
			mylist_.push_back ( mylist_.back() -1 );
		}
		fs2 << "mylist contains:";
		for (ft::list<int>::iterator it=mylist_.begin(); it!=mylist_.end() ; ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> first;
		std::list<int> second;

		first.assign (7,100);                      // 7 ints with value 100

		second.assign (first.begin(),first.end()); // a copy of first

		int myints[]={1776,7,4};
		first.assign (myints,myints+3);            // assigning from array

		fs1 << "Size of first: " << int (first.size()) << '\n';
		fs1 << "Size of second: " << int (second.size()) << '\n' << std::flush;


		ft::list<int> first_;
		ft::list<int> second_;

		first_.assign (7,100);                      // 7 ints with value 100

		second_.assign (first_.begin(),first_.end()); // a copy of first_

		int myints_[]={1776,7,4};
		first_.assign (myints_,myints_+3);            // assigning from array

		fs2 << "Size of first: " << int (first_.size()) << '\n';
		fs2 << "Size of second: " << int (second_.size()) << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist (2,100);         // two ints with a value of 100
		mylist.push_front (200);
		mylist.push_front (300);

		fs1 << "mylist contains:";
		for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;

		fs1 << '\n' << std::flush;


		ft::list<int> mylist_ (2,100);         // two ints with a value of 100
		mylist_.push_front (200);
		mylist_.push_front (300);

		fs2 << "mylist contains:";
		for (ft::list<int>::iterator it_=mylist_.begin(); it_!=mylist_.end(); ++it_)
			fs2 << ' ' << *it_;

		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist;
		mylist.push_back (100);
		mylist.push_back (200);
		mylist.push_back (300);

		fs1 << "Popping out the elements in mylist:";
		while (!mylist.empty())
		{
			fs1 << ' ' << mylist.front();
			mylist.pop_front();
		}

		fs1 << "\nFinal size of mylist is " << mylist.size() << '\n' << std::flush;


		ft::list<int> mylist_;
		mylist_.push_back (100);
		mylist_.push_back (200);
		mylist_.push_back (300);

		fs2<< "Popping out the elements in mylist:";
		while (!mylist_.empty())
		{
			fs2<< ' ' << mylist_.front();
			mylist_.pop_front();
		}

		fs2<< "\nFinal size of mylist is " << mylist_.size() << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist;
		const int myint[8] = {1,2,3,4,5,6,7,8};

		fs1 << "Please enter some integers (enter 0 to end):\n";

		for (int i = 0; i < 8; i++)
			mylist.push_back (myint[i]);

		fs1 << "mylist stores " << mylist.size() << " numbers.\n" << std::flush;


		ft::list<int> mylist_;
		const int myint_[8] = {1,2,3,4,5,6,7,8};

		fs2 << "Please enter some integers (enter 0 to end):\n";

		for (int i = 0; i < 8; i++)
			mylist_.push_back (myint_[i]);

		fs2 << "mylist stores " << mylist_.size() << " numbers.\n" << std::flush;
	}

	judge();

	{
		std::list<int> mylist;
		int sum (0);
		mylist.push_back (100);
		mylist.push_back (200);
		mylist.push_back (300);

		while (!mylist.empty())
		{
			sum+=mylist.back();
			mylist.pop_back();
		}

		fs1 << "The elements of mylist summed " << sum << '\n' << std::flush;


		ft::list<int> mylist_;
		int sum_ (0);
		mylist_.push_back (100);
		mylist_.push_back (200);
		mylist_.push_back (300);

		while (!mylist_.empty())
		{
			sum_+=mylist_.back();
			mylist_.pop_back();
		}

		fs2 << "The elements of mylist summed " << sum_ << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist;
		std::list<int>::iterator it;

		// set some initial values:
		for (int i=1; i<=5; ++i) mylist.push_back(i); // 1 2 3 4 5

		it = mylist.begin();
		++it;       // it points now to number 2           ^

		mylist.insert (it,10);                        // 1 10 2 3 4 5

		// "it" still points to number 2                      ^
		mylist.insert (it,2,20);                      // 1 10 20 20 2 3 4 5

		--it;       // it points now to the second 20            ^

		std::vector<int> myvector (2,30);
		mylist.insert (it,myvector.begin(),myvector.end());
														// 1 10 20 30 30 20 2 3 4 5
														//               ^
		fs1 << "mylist contains:";
		for (it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n';


		ft::list<int> mylist_;
		ft::list<int>::iterator it_;

		// set some init_ial values:
		for (int i=1; i<=5; ++i) mylist_.push_back(i); // 1 2 3 4 5

		it_ = mylist_.begin();
		++it_;       // it_ points now to number 2           ^

		mylist_.insert (it_,10);                        // 1 10 2 3 4 5

		// "it_" still points to number 2                      ^
		mylist_.insert (it_,2,20);                      // 1 10 20 20 2 3 4 5

		--it_;       // it_ points now to the second 20            ^

		std::vector<int> myvector_ (2,30);
		mylist_.insert (it_,myvector_.begin(),myvector_.end());
														// 1 10 20 30 30 20 2 3 4 5
														//               ^
		fs2<< "mylist contains:";
		for (it_=mylist_.begin(); it_!=mylist_.end(); ++it_)
			fs2<< ' ' << *it_;
		fs2<< '\n';
	}

	judge();

	{
		std::list<int> mylist;
		std::list<int>::iterator it1,it2;

		// set some values:
		for (int i=1; i<10; ++i) mylist.push_back(i*10);

									// 10 20 30 40 50 60 70 80 90
		it1 = it2 = mylist.begin(); // ^^
		for (int i = 0; i < 6; i++)
			++it2;          // ^                 ^
		++it1;                      //    ^              ^

		it1 = mylist.erase (it1);   // 10 30 40 50 60 70 80 90
									//    ^           ^

		it2 = mylist.erase (it2);   // 10 30 40 50 60 80 90
									//    ^           ^

		++it1;                      //       ^        ^
		--it2;                      //       ^     ^

		mylist.erase (it1,it2);     // 10 30 60 80 90
									//        ^

		fs1 << "mylist contains:";
		for (it1=mylist.begin(); it1!=mylist.end(); ++it1)
			fs1 << ' ' << *it1;
		fs1 << '\n' << std::flush;


		ft::list<int> mylist_;
		ft::list<int>::iterator it1_,it2_;

		// set some values:
		for (int i=1; i<10; ++i) mylist_.push_back(i*10);

									// 10 20 30 40 50 60 70 80 90
		it1_ = it2_ = mylist_.begin(); // ^^
		for (int i = 0; i < 6; i++)
			++it2_;          // ^                 ^
		++it1_;                      //    ^              ^

		it1_ = mylist_.erase (it1_);   // 10 30 40 50 60 70 80 90
									//    ^           ^

		it2_ = mylist_.erase (it2_);   // 10 30 40 50 60 80 90
									//    ^           ^

		++it1_;                      //       ^        ^
		--it2_;                      //       ^     ^

		mylist_.erase (it1_,it2_);     // 10 30 60 80 90
									//        ^

		fs2 << "mylist contains:";
		for (it1_=mylist_.begin(); it1_!=mylist_.end(); ++it1_)
			fs2 << ' ' << *it1_;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> first (3,100);   // three ints with a value of 100
		std::list<int> second (5,200);  // five ints with a value of 200

		first.swap(second);

		fs1 << "first contains:";
		for (std::list<int>::iterator it=first.begin(); it!=first.end(); it++)
			fs1 << ' ' << *it;
		fs1 << '\n';

		fs1 << "second contains:";
		for (std::list<int>::iterator it=second.begin(); it!=second.end(); it++)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::list<int> first_ (3,100);   // three ints with a value of 100
		ft::list<int> second_ (5,200);  // five ints with a value of 200

		first_.swap(second_);

		fs2 << "first contains:";
		for (ft::list<int>::iterator it=first_.begin(); it!=first_.end(); it++)
			fs2 << ' ' << *it;
		fs2 << '\n';

		fs2 << "second contains:";
		for (ft::list<int>::iterator it=second_.begin(); it!=second_.end(); it++)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist;

		// set some initial content:
		for (int i=1; i<10; ++i) mylist.push_back(i);

		mylist.resize(5);
		mylist.resize(8,100);
		mylist.resize(12);

		fs1 << "mylist contains:";
		for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;

		fs1 << '\n' << std::flush;


		ft::list<int> mylist_;

		// set some initial content:
		for (int i=1; i<10; ++i) mylist_.push_back(i);

		mylist_.resize(5);
		mylist_.resize(8,100);
		mylist_.resize(12);

		fs2 << "mylist contains:";
		for (ft::list<int>::iterator it=mylist_.begin(); it!=mylist_.end(); ++it)
			fs2 << ' ' << *it;

		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist;
		std::list<int>::iterator it;

		mylist.push_back (100);
		mylist.push_back (200);
		mylist.push_back (300);

		fs1 << "mylist contains:";
		for (it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n';

		mylist.clear();
		mylist.push_back (1101);
		mylist.push_back (2202);

		fs1 << "mylist contains:";
		for (it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::list<int> mylist_;
		ft::list<int>::iterator it_;

		mylist_.push_back (100);
		mylist_.push_back (200);
		mylist_.push_back (300);

		fs2 << "mylist contains:";
		for (it_=mylist_.begin(); it_!=mylist_.end(); ++it_)
			fs2 << ' ' << *it_;
		fs2 << '\n';

		mylist_.clear();
		mylist_.push_back (1101);
		mylist_.push_back (2202);

		fs2 << "mylist contains:";
		for (it_=mylist_.begin(); it_!=mylist_.end(); ++it_)
			fs2 << ' ' << *it_;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist1, mylist2;
		std::list<int>::iterator it;

		// set some initial values:
		for (int i=1; i<=4; ++i)
			mylist1.push_back(i);      // mylist1: 1 2 3 4

		for (int i=1; i<=3; ++i)
			mylist2.push_back(i*10);   // mylist2: 10 20 30

		it = mylist1.begin();
		++it;                         // points to 2

		mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
										// mylist2 (empty)
										// "it" still points to 2 (the 5th element)
												
		mylist2.splice (mylist2.begin(),mylist1, it);
										// mylist1: 1 10 20 30 3 4
										// mylist2: 2
										// "it" is now invalid.
		it = mylist1.begin();
		for (int i = 0; i < 3; i++)
			it++;                       // "it" points now to 30

		mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
										// mylist1: 30 3 4 1 10 20

		fs1 << "mylist1 contains:";
		for (it=mylist1.begin(); it!=mylist1.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n';

		fs1 << "mylist2 contains:";
		for (it=mylist2.begin(); it!=mylist2.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::list<int> mylist1_, mylist2_;
		ft::list<int>::iterator it_;

		// set some init_ial values:
		for (int i=1; i<=4; ++i)
			mylist1_.push_back(i);      // mylist1_: 1 2 3 4

		for (int i=1; i<=3; ++i)
			mylist2_.push_back(i*10);   // mylist2_: 10 20 30

		it_ = mylist1_.begin();
		++it_;                         // points to 2
		
		mylist1_.splice (it_, mylist2_); // mylist1_: 1 10 20 30 2 3 4
										// mylist2_ (empty)
										// "it_" still points to 2 (the 5th element)
							
		mylist2_.splice (mylist2_.begin(),mylist1_, it_);
										// mylist1_: 1 10 20 30 3 4
										// mylist2_: 2
										// "it_" is now invalid.
		it_ = mylist1_.begin();
		
		for (int i = 0; i < 3; i++)
			it_++;                       // "it" points now to 30

		mylist1_.splice ( mylist1_.begin(), mylist1_, it_, mylist1_.end());
										// mylist1_: 30 3 4 1 10 20
		

		fs2 << "mylist1 contains:";
		for (it_=mylist1_.begin(); it_!=mylist1_.end(); ++it_)
			fs2 << ' ' << *it_;
		fs2 << '\n';

		fs2 << "mylist2 contains:";
		for (it_=mylist2_.begin(); it_!=mylist2_.end(); ++it_)
			fs2 << ' ' << *it_;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		int myints[]= {17,89,7,14};
		std::list<int> mylist (myints,myints+4);

		mylist.remove(89);

		fs1 << "mylist contains:";
		for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		int myints_[]= {17,89,7,14};
		ft::list<int> mylist_ (myints_,myints_+4);

		mylist_.remove(89);

		fs2 << "mylist contains:";
		for (ft::list<int>::iterator it=mylist_.begin(); it!=mylist_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		int myints[]= {15,36,7,17,20,39,4,1};
		std::list<int> mylist (myints,myints+8);   // 15 36 7 17 20 39 4 1

		mylist.remove_if (single_digit);           // 15 36 17 20 39

		mylist.remove_if (is_odd());               // 36 20

		fs1 << "mylist contains:";
		for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		int myints_[]= {15,36,7,17,20,39,4,1};
		ft::list<int> mylist_ (myints_,myints_+8);   // 15 36 7 17 20 39 4 1

		mylist_.remove_if (single_digit);           // 15 36 17 20 39

		mylist_.remove_if (is_odd());               // 36 20

		fs2 << "mylist contains:";
		for (ft::list<int>::iterator it=mylist_.begin(); it!=mylist_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	{

		double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
							12.77, 73.35, 72.25, 15.3,  72.25 };
		std::list<double> mylist (mydoubles,mydoubles+10);
		
		mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
									// 15.3,  72.25, 72.25, 73.0,  73.35

		mylist.unique();           //  2.72,  3.14, 12.15, 12.77
									// 15.3,  72.25, 73.0,  73.35

		mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
											// 15.3,  72.25, 73.0

		mylist.unique (is_near());           //  2.72, 12.15, 72.25

		fs1 << "mylist contains:";
		for (std::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;



		double mydoubles_[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
							12.77, 73.35, 72.25, 15.3,  72.25 };
		ft::list<double> mylist_ (mydoubles_,mydoubles_+10);
		
		mylist_.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
									// 15.3,  72.25, 72.25, 73.0,  73.35

		mylist_.unique();           //  2.72,  3.14, 12.15, 12.77
									// 15.3,  72.25, 73.0,  73.35

		mylist_.unique (same_integral_part);  //  2.72,  3.14, 12.15
											// 15.3,  72.25, 73.0

		mylist_.unique (is_near());           //  2.72, 12.15, 72.25

		fs2 << "mylist contains:";
		for (ft::list<double>::iterator it=mylist_.begin(); it!=mylist_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<double> first, second;

		first.push_back (3.1);
		first.push_back (2.2);
		first.push_back (2.9);

		second.push_back (3.7);
		second.push_back (7.1);
		second.push_back (1.4);

		first.sort();
		second.sort();

		first.merge(second);

		// (second is now empty)

		second.push_back (2.1);

		first.merge(second,mycomparison);

		fs1 << "first contains:";
		for (std::list<double>::iterator it=first.begin(); it!=first.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;



		ft::list<double> first_, second_;

		first_.push_back (3.1);
		first_.push_back (2.2);
		first_.push_back (2.9);

		second_.push_back (3.7);
		second_.push_back (7.1);
		second_.push_back (1.4);

		first_.sort();
		second_.sort();

		first_.merge(second_);

		// (second_ is now empty)

		second_.push_back (2.1);

		first_.merge(second_,mycomparison);

		fs2 << "first contains:";
		for (ft::list<double>::iterator it=first_.begin(); it!=first_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<std::string> mylist;
		std::list<std::string>::iterator it;
		mylist.push_back ("one");
		mylist.push_back ("two");
		mylist.push_back ("Three");

		mylist.sort();

		fs1 << "mylist contains:";
		for (it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n';

		mylist.sort(compare_nocase);

		fs1 << "mylist contains:";
		for (it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::list<std::string> mylist_;
		ft::list<std::string>::iterator it_;
		mylist_.push_back ("one");
		mylist_.push_back ("two");
		mylist_.push_back ("Three");

		mylist_.sort();

		fs2 << "mylist contains:";
		for (it_=mylist_.begin(); it_!=mylist_.end(); ++it_)
			fs2 << ' ' << *it_;
		fs2 << '\n';

		mylist_.sort(compare_nocase);

		fs2 << "mylist contains:";
		for (it_=mylist_.begin(); it_!=mylist_.end(); ++it_)
			fs2 << ' ' << *it_;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::list<int> mylist;

		for (int i=1; i<10; ++i) mylist.push_back(i);

		mylist.reverse();

		fs1 << "mylist contains:";
		for (std::list<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
			fs1 << ' ' << *it;

		fs1 << '\n' << std::flush;


		ft::list<int> mylist_;

		for (int i=1; i<10; ++i) mylist_.push_back(i);

		mylist_.reverse();

		fs2 << "mylist contains:";
		for (ft::list<int>::iterator it=mylist_.begin(); it!=mylist_.end(); ++it)
			fs2 << ' ' << *it;

		fs2 << '\n' << std::flush;
	}

	judge();

	{
		int _a[] = {10, 20, 30};
		int _b[] = {10, 20, 30};
		int _c[] = {30, 20, 10};
		std::list<int> a(_a, _a+3);
		std::list<int> b(_b, _b+3);
		std::list<int> c(_c, _c+3);

		if (a==b) fs1 << "a and b are equal\n";
		if (b!=c) fs1 << "b and c are not equal\n";
		if (b<c) fs1 << "b is less than c\n";
		if (c>b) fs1 << "c is greater than b\n";
		if (a<=b) fs1 << "a is less than or equal to b\n";
		if (a>=b) fs1 << "a is greater than or equal to b\n" << std::flush;


		int _a_[] = {10, 20, 30};
		int _b_[] = {10, 20, 30};
		int _c_[] = {30, 20, 10};
		ft::list<int> a_(_a_, _a_+3);
		ft::list<int> b_(_b_, _b_+3);
		ft::list<int> c_(_c_, _c_+3);

		if (a_==b_) fs2 << "a and b are equal\n";
		if (b_!=c_) fs2 << "b and c are not equal\n";
		if (b_<c_) fs2 << "b is less than c\n";
		if (c_>b_) fs2 << "c is greater than b\n";
		if (a_<=b_) fs2 << "a is less than or equal to b\n";
		if (a_>=b_) fs2 << "a is greater than or equal to b\n" << std::flush;
	}

	judge();

	{
		std::list<int> foo (3,100);   // three ints with a value of 100
		std::list<int> bar (5,200);   // five ints with a value of 200

		std::swap(foo,bar);

		fs1 << "foo contains:";
		for (std::list<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n';

		fs1 << "bar contains:";
		for (std::list<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::list<int> foo_ (3,100);   // three ints with a value of 100
		ft::list<int> bar_ (5,200);   // five ints with a value of 200

		ft::swap(foo_,bar_);

		fs2 << "foo contains:";
		for (ft::list<int>::iterator it = foo_.begin(); it!=foo_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n';

		fs2 << "bar contains:";
		for (ft::list<int>::iterator it = bar_.begin(); it!=bar_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	std::cout << "\n=== VECTOR ===" << std::endl;
	fs1 << "\n=== VECTOR ===" << std::endl;
	fs2 << "\n=== VECTOR ===" << std::endl;
	{
		// constructors used in the same order as described above:
		std::vector<int> first;                                // empty vector of ints
		std::vector<int> second (4,100);                       // four ints with value 100
		std::vector<int> third (second.begin(),second.end());  // iterating through second
		std::vector<int> fourth (third);                       // a copy of third

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		fs1 << "The contents of fifth are:";
		for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::endl;


		// constructors used in the same order as described above:
		ft::vector<int> first_;                                // empty vector of ints
		ft::vector<int> second_ (4,100);                       // four ints with value 100
		ft::vector<int> third_ (second_.begin(),second_.end());  // iterating through second
		ft::vector<int> fourth_ (third_);                       // a copy of third

		// the iterator constructor can also be used to construct from arrays:
		int myints_[] = {16,2,77,29};
		ft::vector<int> fifth_ (myints_, myints_ + sizeof(myints_) / sizeof(int) );

		fs2 << "The contents of fifth are:";
		for (ft::vector<int>::iterator it = fifth_.begin(); it != fifth_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::endl;
	}

	judge();

	{
		std::vector<int> myvector;
		for (int i=1; i<=5; i++) myvector.push_back(i);

		fs1 << "myvector contains:";
		for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::vector<int> myvector_;
		for (int i=1; i<=5; i++) myvector_.push_back(i);

		fs2 << "myvector contains:";
		for (ft::vector<int>::iterator it = myvector_.begin() ; it != myvector_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> foo (3,0);
		std::vector<int> bar (5,0);

		bar = foo;
		foo = std::vector<int>();

		fs1 << "Size of foo: " << int(foo.size()) << '\n';
		fs1 << "Size of bar: " << int(bar.size()) << '\n' << std::flush;


		ft::vector<int> foo_ (3,0);
		ft::vector<int> bar_ (5,0);

		bar_ = foo_;
		foo_ = ft::vector<int>();

		fs2 << "Size of foo: " << int(foo_.size()) << '\n';
		fs2 << "Size of bar: " << int(bar_.size()) << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector;
		for (int i=1; i<=5; i++) myvector.push_back(i);

		fs1 << "myvector contains:";
		for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::vector<int> myvector_;
		for (int i=1; i<=5; i++) myvector_.push_back(i);

		fs2 << "myvector contains:";
		for (ft::vector<int>::iterator it = myvector_.begin() ; it != myvector_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector (5);  // 5 default-constructed ints

		int i=0;

		std::vector<int>::reverse_iterator rit = myvector.rbegin();
		for (; rit!= myvector.rend(); ++rit)
			*rit = ++i;

		fs1 << "myvector contains:";
		for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::vector<int> myvector_ (5);  // 5 default-constructed ints

		int i_=0;

		ft::vector<int>::reverse_iterator rit_ = myvector_.rbegin();
		for (; rit_!= myvector_.rend(); ++rit_)
			*rit_ = ++i_;

		fs2 << "myvector contains:";
		for (ft::vector<int>::iterator it = myvector_.begin(); it != myvector_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myints;
		fs1 << "0. size: " << myints.size() << '\n';

		for (int i=0; i<10; i++) myints.push_back(i);
		fs1 << "1. size: " << myints.size() << '\n';

		myints.insert (myints.end(),10,100);
		fs1 << "2. size: " << myints.size() << '\n';

		myints.pop_back();
		fs1 << "3. size: " << myints.size() << '\n' << std::flush;


		ft::vector<int> myints_;
		fs2 << "0. size: " << myints_.size() << '\n';

		for (int i=0; i<10; i++) myints_.push_back(i);
		fs2 << "1. size: " << myints_.size() << '\n';

		myints_.insert (myints_.end(),10,100);
		fs2 << "2. size: " << myints_.size() << '\n';

		myints_.pop_back();
		fs2 << "3. size: " << myints_.size() << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector;

		// set some content in the vector:
		for (int i=0; i<100; i++) myvector.push_back(i);

		fs1 << "size: " << myvector.size() << "\n";
		fs1 << "capacity: " << myvector.capacity() << "\n";
		fs1 << "max_size: " << myvector.max_size() << "\n" << std::flush;


		ft::vector<int> myvector_;

		// set some content in the vector:
		for (int i=0; i<100; i++) myvector_.push_back(i);

		fs2 << "size: " << myvector_.size() << "\n";
		fs2 << "capacity: " << myvector_.capacity() << "\n";
		fs2 << "max_size: " << myvector_.max_size() << "\n" << std::flush;
	}

	judge();

	{
		std::vector<int> myvector;

		// set some initial content:
		for (unsigned long i=1;i<10;i++) myvector.push_back(i);

		myvector.resize(5);
		myvector.resize(8,100);
		myvector.resize(12);

		fs1 << "myvector contains:";
		for (unsigned long i=0;i<myvector.size();i++)
			fs1 << ' ' << myvector[i];
		fs1 << '\n' << std::flush;


		ft::vector<int> myvector_;

		// set some initial content:
		for (unsigned long i=1;i<10;i++) myvector_.push_back(i);

		myvector_.resize(5);
		myvector_.resize(8,100);
		myvector_.resize(12);

		fs2 << "myvector contains:";
		for (unsigned long i=0;i<myvector_.size();i++)
			fs2 << ' ' << myvector_[i];
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector;

		// set some content in the vector:
		for (int i=0; i<100; i++) myvector.push_back(i);

		fs1 << "size: " << (int) myvector.size() << '\n';
		fs1 << "capacity: " << (int) myvector.capacity() << '\n';
		fs1 << "max_size: " << (int) myvector.max_size() << '\n' << std::flush;


		ft::vector<int> myvector_;

		// set some content in the vector:
		for (int i=0; i<100; i++) myvector_.push_back(i);

		fs2 << "size: " << (int) myvector_.size() << '\n';
		fs2 << "capacity: " << (int) myvector_.capacity() << '\n';
		fs2 << "max_size: " << (int) myvector_.max_size() << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector;
		int sum (0);

		for (int i=1;i<=10;i++) myvector.push_back(i);

		while (!myvector.empty())
		{
			sum += myvector.back();
			myvector.pop_back();
		}

		fs1 << "total: " << sum << '\n' << std::flush;


		ft::vector<int> myvector_;
		int sum_ (0);

		for (int i=1;i<=10;i++) myvector_.push_back(i);

		while (!myvector_.empty())
		{
			sum_ += myvector_.back();
			myvector_.pop_back();
		}

		fs2 << "total: " << sum_ << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int>::size_type sz;

		std::vector<int> foo;
		sz = foo.capacity();
		fs1 << "making foo grow:\n";
		for (int i=0; i<100; ++i) {
			foo.push_back(i);
			if (sz!=foo.capacity()) {
			sz = foo.capacity();
			fs1 << "capacity changed: " << sz << '\n';
			}
		}

		std::vector<int> bar;
		sz = bar.capacity();
		bar.reserve(100);   // this is the only difference with foo above
		fs1 << "making bar grow:\n";
		for (int i=0; i<100; ++i) {
			bar.push_back(i);
			if (sz!=bar.capacity()) {
			sz = bar.capacity();
			fs1 << "capacity changed: " << sz << '\n' << std::flush;
			}
		}


		ft::vector<int>::size_type sz_;

		ft::vector<int> foo_;
		sz_ = foo_.capacity();
		fs2 << "making foo grow:\n";
		for (int i=0; i<100; ++i) {
			foo_.push_back(i);
			if (sz_!=foo_.capacity()) {
			sz_ = foo_.capacity();
			fs2 << "capacity changed: " << sz_ << '\n';
			}
		}

		ft::vector<int> bar_;
		sz_ = bar_.capacity();
		bar_.reserve(100);   // this is the only difference with foo above
		fs2 << "making bar grow:\n";
		for (int i=0; i<100; ++i) {
			bar_.push_back(i);
			if (sz_!=bar_.capacity()) {
			sz_ = bar_.capacity();
			fs2 << "capacity changed: " << sz_ << '\n' << std::flush;
			}
		}
	}

	judge();

	{
		std::vector<int> myvector (10);   // 10 zero-initialized elements

		std::vector<int>::size_type sz = myvector.size();

		// assign some values:
		for (unsigned i=0; i<sz; i++) myvector[i]=i;

		// reverse vector using operator[]:
		for (unsigned i=0; i<sz/2; i++)
		{
			int temp;
			temp = myvector[sz-1-i];
			myvector[sz-1-i]=myvector[i];
			myvector[i]=temp;
		}

		fs1 << "myvector contains:";
		for (unsigned i=0; i<sz; i++)
			fs1 << ' ' << myvector[i];
		fs1 << '\n' << std::flush;


		ft::vector<int> myvector_ (10);   // 10 zero-initialized elements

		ft::vector<int>::size_type sz_ = myvector_.size();

		// assign some values:
		for (unsigned i=0; i<sz_; i++) myvector_[i]=i;

		// reverse vector using operator[]:
		for (unsigned i=0; i<sz_/2; i++)
		{
			int temp;
			temp = myvector_[sz_-1-i];
			myvector_[sz_-1-i]=myvector_[i];
			myvector_[i]=temp;
		}

		fs2 << "myvector contains:";
		for (unsigned i=0; i<sz_; i++)
			fs2 << ' ' << myvector_[i];
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector (10);   // 10 zero-initialized ints

		// assign some values:
		for (unsigned i=0; i<myvector.size(); i++)
			myvector.at(i)=i;
		
		try
		{
			fs1 << "myvector contains:";
			for (unsigned i=0; i<12; i++)
				fs1 << ' ' << myvector.at(i);
			fs1 << '\n';
		}
		catch(const std::out_of_range& e)
		{
			fs1 << e.what() << '\n' << std::flush;
		}


		ft::vector<int> myvector_ (10);   // 10 zero-initialized ints

		// assign some values:
		for (unsigned i=0; i<myvector_.size(); i++)
			myvector_.at(i)=i;
		
		try
		{
			fs2 << "myvector contains:";
			for (unsigned i=0; i<12; i++)
				fs2 << ' ' << myvector_.at(i);
			fs2 << '\n';
		}
		catch(const std::out_of_range& e)
		{
			fs2 << e.what() << '\n' << std::flush;
		}
		
	}

	judge();

	{
		std::vector<int> myvector;

		myvector.push_back(78);
		myvector.push_back(16);

		// now front equals 78, and back 16

		myvector.front() -= myvector.back();

		fs1 << "myvector.front() is now " << myvector.front() << '\n' << std::flush;


		ft::vector<int> myvector_;

		myvector_.push_back(78);
		myvector_.push_back(16);

		// now front equals 78, and back 16

		myvector_.front() -= myvector_.back();

		fs2 << "myvector.front() is now " << myvector_.front() << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector;

		myvector.push_back(10);

		while (myvector.back() != 0)
		{
			myvector.push_back ( myvector.back() -1 );
		}

		fs1 << "myvector contains:";
		for (unsigned i=0; i<myvector.size() ; i++)
			fs1 << ' ' << myvector[i];
		fs1 << '\n' << std::flush;


		ft::vector<int> myvector_;

		myvector_.push_back(10);

		while (myvector_.back() != 0)
		{
			myvector_.push_back ( myvector_.back() -1 );
		}

		fs2 << "myvector contains:";
		for (unsigned i=0; i<myvector_.size() ; i++)
			fs2 << ' ' << myvector_[i];
		fs2 << '\n' << std::flush;
	} 

	judge();

	{
		std::vector<int> first;
		std::vector<int> second;
		std::vector<int> third;

		first.assign (7,100);             // 7 ints with a value of 100

		std::vector<int>::iterator it;
		it=first.begin()+1;

		second.assign (it,first.end()-1); // the 5 central values of first

		int myints[] = {1776,7,4};
		third.assign (myints,myints+3);   // assigning from array.

		fs1 << "Size of first: " << int (first.size()) << '\n';
		fs1 << "Size of second: " << int (second.size()) << '\n';
		fs1 << "Size of third: " << int (third.size()) << '\n' << std::flush;



		ft::vector<int> first_;
		ft::vector<int> second_;
		ft::vector<int> third_;

		first_.assign (7,100);             // 7 ints with a value of 100

		ft::vector<int>::iterator it_;
		it_=first_.begin()+1;

		second_.assign (it_,first_.end()-1); // the 5 central values of first_

		int myints_[] = {1776,7,4};
		third_.assign (myints_,myints_+3);   // assigning from array.

		fs2 << "Size of first: " << int (first_.size()) << '\n';
		fs2 << "Size of second: " << int (second_.size()) << '\n';
		fs2 << "Size of third: " << int (third_.size()) << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector;

		fs1 << "Please enter some integers (enter 0 to end):\n";

		for (int i = 0; i < 42; i++)
			myvector.push_back (i);

		fs1 << "myvector stores " << int(myvector.size()) << " numbers.\n" << std::flush;


		ft::vector<int> myvector_;

		fs2 << "Please enter some integers (enter 0 to end):\n";

		for (int i = 0; i < 42; i++)
			myvector_.push_back (i);

		fs2 << "myvector stores " << int(myvector_.size()) << " numbers.\n" << std::flush;
	}

	judge();

	{
		std::vector<int> myvector;
		int sum (0);
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);

		while (!myvector.empty())
		{
			sum+=myvector.back();
			myvector.pop_back();
		}

		fs1 << "The elements of myvector add up to " << sum << '\n' << std::flush;


		ft::vector<int> myvector_;
		int sum_ (0);
		myvector_.push_back (100);
		myvector_.push_back (200);
		myvector_.push_back (300);

		while (!myvector_.empty())
		{
			sum_+=myvector_.back();
			myvector_.pop_back();
		}

		fs2 << "The elements of myvector add up to " << sum_ << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector (3,100);
		std::vector<int>::iterator it;
		std::vector<int>::iterator it_tmp;

		it_tmp = it = myvector.begin();
		it = myvector.insert ( it , 200 );

		myvector.insert (it,2,300);

		// "it" no longer valid, get a new one:
		it = myvector.begin();

		std::vector<int> anothervector (2,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());

		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);

		fs1 << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::vector<int> myvector_ (3,100);
		ft::vector<int>::iterator it_;
		ft::vector<int>::iterator it__tmp;

		it__tmp = it_ = myvector_.begin();
		it_ = myvector_.insert ( it_ , 200 );

		myvector_.insert (it_,2,300);

		// "it_" no longer valid, get a new one:
		it_ = myvector_.begin();

		ft::vector<int> anothervector_ (2,400);
		myvector_.insert (it_+2,anothervector_.begin(),anothervector_.end());

		int myarray_ [] = { 501,502,503 };
		myvector_.insert (myvector_.begin(), myarray_, myarray_+3);

		fs2 << "myvector contains:";
		for (it_=myvector_.begin(); it_<myvector_.end(); it_++)
			fs2 << ' ' << *it_;
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector;

		// set some values (from 1 to 10)
		for (int i=1; i<=10; i++) myvector.push_back(i);

		// erase the 6th element
		myvector.erase (myvector.begin()+5);

		// erase the first 3 elements:
		myvector.erase (myvector.begin(),myvector.begin()+3);

		fs1 << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
			fs1 << ' ' << myvector[i];
		fs1 << '\n' << std::flush;


		ft::vector<int> myvector_;

		// set some values (from 1 to 10)
		for (int i=1; i<=10; i++) myvector_.push_back(i);

		// erase the 6th element
		myvector_.erase (myvector_.begin()+5);

		// erase the first 3 elements:
		myvector_.erase (myvector_.begin(),myvector_.begin()+3);

		fs2 << "myvector contains:";
		for (unsigned i=0; i<myvector_.size(); ++i)
			fs2 << ' ' << myvector_[i];
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> foo (3,100);   // three ints with a value of 100
		std::vector<int> bar (5,200);   // five ints with a value of 200

		foo.swap(bar);

		fs1 << "foo contains:";
		for (unsigned i=0; i<foo.size(); i++)
			fs1 << ' ' << foo[i];
		fs1 << '\n';

		fs1 << "bar contains:";
		for (unsigned i=0; i<bar.size(); i++)
			fs1 << ' ' << bar[i];
		fs1 << '\n' << std::flush;


		ft::vector<int> foo_ (3,100);   // three ints with a value of 100
		ft::vector<int> bar_ (5,200);   // five ints with a value of 200

		foo_.swap(bar_);

		fs2 << "foo contains:";
		for (unsigned i=0; i<foo_.size(); i++)
			fs2 << ' ' << foo_[i];
		fs2 << '\n';

		fs2 << "bar contains:";
		for (unsigned i=0; i<bar_.size(); i++)
			fs2 << ' ' << bar_[i];
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> myvector;
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);

		fs1 << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			fs1 << ' ' << myvector[i];
		fs1 << '\n';

		myvector.clear();
		myvector.push_back (1101);
		myvector.push_back (2202);

		fs1 << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			fs1 << ' ' << myvector[i];
		fs1 << '\n' << std::flush;


		ft::vector<int> myvector_;
		myvector_.push_back (100);
		myvector_.push_back (200);
		myvector_.push_back (300);

		fs2 << "myvector contains:";
		for (unsigned i=0; i<myvector_.size(); i++)
			fs2 << ' ' << myvector_[i];
		fs2 << '\n';

		myvector_.clear();
		myvector_.push_back (1101);
		myvector_.push_back (2202);

		fs2 << "myvector contains:";
		for (unsigned i=0; i<myvector_.size(); i++)
			fs2 << ' ' << myvector_[i];
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::vector<int> foo (3,100);   // three ints with a value of 100
		std::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) fs1 << "foo and bar are equal\n";
		if (foo!=bar) fs1 << "foo and bar are not equal\n";
		if (foo< bar) fs1 << "foo is less than bar\n";
		if (foo> bar) fs1 << "foo is greater than bar\n";
		if (foo<=bar) fs1 << "foo is less than or equal to bar\n";
		if (foo>=bar) fs1 << "foo is greater than or equal to bar\n" << std::flush;


		ft::vector<int> foo_ (3,100);   // three ints with a value of 100
		ft::vector<int> bar_ (2,200);   // two ints with a value of 200

		if (foo_==bar_) fs2 << "foo and bar are equal\n";
		if (foo_!=bar_) fs2 << "foo and bar are not equal\n";
		if (foo_< bar_) fs2 << "foo is less than bar\n";
		if (foo_> bar_) fs2 << "foo is greater than bar\n";
		if (foo_<=bar_) fs2 << "foo is less than or equal to bar\n";
		if (foo_>=bar_) fs2 << "foo is greater than or equal to bar\n" << std::flush;
	}

	judge();

	{
		std::vector<int> foo (3,100);   // three ints with a value of 100
		std::vector<int> bar (5,200);   // five ints with a value of 200

		foo.swap(bar);

		fs1 << "foo contains:";
		for (std::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n';

		fs1 << "bar contains:";
		for (std::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			fs1 << ' ' << *it;
		fs1 << '\n' << std::flush;


		ft::vector<int> foo_ (3,100);   // three ints with a value of 100
		ft::vector<int> bar_ (5,200);   // five ints with a value of 200

		foo_.swap(bar_);

		fs2 << "foo contains:";
		for (ft::vector<int>::iterator it = foo_.begin(); it!=foo_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n';

		fs2 << "bar contains:";
		for (ft::vector<int>::iterator it = bar_.begin(); it!=bar_.end(); ++it)
			fs2 << ' ' << *it;
		fs2 << '\n' << std::flush;
	}

	judge();

	std::cout << "\n=== MAP ===" << std::endl;
	fs1 << "\n=== MAP ===" << std::endl;
	fs2 << "\n=== MAP ===" << std::endl;
	{
		
	}

	judge();

	std::cout << "\n=== STACK ===" << std::endl;
	fs1 << "\n=== STACK ===" << std::endl;
	fs2 << "\n=== STACK ===" << std::endl;
	{
		std::deque<int> mydeque (3,100);          // deque with 3 elements
		std::vector<int> myvector (2,200);        // vector with 2 elements

		std::stack<int> first;                    // empty stack
		std::stack<int> second (mydeque);         // stack initialized to copy of deque

		std::stack<int,std::vector<int> > third;  // empty stack using vector
		std::stack<int,std::vector<int> > fourth (myvector);

		fs1 << "size of first: " << first.size() << '\n';
		fs1 << "size of second: " << second.size() << '\n';
		fs1 << "size of third: " << third.size() << '\n';
		fs1 << "size of fourth: " << fourth.size() << '\n' << std::flush;


		ft::vector<int> mydeque_ (3,100);          // deque with 3 elements
		std::vector<int> myvector_ (2,200);        // vector with 2 elements

		ft::stack<int> first_;                    // empty stack
		ft::stack<int> second_ (mydeque_);         // stack initialized to copy of deque

		ft::stack<int,std::vector<int> > third_;  // empty stack using vector
		ft::stack<int,std::vector<int> > fourth_ (myvector_);

		fs2 << "size of first: " << first_.size() << '\n';
		fs2 << "size of second: " << second_.size() << '\n';
		fs2 << "size of third: " << third_.size() << '\n';
		fs2 << "size of fourth: " << fourth_.size() << '\n' << std::flush;
	}

	judge();

	{
		std::stack<int> mystack;
		int sum (0);

		for (int i=1;i<=10;i++) mystack.push(i);

		while (!mystack.empty())
		{
			sum += mystack.top();
			mystack.pop();
		}

		fs1 << "total: " << sum << '\n' << std::flush;


		ft::stack<int> mystack_;
		int sum_ (0);

		for (int i=1;i<=10;i++) mystack_.push(i);

		while (!mystack_.empty())
		{
			sum_ += mystack_.top();
			mystack_.pop();
		}

		fs2 << "total: " << sum_ << '\n' << std::flush;
	}

	judge();

	{
		std::stack<int> myints;
		fs1 << "0. size: " << myints.size() << '\n';

		for (int i=0; i<5; i++) myints.push(i);
		fs1 << "1. size: " << myints.size() << '\n';

		myints.pop();
		fs1 << "2. size: " << myints.size() << '\n' << std::flush;


		ft::stack<int> myints_;
		fs2 << "0. size: " << myints_.size() << '\n';

		for (int i=0; i<5; i++) myints_.push(i);
		fs2 << "1. size: " << myints_.size() << '\n';

		myints_.pop();
		fs2 << "2. size: " << myints_.size() << '\n' << std::flush;
	}

	judge();

	{
		std::stack<int> mystack;

		mystack.push(10);
		mystack.push(20);

		mystack.top() -= 5;

		fs1 << "mystack.top() is now " << mystack.top() << '\n' << std::flush;


		ft::stack<int> mystack_;

		mystack_.push(10);
		mystack_.push(20);

		mystack_.top() -= 5;

		fs2 << "mystack.top() is now " << mystack_.top() << '\n' << std::flush;
	}

	judge();

	{
		std::stack<int> mystack;

		for (int i=0; i<5; ++i) mystack.push(i);

		fs1 << "Popping out elements...";
		while (!mystack.empty())
		{
			fs1 << ' ' << mystack.top();
			mystack.pop();
		}
		fs1 << '\n' << std::flush;


		ft::stack<int> mystack_;

		for (int i=0; i<5; ++i) mystack_.push(i);

		fs2 << "Popping out elements...";
		while (!mystack_.empty())
		{
			fs2 << ' ' << mystack_.top();
			mystack_.pop();
		}
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::stack<int> mystack;

		for (int i=0; i<5; ++i) mystack.push(i);

		fs1 << "Popping out elements...";
		while (!mystack.empty())
		{
			fs1 << ' ' << mystack.top();
			mystack.pop();
		}
		fs1 << '\n' << std::flush;


		ft::stack<int> mystack_;

		for (int i=0; i<5; ++i) mystack_.push(i);

		fs2 << "Popping out elements...";
		while (!mystack_.empty())
		{
			fs2 << ' ' << mystack_.top();
			mystack_.pop();
		}
		fs2 << '\n' << std::flush;
	}

	judge();

	{
		std::stack<int> foo;   // three ints with a value of 100
		for (int i = 0; i < 3; i++)foo.push(100);
		std::stack<int> bar;   // two ints with a value of 200
		for (int i = 0; i < 2; i++)bar.push(200);
		if (foo==bar) fs1 << "foo and bar are equal\n";
		if (foo!=bar) fs1 << "foo and bar are not equal\n";
		if (foo< bar) fs1 << "foo is less than bar\n";
		if (foo> bar) fs1 << "foo is greater than bar\n";
		if (foo<=bar) fs1 << "foo is less than or equal to bar\n";
		if (foo>=bar) fs1 << "foo is greater than or equal to bar\n" << std::flush;


		ft::stack<int> foo_;   // three ints with a value of 100
		for (int i = 0; i < 3; i++)foo_.push(100);
		ft::stack<int> bar_;   // two ints with a value of 200
		for (int i = 0; i < 2; i++)bar_.push(200);
		if (foo_==bar_) fs2 << "foo and bar are equal\n";
		if (foo_!=bar_) fs2 << "foo and bar are not equal\n";
		if (foo_< bar_) fs2 << "foo is less than bar\n";
		if (foo_> bar_) fs2 << "foo is greater than bar\n";
		if (foo_<=bar_) fs2 << "foo is less than or equal to bar\n";
		if (foo_>=bar_) fs2 << "foo is greater than or equal to bar\n" << std::flush;
	}

	std::cout << "\n=== QUEUE ===" << std::endl;
	fs1 << "\n=== QUEUE ===" << std::endl;
	fs2 << "\n=== QUEUE ===" << std::endl;
	{
		std::deque<int> mydeque (3,100);          // deque with 3 elements
		std::vector<int> myvector (2,200);        // vector with 2 elements

		std::queue<int> first;                    // empty queue
		std::queue<int> second (mydeque);         // queue initialized to copy of deque

		std::queue<int,std::vector<int> > third;  // empty queue using vector
		std::queue<int,std::vector<int> > fourth (myvector);

		fs1 << "size of first: " << first.size() << '\n';
		fs1 << "size of second: " << second.size() << '\n';
		fs1 << "size of third: " << third.size() << '\n';
		fs1 << "size of fourth: " << fourth.size() << '\n' << std::flush;


		ft::list<int> mydeque_ (3,100);          // deque with 3 elements
		std::vector<int> myvector_ (2,200);        // vector with 2 elements

		ft::queue<int> first_;                    // empty queue
		ft::queue<int> second_ (mydeque_);         // queue initialized to copy of deque

		ft::queue<int,std::vector<int> > third_;  // empty queue using vector
		ft::queue<int,std::vector<int> > fourth_ (myvector_);

		fs2 << "size of first: " << first_.size() << '\n';
		fs2 << "size of second: " << second_.size() << '\n';
		fs2 << "size of third: " << third_.size() << '\n';
		fs2 << "size of fourth: " << fourth_.size() << '\n' << std::flush;
	}

	judge();

	{
		std::queue<int> myqueue;
		int sum (0);

		for (int i=1;i<=10;i++) myqueue.push(i);

		while (!myqueue.empty())
		{
			sum += myqueue.front();
			myqueue.pop();
		}

		fs1 << "total: " << sum << '\n' << std::flush;


		ft::queue<int> myqueue_;
		int sum_ (0);

		for (int i=1;i<=10;i++) myqueue_.push(i);

		while (!myqueue_.empty())
		{
			sum_ += myqueue_.front();
			myqueue_.pop();
		}

		fs2 << "total: " << sum_ << '\n' << std::flush;
	}

	judge();

	{
		std::queue<int> myints;
		fs1 << "0. size: " << myints.size() << '\n';

		for (int i=0; i<5; i++) myints.push(i);
		fs1 << "1. size: " << myints.size() << '\n';

		myints.pop();
		fs1 << "2. size: " << myints.size() << '\n' << std::flush;


		ft::queue<int> myints_;
		fs2 << "0. size: " << myints_.size() << '\n';

		for (int i=0; i<5; i++) myints_.push(i);
		fs2 << "1. size: " << myints_.size() << '\n';

		myints_.pop();
		fs2 << "2. size: " << myints_.size() << '\n' << std::flush;
	}

	judge();

	{
		std::queue<int> myqueue;

		myqueue.push(77);
		myqueue.push(16);

		myqueue.front() -= myqueue.back();    // 77-16=61

		fs1 << "myqueue.front() is now " << myqueue.front() << '\n' << std::flush;


		ft::queue<int> myqueue_;

		myqueue_.push(77);
		myqueue_.push(16);

		myqueue_.front() -= myqueue_.back();    // 77-16=61

		fs2<< "myqueue.front() is now " << myqueue_.front() << '\n' << std::flush;
	}

	judge();

	{
		std::queue<int> myqueue;

		myqueue.push(12);
		myqueue.push(75);   // this is now the back

		myqueue.back() -= myqueue.front();

		fs1 << "myqueue.back() is now " << myqueue.back() << '\n' << std::flush;


		ft::queue<int> myqueue_;

		myqueue_.push(12);
		myqueue_.push(75);   // this is now the back

		myqueue_.back() -= myqueue_.front();

		fs2 << "myqueue.back() is now " << myqueue_.back() << '\n' << std::flush;
	}

	judge();

	{
		std::queue<int> myqueue;

		fs1 << "Please enter some integers (enter 0 to end):\n";

		for (int i = 0; i < 42; i++)
			myqueue.push(i);

		fs1 << "myqueue contains: ";
		while (!myqueue.empty())
		{
			fs1 << ' ' << myqueue.front();
			myqueue.pop();
		}
		fs1 << '\n' << std::flush;


		ft::queue<int> myqueue_;

		fs2 << "Please enter some integers (enter 0 to end):\n";

		for (int i = 0; i < 42; i++)
			myqueue_.push(i);

		fs2 << "myqueue contains: ";
		while (!myqueue_.empty())
		{
			fs2 << ' ' << myqueue_.front();
			myqueue_.pop();
		}
		fs2 << '\n' << std::flush;
	}
	
	judge();

	{
		std::queue<int> foo;   // three ints with a value of 100
		for (int i = 0; i < 3; i++)foo.push(100);
		std::queue<int> bar;   // two ints with a value of 200
		for (int i = 0; i < 2; i++)bar.push(200);
		if (foo==bar) fs1 << "foo and bar are equal\n";
		if (foo!=bar) fs1 << "foo and bar are not equal\n";
		if (foo< bar) fs1 << "foo is less than bar\n";
		if (foo> bar) fs1 << "foo is greater than bar\n";
		if (foo<=bar) fs1 << "foo is less than or equal to bar\n";
		if (foo>=bar) fs1 << "foo is greater than or equal to bar\n" << std::flush;


		ft::queue<int> foo_;   // three ints with a value of 100
		for (int i = 0; i < 3; i++)foo_.push(100);
		ft::queue<int> bar_;   // two ints with a value of 200
		for (int i = 0; i < 2; i++)bar_.push(200);
		if (foo_==bar_) fs2 << "foo and bar are equal\n";
		if (foo_!=bar_) fs2 << "foo and bar are not equal\n";
		if (foo_< bar_) fs2 << "foo is less than bar\n";
		if (foo_> bar_) fs2 << "foo is greater than bar\n";
		if (foo_<=bar_) fs2 << "foo is less than or equal to bar\n";
		if (foo_>=bar_) fs2 << "foo is greater than or equal to bar\n" << std::flush;
	}

	judge();

	std::cout << std::endl;
	fs1.close();
	fs2.close();
	// system("rm 1 2");
	std::cout << "=== LEAK ===" << std::endl;
	if (system("leaks a.out > /dev/null") == 0)
		std::cout << "\033[32m[OK] \033[m\n";
	else
		std::cout << "\033[31m[KO] \033[m\n";
    return(EXIT_SUCCESS);
}
