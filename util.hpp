#ifndef UTIL_HPP
#define UTIL_HPP

namespace ft
{

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
