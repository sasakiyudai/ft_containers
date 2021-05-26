#include <memory> // allocator
#include <iostream> // debug
#include <limits> // max
#include "util.hpp"

namespace ft
{
	template <class T, class Allocatorr = std::allocator<T> >
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
				// insert(begin(), n, val);
			}

			template <class InputIterator>
        	 vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type())
			{
				head = NULL;
				len = cap = 0;
				allocator = alloc;
				// insert(begin(), first, last);
			}

			vector (const vector& x)
			{
				head = NULL;
				len = cap = 0;
				allocator = alloc;
				// insert(begin(), x.begin(), x.end());
			}

			~vector()
			{
				for (size_type i = 0; i < len; i++)
					allocator.destroy(&head[i]);
				allocator.deallocate(head, cap);
			}

			vector &operator=(const list& x)
			{
				// clear();
				// assign(x.begin(), x.end());
				return *this;
			}

			iterator
	};

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
			vector_iterator(pointer *elem):elem(elem) {}
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

			vector_iterator<T> &operator++(int)
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
	};
}