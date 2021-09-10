#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {

//// * enable-if

template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };

//// * is_integral

template <class T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T,v> type;
  inline operator T() { return v; }
};

typedef integral_constant<bool,true> true_type;
typedef integral_constant<bool,false> false_type;

template <class T> struct is_integral : public false_type {};
template <class T> struct is_integral<const T> : public is_integral<T> {};
template <class T> struct is_integral<volatile const T> : public is_integral<T>{};
template <class T> struct is_integral<volatile T> : public is_integral<T>{};
template<> struct is_integral<unsigned char> : public true_type {};
template<> struct is_integral<unsigned short> : public true_type{};
template<> struct is_integral<unsigned int> : public true_type{};
template<> struct is_integral<unsigned long> : public true_type{};
template<> struct is_integral<unsigned long long> : public true_type{};
template<> struct is_integral<signed char> : public true_type{};
template<> struct is_integral<char> : public true_type{};
template<> struct is_integral<short> : public true_type{};
template<> struct is_integral<int> : public true_type{};
template<> struct is_integral<long> : public true_type{};
template<> struct is_integral<long long> : public true_type{};
template<> struct is_integral<bool> : public true_type{};
template<> struct is_integral<wchar_t> : public true_type{};

//// * is_same

template<class T, class U>
struct is_same : ft::false_type {};
 
template<class T>
struct is_same<T, T> : ft::true_type {};

//// * _static_assert

template <bool b>
struct _assert {};

template <>
struct _assert<true>
{
    typedef void type;
};

#define _static_assert(condition, msg) typedef typename _assert<condition>::type is_true
 
} // end namespace ft

#endif
