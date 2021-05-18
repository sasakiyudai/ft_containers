#include <memory> // allocator
#include <iostream> // debug

namespace ft
{
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
			// typedef list_iterator<T> iterator;
			// typedef list_iterator<const T> const_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef size_t size_type;
		
		private:
			struct list_node
			{
				list_node *prev;
				list_node *next;
				T value;

				list_node(list_node *prev, list_node *next):prev(prev), next(next)
				{

				}
			};
			list_node *head;
			allocator_type allocator;

		public:
			explicit list(const allocator_type& alloc = allocator_type())
			{
				head = new list_node(NULL, NULL);
				allocator = alloc;
			}

			explicit list (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type())
			{
				head = new list_node(NULL, NULL);
				allocator = alloc;
				// assign(n, val);
			}

			template <class InputIterator>
  			list (InputIterator first, InputIterator last,
        		const allocator_type& alloc = allocator_type())
			{
				head = new list_node(NULL, NULL);
				allocator = alloc;
				// assign(first, last);
			}

			list (const list& x)
			{
				head = new list_node(NULL, NULL);
				allocator = x.allocator;
				// assign(x.begin(), x.end());
			}

			~list ()
			{
				// erase(begin(), end());
				delete head;
			}

			list& operator= (const list& x)
			{
				// clear();
				// assign(x.begin(), x.end());
				return *this;
			}

	};


}