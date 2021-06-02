#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include <functional>
#include "util.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			class value_compare : std::binary_function<value_type,value_type,bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			typedef Alloc allocator_type;
			typedef allocator_type::reference reference;
			typedef allocator_type::const_reference const_reference;
			typedef allocator_type::pointer pointer;
			typedef allocator_type::const_pointer const_pointer;
			typedef iterator;
	};

}

#endif
