#ifndef UTIL_HPP
#define UTIL_HPP

namespace ft
{
	template <class InputIterator1, class InputIterator2>
  	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class Iter>
	class reverse__iterator
	{
		public:
			typedef Iter iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename iterator_traits<Iter>::value_type value_type;
			typedef typename iterator_traits<Iter>::difference_type difference_type;
			typedef typename iterator_traits<Iter>::pointer pointer;
			typedef typename iterator_traits<Iter>::reference reference;
		private:
			Iter ite;
			reverse__iterator() {};
		public:
			reverse__iterator(Iter base):ite(base)
			{

			}
			reverse__iterator(reverse__iterator<Iter> const &other):ite(other.ite)
			{

			}
			~reverse__iterator()
			{

			}
			Iter base() const
			{
				return ite;
			}
			reverse__iterator<Iter> &operator=(reverse__iterator<Iter> const &other)
			{
				ite = other.ite;
				return *this;
			}
			reference operator*() const
			{
				Iter it(ite);
				--it;
				return *it;
			}
			reverse__iterator operator+(difference_type n) const
			{
				reverse__iterator<Iter> ret(ite.base() - n);
				return ret;
			}
			reverse__iterator<Iter> &operator++()
			{
				--ite;
				return *this;
			}
			reverse__iterator<Iter> operator++(int)
			{
				reverse__iterator<Iter> ite(ite);
				--ite;
				return ite;
			}
			reverse__iterator<Iter> &operator+=(difference_type n)
			{
				ite -= n;
				return *this;
			}
			reverse__iterator operator-(difference_type n) const
			{
				reverse__iterator<Iter> ret(ite.base() + n);
				return ret;
			}
			reverse__iterator<Iter> &operator--()
			{
				++ite;
				return *this;
			}
			reverse__iterator<Iter> operator--(int)
			{
				reverse__iterator<Iter> ite(ite);
				++ite;
				return ite;
			}
			reverse__iterator<Iter> &operator-=(difference_type n)
			{
				ite += n;
				return *this;
			}
			pointer operator->() const
			{
				Iter it(ite);
				--it;
				return it.operator->();
			}
	};

	template<class Iter1, class Iter2>
	bool operator==(const reverse__iterator<Iter1>& x,
					const reverse__iterator<Iter2> &y)
	{
		return (x.base() - y.base());
	}

	template<class Iter1, class Iter2>
	bool operator!=(const reverse__iterator<Iter1>& x,
					const reverse__iterator<Iter2> &y)
	{
		return !(y.base() == x.base());
	}

	template<class Iter1, class Iter2>
	bool operator<(const reverse__iterator<Iter1>& x,
					const reverse__iterator<Iter2> &y)
	{
		return (y.base() < x.base());
	}

	template<class Iter1, class Iter2>
	bool operator>=(const reverse__iterator<Iter1>& x,
					const reverse__iterator<Iter2> &y)
	{
		return !(y.base() < x.base());
	}

	template<class Iter1, class Iter2>
	bool operator>(const reverse__iterator<Iter1>& x,
					const reverse__iterator<Iter2> &y)
	{
		return (y.base() > x.base());
	}

	template<class Iter1, class Iter2>
	bool operator<=(const reverse__iterator<Iter1>& x,
					const reverse__iterator<Iter2> &y)
	{
		return !(y.base() > x.base());
	}

	template<class Iter1, class Iter2>
	typename reverse__iterator<Iter1>::difference_type
	operator-(const reverse__iterator<Iter1>& x, const reverse__iterator<Iter2>& y)
	{
		return x.base() - y.base();
	}




	template <bool is_integral, class T>
	struct is_integral_res
	{
		typedef T type;
		static const bool value = is_integral;
	};

	template <typename>
	struct is_integral_type : public is_integral_res<false, bool> {};
	template <>
	struct is_integral_type<bool> : public is_integral_res<true, bool> {};
	template <>
	struct is_integral_type<char> : public is_integral_res<true, char> {};
	template <>
	struct is_integral_type<char16_t> : public is_integral_res<true, char16_t> {};
	template <>
	struct is_integral_type<char32_t> : public is_integral_res<true, char32_t> {};
	template <>
	struct is_integral_type<wchar_t> : public is_integral_res<true, wchar_t> {};
	template <>
	struct is_integral_type<short> : public is_integral_res<true, short> {};
	template <>
	struct is_integral_type<int> : public is_integral_res<true, int> {};
	template <>
	struct is_integral_type<long> : public is_integral_res<true, long> {};
	template <>
	struct is_integral_type<long long> : public is_integral_res<true, long long> {};

	template<class T> struct is_integral : public is_integral_type<T> { };

	template<bool Condition, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> {typedef T type;};
}

#endif
