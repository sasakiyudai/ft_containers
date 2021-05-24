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
		fs1 << "3. size: " << myints.size() << '\n' << std::endl << std::flush;


		ft::list<int> myints_;
		fs2 << "0. size: " << myints_.size() << '\n';
		for (int i=0; i<10; i++) myints_.push_back(i);
		fs2 << "1. size: " << myints_.size() << '\n';
		myints_.insert (myints_.begin(),10,100);
		fs2 << "2. size: " << myints_.size() << '\n';
		myints_.pop_back();
		fs2 << "3. size: " << myints_.size() << '\n' << std::endl << std::flush;
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

	}


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
