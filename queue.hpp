#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace ft
{
	template <class T, class Container = list<T> >
	class queue
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

		private:
			container_type ctnr;
	};
}

#endif
