#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> // allocator
#include <iostream> // debug
#include <limits> // max
#include "util.hpp"

namespace ft
{
	template <class T>
	class vector_iterator;

	template <class T>
	class const_vector_iterator;

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef vector_iterator<T> iterator;
			typedef const_vector_iterator<T> const_iterator;
			typedef reverse__iterator<iterator> reverse_iterator;
			typedef reverse__iterator<const_iterator> const_reverse_iterator;
			typedef typename allocator_type::difference_type difference_type;
			typedef typename allocator_type::size_type size_type;
		
		private:
			pointer head;
			size_type len;
			size_type cap;
			allocator_type allocator;
		
		public:
			explicit vector (const allocator_type& alloc = allocator_type())
			{
				head = NULL;
				len = cap = 0;
				allocator = alloc;
			}

			explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
			{
				head = NULL;
				len = cap = 0;
				allocator = alloc;
				insert(begin(), n, val);
			}

			template <class InputIterator>
        	 vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type())
			{
				head = NULL;
				len = cap = 0;
				allocator = alloc;
				insert(begin(), first, last);
			}

			vector (const vector& x)
			{
				head = NULL;
				len = cap = 0;
				allocator = x.allocator;
				insert(begin(), x.begin(), x.end());
			}

			~vector()
			{
				for (size_type i = 0; i < len; i++)
					allocator.destroy(&head[i]);
				allocator.deallocate(head, cap);
			}

			vector &operator=(const vector& x)
			{
				clear();
				assign(x.begin(), x.end());
				return *this;
			}

			iterator begin()
			{
				return iterator(head);
			}

			const_iterator begin() const
			{
				return const_iterator(head);
			}

			iterator end()
			{
				return iterator(head + len);
			}
			
			const_iterator end() const
			{
				return const_iterator(head + len);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			size_type size() const
			{
				return len;
			}

			size_type max_size() const
			{
				// return std::numeric_limits<difference_type>::max() / sizeof(T);
				return allocator.max_size();
			}

			void resize (size_type n, value_type val = value_type())
			{
				if (n < len)
					erase(begin() + n, end());
				else
					insert(end(), n - len, val);
			}

			size_type capacity() const
			{
				return cap;
			}

			bool empty() const
			{
				return len == 0;
			}

			void reserve (size_type n)
			{
				if (n == 0 || n <= cap)
					return ;
				value_type *new_head = allocator.allocate(n);
				for (size_type i = 0; i < len; i++)
				{
					allocator.construct(new_head + i, head[i]);
					allocator.destroy(head + i);
				}
				allocator.deallocate(head, cap);
				cap = n;
				head = new_head;
			}

			reference operator[] (size_type n)
			{
				return head[n];
			}

			const_reference operator[] (size_type n) const
			{
				return head[n];
			}

			reference at (size_type n)
			{
				if (n >= len)
					throw std::out_of_range("vector");
				return head[n];
			}

			const_reference at (size_type n) const
			{
				if (n >= len)
					throw std::out_of_range("vector");
				return head[n];
			}

			reference front()
			{
				return head[0];
			}
			
			const_reference front() const
			{
				return head[0];
			}

			reference back()
			{
				return head[len - 1];
			}

			const_reference back() const
			{
				return head[len - 1];
			}

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last)
			{
				clear();
				insert(begin(), first, last);
			}

			void assign (size_type n, const value_type& val)
			{
				clear();
				insert(begin(), n, val);
			}

			void push_back (const value_type& val)
			{
				if (size() + 1 > capacity())
				{
					size_type _cap = capacity();
					if (_cap == 0)
						_cap = 1;
					else
						_cap *= 2;
					reserve(_cap);
				}
				insert(end(), val);
			}

			void pop_back()
			{
				erase(end() - 1);
			}

			iterator insert (iterator position, const value_type& val)
			{
				iterator old_head = begin();
				size_t offset = 0;

				insert(position, 1, val);
				offset = begin() - old_head;
				return position + offset;
			}

    		void insert (iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				difference_type first_id = position.get_elem() - head;
				reserve(len + n);
				for (difference_type i = len - 1; i >= first_id; i--)
				{
					allocator.construct(&head[i + n], head[i]);
					allocator.destroy(&head[i]);
				}
				for (size_type i = 0; i < n; i++)
					allocator.construct(&head[first_id + i], val);
				len += n;
			}

			template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
    		insert (iterator position, InputIterator first, InputIterator last)
			{
				difference_type end_at = position.get_elem() - head;
				InputIterator ite = first;
				difference_type n = distance(first, last);
				if (n == 0)
					return ;
				reserve(len + n);
				for (difference_type i = len - 1; i >= end_at; i--)
				{
					allocator.construct(&head[i + n], head[i]);
					allocator.destroy(&head[i]);
				}
				for (difference_type i = 0; i < n; i++)
					allocator.construct(&head[end_at + i], *ite++);
				len += n;
			}

			iterator erase (iterator position)
			{
				return erase(position, position + 1);
			}

			iterator erase (iterator first, iterator last)
			{
				size_type n = last - first;
				if (n <= 0)
					return last;
				size_type first_id = first.get_elem() - head;
				for (size_type i = 0; i < n; i++)
					allocator.destroy(&head[first_id + i]);
				for (size_type i = first_id + n; i < len; i++)
				{
					allocator.construct(&head[i - n], head[i]);
					allocator.destroy(&head[i]);
				}
				len -= n;
				return first;
			}

			void swap (vector& x)
			{
				std::swap(head, x.head);
				std::swap(len, x.len);
				std::swap(cap, x.cap);
				std::swap(allocator, x.allocator);
			}

			void clear()
			{
				erase(begin(), end());
			}
	};

	template <class T, class Alloc>
  	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
			return equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}

	template <class T, class Alloc>
  	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
  	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
  	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class T, class Alloc>
  	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Alloc>
  	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

	template <class T>
	class vector_iterator
	{
		public:
			typedef random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;

		private:
			pointer elem;
		
		public:
			vector_iterator():elem(NULL) {}
			vector_iterator(pointer elem):elem(elem) {}
			vector_iterator(const vector_iterator &other):elem(other.elem) {}

			~vector_iterator() {}

			pointer get_elem()
			{
				return elem;
			}

			vector_iterator<T> &operator=(const vector_iterator<T> &other)
			{
				elem = other.elem;
				return *this;
			}

			vector_iterator<T> &operator++()
			{
				++elem;
				return *this;
			}

			vector_iterator<T> operator++(int)
			{
				vector_iterator<T> ret = *this;
				++*this;
				return ret;
			}

			vector_iterator<T> &operator--()
			{
				--elem;
				return *this;
			}

			vector_iterator<T> operator--(int)
			{
				 vector_iterator<T> ret = *this;
				--*this;
				return ret;
			}

			reference operator*() const
			{
				return *elem;
			}

			pointer operator->() const
			{
				return elem;
			}

			vector_iterator<T> &operator+=(difference_type delta)
			{
				elem += delta;
				return *this;
			}

			vector_iterator<T> &operator-=(difference_type delta)
			{
				elem -= delta;
				return *this;
			}

			reference operator[](difference_type n) const
			{
				return *(elem + n);
			}

			friend void swap(const vector_iterator &a, const vector_iterator &b)
			{
				vector_iterator tmp(a);
				a = b;
				b = tmp;
			}

			friend bool operator==(const vector_iterator &lhs, const vector_iterator &rhs)
			{
				return lhs.elem == rhs.elem;
			}

			friend bool operator!=(const vector_iterator &lhs, const vector_iterator &rhs)
			{
				return !(lhs.elem == rhs.elem);
			}

			friend bool operator<(const vector_iterator &lhs, const vector_iterator &rhs)
			{
				return lhs.elem < rhs.elem;
			}

			friend bool operator>(const vector_iterator &lhs, const vector_iterator &rhs)
			{
				return rhs.elem < lhs.elem;
			}

			friend bool operator<=(const vector_iterator &lhs, const vector_iterator &rhs)
			{
				return !(lhs.elem > rhs.elem);
			}

			friend bool operator>=(const vector_iterator &lhs, const vector_iterator &rhs)
			{
				return !(lhs.elem < rhs.elem);
			}

			friend ptrdiff_t operator-(const vector_iterator<T> &lhs, const vector_iterator<T> &rhs)
			{
				return lhs.elem - rhs.elem;
			}
	};

	template <class T>
	vector_iterator<T> operator+(const vector_iterator<T> &ite, size_t delta)
	{
		vector_iterator<T> ret = ite;
		return ret += delta;
	}

	template <class T>
	vector_iterator<T> operator+(size_t delta, const vector_iterator<T> &ite)
	{
		return ite + delta;
	}

	template <class T>
	vector_iterator<T> operator-(const vector_iterator<T> &ite, size_t delta)
	{
		vector_iterator<T> ret = ite;
		return ret -= delta;
	}

	template <class T>
	class const_vector_iterator
	{
		public:
			typedef random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef const T* pointer;
			typedef const T& reference;

		private:
			pointer elem;
		
		public:
			const_vector_iterator():elem(NULL) {}
			const_vector_iterator(pointer elem):elem(elem) {}
			const_vector_iterator(const const_vector_iterator &other):elem(other.elem) {}

			~const_vector_iterator() {}

			pointer get_elem()
			{
				return elem;
			}

			const_vector_iterator<T> &operator=(const const_vector_iterator<T> &other)
			{
				elem = other.elem;
				return *this;
			}

			const_vector_iterator<T> &operator++()
			{
				++elem;
				return *this;
			}

			const_vector_iterator<T> operator++(int)
			{
				const_vector_iterator<T> ret = *this;
				++*this;
				return ret;
			}

			const_vector_iterator<T> &operator--()
			{
				--elem;
				return *this;
			}

			const_vector_iterator<T> operator--(int)
			{
				 const_vector_iterator<T> ret = *this;
				--*this;
				return ret;
			}

			reference operator*() const
			{
				return *elem;
			}

			pointer operator->() const
			{
				return elem;
			}

			const_vector_iterator<T> &operator+=(difference_type delta)
			{
				elem += delta;
				return *this;
			}

			const_vector_iterator<T> &operator-=(difference_type delta)
			{
				elem -= delta;
				return *this;
			}

			reference operator[](difference_type n) const
			{
				return *(elem + n);
			}

			friend void swap(const const_vector_iterator &a, const const_vector_iterator &b)
			{
				const_vector_iterator tmp(a);
				a = b;
				b = tmp;
			}

			friend bool operator==(const const_vector_iterator &lhs, const const_vector_iterator &rhs)
			{
				return lhs.elem == rhs.elem;
			}

			friend bool operator!=(const const_vector_iterator &lhs, const const_vector_iterator &rhs)
			{
				return !(lhs.elem == rhs.elem);
			}

			friend bool operator<(const const_vector_iterator &lhs, const const_vector_iterator &rhs)
			{
				return lhs.elem < rhs.elem;
			}

			friend bool operator>(const const_vector_iterator &lhs, const const_vector_iterator &rhs)
			{
				return rhs.elem < lhs.elem;
			}

			friend bool operator<=(const const_vector_iterator &lhs, const const_vector_iterator &rhs)
			{
				return !(lhs.elem > rhs.elem);
			}

			friend bool operator>=(const const_vector_iterator &lhs, const const_vector_iterator &rhs)
			{
				return !(lhs.elem < rhs.elem);
			}
	};
}

#endif