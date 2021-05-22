#include <memory> // allocator
#include <iostream> // debug
#include <limits> // max
#include "util.hpp"

namespace ft
{
	template <class T>
	struct list_node
	{
		list_node *prev;
		list_node *next;
		T value;

		list_node(list_node *prev, list_node *next):prev(prev), next(next), value() {}
	};

	template <class T>
	class list_iterator;

	template <class T, class Allocator = std::allocator<T> >
	class list
	{
		public:
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef list_iterator<T> iterator;
			// typedef list_iterator<const T> const_iterator;
			typedef typename allocator_type::difference_type difference_type;
			typedef typename allocator_type::size_type size_type;
		
		private:
			typedef list_node<T> list_node;

			list_node *head;
			list_node *tail;
			allocator_type allocator;
			size_type len;

		public:
			explicit list(const allocator_type& alloc = allocator_type()):len(0)
			{
				head = tail = new list_node(NULL, NULL);
				allocator = alloc;
			}
			explicit list (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()):len(0)
			{
				head = tail = new list_node(NULL, NULL);
				allocator = alloc;
				// assign(n, val);
			}
			template <class InputIterator>
  			list (InputIterator first, InputIterator last,
        		const allocator_type& alloc = allocator_type()):len(0)
			{
				head = tail = new list_node(NULL, NULL);
				allocator = alloc;
				// assign(first, last);
			}
			list (const list& x):len(0)
			{
				head = tail = new list_node(NULL, NULL);
				allocator = x.allocator;
				// assign(x.begin(), x.end());
			}

			~list ()
			{
				erase(begin(), end());
				delete tail;
			}

			list &operator=(const list& x)
			{
				// clear();
				// assign(x.begin(), x.end());
				return *this;
			}

			iterator begin()
			{
				return iterator(head);
			}

			/* const_iterator begin() const
			{

			} */

			iterator end()
			{
				return iterator(tail);
			}

			/* const_iterator end() const
			{

			} */

			/* todo : reverse */

			bool empty() const
			{
				return len == 0;
			}

			size_type size() const
			{
				return len;
			}

			size_type max_size() const
			{
				return std::numeric_limits<difference_type>::max() / sizeof(T);
			}

			reference front()
			{
				return head->value;
			}

			const_reference front() const
			{
				return head->value;
			}

			reference back()
			{
				return tail->prev->value;
			}

			const_reference back() const
			{
				return tail->prev->value;
			}

			template<class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				// clear();
				insert(begin(), first, last);
			}

			void assign(size_type n, const value_type &val)
			{
				// clear();
				insert(begin(), n, val);
			}

			void push_front(const value_type &val)
			{
				insert(begin(), val);
			}

			void pop_front()
			{
				erase(begin());
			}

			void push_back(const value_type &val)
			{
				insert(end(), val);
			}

			void pop_back()
			{
				erase(--end());
			}

			iterator insert(iterator position, const value_type& val)
			{
				list_node *node = new list_node(position.get_node()->prev, position.get_node());

				node->value = val;
				if (node->prev)
					node->prev->next = node;
				else
					head = node;
				node->next->prev = node;
				len++;
				return iterator(node);
			}

			void insert(iterator position, size_type n, const value_type& val)
			{
				/* list tmp(n, val);

				splice(position, tmp); */
				list_node *node1 = position.get_node()->prev;
				list_node *node2 = position.get_node();
				list_node *cnt = node1;

				while (n > 0)
				{
					list_node *node = new list_node(cnt, NULL);
					node->value = val;
					if (node->prev)
						node->prev->next = node;
					else
						head = node;
					cnt = node;
					len++;
					n--;
				}
				node2->prev = cnt;
				if (cnt)
					cnt->next = node2;
			}

			template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
    		insert (iterator position, InputIterator first, InputIterator last)
			{
				/* list tmp(first, last);

				splice(position, tmp); */
				list_node *node1 = position.get_node()->prev;
				list_node *node2 = position.get_node();
				list_node *cnt = node1;

				for (InputIterator ite = first; ite != last; ite++)
				{
					list_node *node = new list_node(cnt, NULL);
					node->value = *ite;
					if (node->prev)
						node->prev->next = node;
					else
						head = node;
					cnt = node;
					len++;
				}
				node2->prev = cnt;
				if (cnt)
					cnt->next = node2;
			}

			iterator erase(iterator first, iterator last)
			{
				list_node *node1 = first.get_node()->prev;
				list_node *node2 = last.get_node();
				iterator cnt = first;

				while (cnt != last)
				{
					iterator tmp(cnt);
					cnt++;
					len--;
					delete tmp.get_node();
				}
				if (node1)
					node1->next = node2;
				else
					head = node2;
				node2->prev = node1;
				return iterator(node2);
			}

			iterator erase(iterator position)
			{
				iterator last = position;
				
				last++;
				return erase(position, last);
			}

			void splice(iterator position, list &x)
			{
				splice(position, x, x.begin(), x.end());
			}

			void splice(iterator position, list& x, iterator i)
			{
				iterator tmp = i;

				tmp++;
				splice(position, x, i, tmp);
			}

			void splice(iterator position, list& x, iterator first, iterator last)
			{
				list_node *node1 = position.get_node()->prev;
				list_node *node2 = position.get_node();
				list_node *_node1 = first.get_node()->prev;
				list_node *_node2 = last.get_node();
				size_type splice_length = 0;

				while (first != last)
				{
					list_node *tmp = first.get_node();

					if (node1)
						node1->next = tmp;
					else
						head = tmp;
					tmp->prev = node1;
					node1 = tmp;
					first++;
					splice_length++;
				}
				node1->next = node2;
				node2->prev = node1;
				if (_node1)
					_node1->next = _node2;
				else
					x.head = node2;
				_node2->prev = _node1;
				len += splice_length;
				x.len -= splice_length;
			}

	};

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <class T>
	class list_iterator
	{
		public:
			typedef bidirectional_iterator_tag iterator_category;
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			typedef list_node<T> list_node;
                                                                                                                         
		private:
			list_node *node;
		
		public:
			list_iterator():node(NULL) {}
			list_iterator(list_node *node):node(node) {}
			list_iterator(const list_iterator &other):node(other.node) {}

			~list_iterator() {}

			list_node *get_node()
			{
				return node;
			}

			list_iterator<T> &operator=(const list_iterator<T> &other)
			{
				node = other.node;
				return *this;
			}

			list_iterator<T> &operator++()
			{
				node = node->next;
				return *this;
			}

			list_iterator<T> operator++(int)
			{
				list_iterator<T> ret = *this;
				++*this;
				return ret;
			}

			list_iterator<T> &operator--()
			{
				node = node->prev;
				return *this;
			}

			list_iterator<T> operator--(int)
			{
				list_iterator<T> ret = *this;
				--*this;
				return ret;
			}

			reference operator*() const
			{
				return node->value;
			}

			pointer operator->() const
			{
				return &node->value;
			}

			friend void swap(const list_iterator &a, const list_iterator &b)
			{
				list_iterator tmp(a);
				a = b;
				b = tmp;
			}

			friend bool operator==(const list_iterator &lhs, const list_iterator &rhs)
			{
				return lhs.node == rhs.node;
			}

			friend bool operator!=(const list_iterator &lhs, const list_iterator &rhs)
			{
				return !(lhs.node == rhs.node);
			}
	};
}