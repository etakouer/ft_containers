#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {

//// * equal & lexicographical_compare

template <class InputIterator1, class InputIterator2>
bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
{
    while (first1!=last1) {
        if (!(*first1 == *first2)) 
            return false;
        ++first1; ++first2;
    }
    return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
{
  while (first1!=last1)
  {
    if (first2==last2 || *first2<*first1) return false;
    else if (*first1<*first2) return true;
    ++first1; ++first2;
  }
  return (first2!=last2);
}

//// * util functions

template <class T> const T& min (const T& a, const T& b) {
  return (a>b)?b:a;
}

template <class T> const T& max (const T& a, const T& b) {
  return (a>b)?a:b;
}

template<class InputIterator, class Function>
  Function for_each(InputIterator first, InputIterator last, Function fn)
{
  while (first!=last) {
    fn (*first);
    ++first;
  }
  return fn;   
}

template <class T> void swap ( T& a, T& b )
{
  T c(a); a=b; b=c;
}

} // end namespace ft

#endif
