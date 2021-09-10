#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include "type_traits.hpp"
#include <iostream>

#define T_REV template <class Iterator>
#define S_REV reverse_iterator<Iterator>
#define TN_REV typename S_REV 

namespace ft {

//// * Category tags

struct input_iterator_tag  {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


//// * iterator_traits

template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template<class T>
struct iterator_traits<T*>
{
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef random_access_iterator_tag iterator_category;
};

template<class T>
struct iterator_traits<const T*>
{
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef random_access_iterator_tag iterator_category;
};

//// * iterator

template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

//// * reverse_iterator

template <class Iterator>
class reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference>
{
    public:

        // Member types

        typedef Iterator                                            iterator_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::reference       reference;
        typedef typename iterator_traits<Iterator>::pointer         pointer;

        // Member functions

        reverse_iterator();
        explicit reverse_iterator(iterator_type it);
        template <class Iter> 
            reverse_iterator(const reverse_iterator<Iter>& rev_it);
        template <class Iter> 
            reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it);
        iterator_type base() const;

        reference         operator*() const;
        reverse_iterator  operator+ (difference_type n) const;
        reverse_iterator& operator++();
        reverse_iterator  operator++(int);
        reverse_iterator& operator+=(difference_type n);
        reverse_iterator  operator- (difference_type n) const;
        reverse_iterator& operator--();
        reverse_iterator  operator--(int);
        reverse_iterator& operator-=(difference_type n);
        pointer           operator->() const;
        reference         operator[](difference_type n) const;

    protected:
        iterator_type _current;
};

// Non-member function overloads

T_REV bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
T_REV bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
T_REV bool operator<  (const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs);
T_REV bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
T_REV bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
T_REV bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
T_REV reverse_iterator<Iterator> operator+ (
          typename reverse_iterator<Iterator>::difference_type n, 
          const reverse_iterator<Iterator>& rev_it);
T_REV TN_REV::difference_type operator- (
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs);

//// * implemetation reverse_iterator

// Member function

T_REV S_REV::reverse_iterator() : _current() {
}

T_REV S_REV::reverse_iterator(iterator_type it) : _current(it) {
}

T_REV
template <class Iter>
S_REV::reverse_iterator(const reverse_iterator<Iter>& rev_it) : _current(rev_it.base()) {
}

T_REV
template <class Iter>
reverse_iterator<Iterator>& S_REV::operator=(const reverse_iterator<Iter>& rev_it) {
    _current = rev_it.base();
    return *this;
}


T_REV TN_REV::iterator_type S_REV::base() const {
    return _current;
}

T_REV TN_REV::reference   S_REV::operator*() const {
    iterator_type tmp = _current;
    return  *(--tmp);
}

T_REV reverse_iterator<Iterator>  S_REV::operator+ (difference_type n) const {
    return reverse_iterator(_current - n);
}

T_REV reverse_iterator<Iterator> & S_REV::operator++() {
    _current--;
    return *this;
}

T_REV reverse_iterator<Iterator> S_REV::operator++(int) {
    reverse_iterator tmp = *this;
    ++(*this);
    return tmp;
}

T_REV reverse_iterator<Iterator>&  S_REV::operator+=(difference_type n) {
    _current-=n;
    return *this;
}

T_REV reverse_iterator<Iterator> S_REV::operator- (difference_type n) const {
    return reverse_iterator(_current + n);
}

T_REV reverse_iterator<Iterator>& S_REV::operator--() {
    _current++;
    return *this;
}  

T_REV reverse_iterator<Iterator>  S_REV::operator--(int) {
    reverse_iterator tmp = *this;
    --(*this);
    return tmp;
}

T_REV reverse_iterator<Iterator>& S_REV::operator-=(difference_type n) {
    _current+=n;
    return *this;
}

T_REV TN_REV::pointer S_REV::operator->() const {
    return  &(operator*());
}

T_REV TN_REV::reference S_REV::operator[](difference_type n) const {
    return _current[-n-1];
}

// Non-member function

T_REV bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return lhs.base() == rhs.base();
}

T_REV bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return lhs.base() != rhs.base(); 
}

T_REV bool operator<  (const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs)  {
    return lhs.base() > rhs.base(); 
}

T_REV bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return lhs.base() >= rhs.base(); 
}

T_REV bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return lhs.base() < rhs.base(); 
}

T_REV bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return lhs.base() <= rhs.base(); 
}

T_REV reverse_iterator<Iterator> operator+ (
          TN_REV::difference_type n, 
          const reverse_iterator<Iterator>& rev_it) {
    return reverse_iterator<Iterator>(rev_it.base() - n);
}

T_REV TN_REV::difference_type operator- (
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
    return rhs.base() - lhs.base();
}

// Allow reverse vs const reverse

template<typename IteratorL, typename IteratorR>
inline bool
operator==(const reverse_iterator<IteratorL>& x,
       const reverse_iterator<IteratorR>& y)
{ return x.base() == y.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator<(const reverse_iterator<IteratorL>& x,
      const reverse_iterator<IteratorR>& y)
{ return y.base() < x.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator!=(const reverse_iterator<IteratorL>& x,
       const reverse_iterator<IteratorR>& y)
{ return !(x == y); }

template<typename IteratorL, typename IteratorR>
inline bool
operator>(const reverse_iterator<IteratorL>& x,
      const reverse_iterator<IteratorR>& y)
{ return y < x; }

template<typename IteratorL, typename IteratorR>
inline bool
operator<=(const reverse_iterator<IteratorL>& x,
       const reverse_iterator<IteratorR>& y)
{ return !(y < x); }

template<typename IteratorL, typename IteratorR>
inline bool
operator>=(const reverse_iterator<IteratorL>& x,
       const reverse_iterator<IteratorR>& y)
{ return !(x < y); }

template<typename IteratorL, typename IteratorR>
inline typename reverse_iterator<IteratorL>::difference_type
operator-(const reverse_iterator<IteratorL>& x,
      const reverse_iterator<IteratorR>& y)
{ return y.base() - x.base(); }

//// * wrap_iter

template<typename Iterator>
class wrap_iter {
    protected:
        Iterator _current;

    public:
        typedef Iterator                                          iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type    value_type;
        typedef typename iterator_traits<Iterator>::difference_type   difference_type;
        typedef typename iterator_traits<Iterator>::reference     reference;
        typedef typename iterator_traits<Iterator>::pointer       pointer;

        wrap_iter() : _current(Iterator()) { }
        explicit  wrap_iter(const Iterator& it) : _current(it) { }
        template<typename Iter>
            wrap_iter(const wrap_iter<Iter> & it) : _current(it.base()) { }

        // Forward iterator requirements
        reference operator*() const { return *_current; }
        pointer operator->() const { return _current; }
        wrap_iter& operator++() { ++_current; return *this; }
        wrap_iter operator++(int) { return wrap_iter(_current++); }

        // Bidirectional iterator requirements
        wrap_iter& operator--() { --_current; return *this; }
        wrap_iter operator--(int) { return wrap_iter(_current--); }

        // Random access iterator requirements
        reference operator[](const difference_type& n) const { return _current[n]; }
        wrap_iter& operator+=(const difference_type& n)
            { _current += n; return *this; }
        wrap_iter operator+(const difference_type& n) const 
            { return wrap_iter(_current + n); }
        wrap_iter& operator-=(const difference_type& n)
            { _current -= n; return *this; }
        wrap_iter operator-(const difference_type& n) const
            { return wrap_iter(_current - n); }
        const Iterator& base() const { return _current; }
};

// Forward iterator requirements
template<typename IteratorL, typename IteratorR>
inline bool
operator==(const wrap_iter<IteratorL>& lhs,
       const wrap_iter<IteratorR>& rhs)
{ return lhs.base() == rhs.base(); }

template<typename Iterator>
inline bool
operator==(const wrap_iter<Iterator>& lhs,
       const wrap_iter<Iterator>& rhs)
{ return lhs.base() == rhs.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator!=(const wrap_iter<IteratorL>& lhs,
       const wrap_iter<IteratorR>& rhs)
{ return lhs.base() != rhs.base(); }

template<typename Iterator>
inline bool
operator!=(const wrap_iter<Iterator>& lhs,
       const wrap_iter<Iterator>& rhs)
{ return lhs.base() != rhs.base(); }

// Random access iterator requirements
template<typename IteratorL, typename IteratorR>
inline bool
operator<(const wrap_iter<IteratorL>& lhs,
      const wrap_iter<IteratorR>& rhs)
{ return lhs.base() < rhs.base(); }

template<typename Iterator>
inline bool
operator<(const wrap_iter<Iterator>& lhs,
      const wrap_iter<Iterator>& rhs)
{ return lhs.base() < rhs.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator>(const wrap_iter<IteratorL>& lhs,
      const wrap_iter<IteratorR>& rhs)
{ return lhs.base() > rhs.base(); }

template<typename Iterator>
inline bool
operator>(const wrap_iter<Iterator>& lhs,
      const wrap_iter<Iterator>& rhs)
{ return lhs.base() > rhs.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator<=(const wrap_iter<IteratorL>& lhs,
       const wrap_iter<IteratorR>& rhs)
{ return lhs.base() <= rhs.base(); }

template<typename Iterator>
inline bool
operator<=(const wrap_iter<Iterator>& lhs,
       const wrap_iter<Iterator>& rhs)
{ return lhs.base() <= rhs.base(); }

template<typename IteratorL, typename IteratorR>
inline bool
operator>=(const wrap_iter<IteratorL>& lhs,
       const wrap_iter<IteratorR>& rhs)
{ return lhs.base() >= rhs.base(); }

template<typename Iterator>
inline bool
operator>=(const wrap_iter<Iterator>& lhs,
       const wrap_iter<Iterator>& rhs)
{ return lhs.base() >= rhs.base(); }

template<typename IteratorL, typename IteratorR>
inline typename wrap_iter<IteratorL>::difference_type
operator-(const wrap_iter<IteratorL>& lhs,
      const wrap_iter<IteratorR>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename Iterator>
inline typename wrap_iter<Iterator>::difference_type
operator-(const wrap_iter<Iterator>& lhs,
      const wrap_iter<Iterator>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename Iterator>
inline wrap_iter<Iterator>
operator+(typename wrap_iter<Iterator>::difference_type
      n, const wrap_iter<Iterator>& it)
{ return wrap_iter<Iterator>(it.base() + n); }

//// * distance

template<typename InputIterator>
inline typename std::iterator_traits<InputIterator>::difference_type
_distance(InputIterator first, InputIterator last,
           std::input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

template<typename RandomAccessIterator>
inline typename std::iterator_traits<RandomAccessIterator>::difference_type
_distance(RandomAccessIterator first, RandomAccessIterator last,
           std::random_access_iterator_tag) {
  return last - first;
}

template<typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
_distance(InputIterator first, InputIterator last,
           input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

template<typename RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
_distance(RandomAccessIterator first, RandomAccessIterator last,
           random_access_iterator_tag) {
  return last - first;
}

template<typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
  return _distance(first, last,
             typename iterator_traits<InputIterator>::iterator_category());
}

} // end namespace ft
#endif
