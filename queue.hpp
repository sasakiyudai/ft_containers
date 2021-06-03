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

		public:
			explicit queue (const container_type& ctnr = container_type()):ctnr(ctnr)
			{
			}

			bool empty() const
			{
				return ctnr.empty();
			}

			size_type size() const
			{
				return ctnr.size();
			}

			value_type& front()
			{
				return ctnr.front();
			}

			const value_type& front() const
			{
				return ctnr.front();
			}

			value_type& back()
			{
				return ctnr.back();
			}

			const value_type& back() const
			{
				return ctnr.back();
			}

			void push (const value_type& val)
			{
				ctnr.push_back(val);
			}

			void pop()
			{
				ctnr.pop_front();
			}

			template <class T_, class Container_>
			friend bool operator== (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

			template <class T_, class Container_>
			friend bool operator!= (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

			template <class T_, class Container_>
			friend bool operator< (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

			template <class T_, class Container_>
			friend bool operator> (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

			template <class T_, class Container_>
			friend bool operator<= (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

			template <class T_, class Container_>
			friend bool operator>= (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);
	};

	template <class T, class Container>
	bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return lhs.ctnr == rhs.ctnr;
	}

	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return lhs.ctnr != rhs.ctnr;
	}

	template <class T, class Container>
	bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return lhs.ctnr < rhs.ctnr;
	}

	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return lhs.ctnr <= rhs.ctnr;
	}

	template <class T, class Container>
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return lhs.ctnr > rhs.ctnr;
	}

	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return lhs.ctnr >= rhs.ctnr;
	}
}

#endif
