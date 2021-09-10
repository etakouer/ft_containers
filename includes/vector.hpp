#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <limits>
#include <iostream>
#include <stdexcept>
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

#define T_VECTOR template <class T, class Allocator>
#define S_VECTOR vector<T, Allocator>
#define TN_VECTOR typename S_VECTOR

namespace ft {

//// * class vector

template < class T, class Allocator = std::allocator<T> >
    class vector {

    public:
 
        // Member types

        typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer        	pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::wrap_iter<pointer>				iterator;
		typedef ft::wrap_iter<const_pointer>		const_iterator;
		typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
		typedef ft::reverse_iterator<iterator>              reverse_iterator;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

        // Member functions
 
        explicit vector(const allocator_type& alloc = allocator_type());
        vector(size_type n, const value_type& value = value_type(), const allocator_type& = allocator_type());
        template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& = allocator_type());
        vector(const vector& x);

        ~vector();
        vector& operator=(const vector& x);
    
            // Iterator

        iterator               begin() throw();
        const_iterator         begin()   const throw();
        iterator               end() throw();
        const_iterator         end()     const throw();

        reverse_iterator       rbegin() throw();
        const_reverse_iterator rbegin()  const throw();
        reverse_iterator       rend() throw();
        const_reverse_iterator rend()    const throw();

            // Capacity

        size_type size() const throw();
        size_type max_size() const throw();
        size_type capacity() const throw();
        bool empty() const throw();
        void reserve(size_type n);

            // Element access

        reference       operator[](size_type n);
        const_reference operator[](size_type n) const;
        reference       at(size_type n);
        const_reference at(size_type n) const;

        reference       front();
        const_reference front() const;
        reference       back();
        const_reference back() const;

            // Modifiers

        template <class InputIterator>
            typename ft::enable_if < !ft::is_integral<InputIterator>::value, void >::type 
                assign(InputIterator first, InputIterator last);

        void assign(size_type n, const value_type& u);

        void push_back(const value_type& x);
        void pop_back();

        iterator insert(const_iterator position, const value_type& x);
        iterator insert(const_iterator position, size_type n, const value_type& x);

        template <class InputIterator>
            typename ft::enable_if < !ft::is_integral<InputIterator>::value, iterator >::type 
            insert(const_iterator position, InputIterator first, InputIterator last);

        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);

        void clear() throw();

        void resize(size_type sz, const value_type& x = value_type());

        void swap(vector& x);
        
            // allocator

        allocator_type get_allocator() const throw();
    
        private:
            pointer         _begin;
            pointer         _end;
            pointer         _end_cap;
            allocator_type  _alloc;

            size_type       _good_size(size_type n, bool _assign = false) const;
            void            _destroy_content(pointer begin, pointer end);
            void            _copy_destroy_content(pointer begin, pointer end, pointer new_begin);
            void            _append(size_type n, const value_type & x, bool _assign = false);
            template <class InputIterator>
            typename ft::enable_if < !ft::is_integral<InputIterator>::value, void >::type 
                            _append(InputIterator first, InputIterator last);
            size_type       _rest();
            void            _modify(pointer pos, pointer end, const value_type & x);
};

// Non-member functions

T_VECTOR bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
T_VECTOR bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
T_VECTOR bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
T_VECTOR bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
T_VECTOR bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
T_VECTOR bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

T_VECTOR void swap(vector<T,Allocator>& x, vector<T,Allocator>& y) throw();

//// * implementation

// Member functions

T_VECTOR S_VECTOR::vector(const allocator_type& alloc) : _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc) {
}

T_VECTOR S_VECTOR::vector(size_type n, const value_type& value, const allocator_type& alloc) : _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc) {
    assign(n, value);
}

T_VECTOR template <class InputIterator>
    S_VECTOR::vector(InputIterator first, InputIterator last, const allocator_type& alloc) : _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc) {
    assign(first, last);
}

T_VECTOR S_VECTOR::vector(const vector& x) : _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(x.get_allocator()) {
    assign(x.begin(), x.end());
}

T_VECTOR S_VECTOR::~vector() {
    _destroy_content(_begin, _end);
    _alloc.deallocate(_begin, capacity());
    _begin = _end = _end_cap = NULL;
}

T_VECTOR vector<T, Allocator>& S_VECTOR::operator=(const vector& x) {
    if (&x != this)
        assign(x.begin(), x.end());
    return *this;
}

// Iterator

T_VECTOR TN_VECTOR::iterator S_VECTOR::begin() throw() {
    return iterator(_begin);
}

T_VECTOR TN_VECTOR::const_iterator S_VECTOR::begin() const throw() {
    return const_iterator(_begin);
}

T_VECTOR TN_VECTOR::iterator S_VECTOR::end() throw() {
    return iterator(_end);
}

T_VECTOR TN_VECTOR::const_iterator S_VECTOR::end() const throw() {
    return const_iterator(_end);
}

T_VECTOR TN_VECTOR::reverse_iterator       S_VECTOR::rbegin() throw() {
    return reverse_iterator(end());
}

T_VECTOR TN_VECTOR::const_reverse_iterator S_VECTOR::rbegin()  const throw() {
    return const_reverse_iterator(end());
}

T_VECTOR TN_VECTOR::reverse_iterator       S_VECTOR::rend() throw() {
    return reverse_iterator(begin());
}

T_VECTOR TN_VECTOR::const_reverse_iterator S_VECTOR::rend()    const throw() {
    return const_reverse_iterator(begin());
}

// Capacity

T_VECTOR TN_VECTOR::size_type S_VECTOR::size() const throw() {
    return static_cast<size_type>(_end - _begin);
}
T_VECTOR TN_VECTOR::size_type S_VECTOR::max_size() const throw() {
    return ft::min<size_type>(_alloc.max_size(), std::numeric_limits<difference_type>::max());
}
T_VECTOR TN_VECTOR::size_type S_VECTOR::capacity() const throw() {
    return static_cast<size_type>(_end_cap - _begin);
}

T_VECTOR bool S_VECTOR::empty() const throw() {
    return _begin == _end;
}
T_VECTOR void S_VECTOR::reserve(size_type n) {
    const size_type cap = capacity();
    if (n > cap) {
        _end_cap = _begin;
        pointer new_begin = _alloc.allocate(n);
        _copy_destroy_content(_begin, _end, new_begin);
        _alloc.deallocate(_begin, cap);
        _end = new_begin + size();
        _begin = new_begin;
        _end_cap = new_begin + n;
    }
}

// Element access

T_VECTOR TN_VECTOR::reference       S_VECTOR::operator[](size_type n) {
    return _begin[n];
}

T_VECTOR TN_VECTOR::const_reference S_VECTOR::operator[](size_type n) const {
    return _begin[n];
}

T_VECTOR TN_VECTOR::reference       S_VECTOR::at(size_type n) {
    if (n >= size())
        throw std::out_of_range("vector");
    return _begin[n];
}

T_VECTOR TN_VECTOR::const_reference S_VECTOR::at(size_type n) const {
    if (n >= size())
        throw std::out_of_range("vector");
    return _begin[n];
}
 
T_VECTOR TN_VECTOR::reference       S_VECTOR::front() {
    return *_begin;
}
T_VECTOR TN_VECTOR::const_reference S_VECTOR::front() const {
    return *_begin;
}
T_VECTOR TN_VECTOR::reference       S_VECTOR::back() {
    return *(_end - 1);
}
T_VECTOR TN_VECTOR::const_reference S_VECTOR::back() const {
    return *(_end - 1);
}
 
// Modifiers
 
T_VECTOR template <class InputIterator>
typename ft::enable_if < !ft::is_integral<InputIterator>::value, void >::type
S_VECTOR::assign(InputIterator first, InputIterator last) {
    const size_type n = static_cast<size_type>(ft::distance(first, last));
    if (n < 0) 
        throw std::length_error("vector");
    if ( n > capacity()) {
        clear();
        _append(first, last);
    } else {
        pointer new_begin = _begin;
        while(first != last) {
            if (new_begin >= _end)
                _alloc.construct(new_begin, *first);
            else
                *new_begin = *first;
            first++;
            new_begin++;
        } 
        while(new_begin < _end) {
            _alloc.destroy(new_begin);
            new_begin++;
        }
        _end = _begin + n;
    }
}

T_VECTOR void S_VECTOR::assign(size_type n, const value_type& u) {
    if (n < 0) 
        throw std::length_error("vector");
    const size_type l = n;
    if ( n > capacity()) {
        clear();
        _append(n, u, true);
    } else {
        pointer new_begin = _begin;
        while(n--) {
            if (new_begin >= _end)
                _alloc.construct(new_begin, u);
            else
                *new_begin = u;
            new_begin++;
        } 
        while(new_begin < _end) {
            _alloc.destroy(new_begin);
            new_begin++;
        }
        _end = _begin + l;
    }
}
 
T_VECTOR void S_VECTOR::push_back(const value_type& x) {
    _append(1, x);
}

T_VECTOR void S_VECTOR::pop_back() {
    _alloc.destroy(--_end);
}
 
T_VECTOR TN_VECTOR::iterator S_VECTOR::insert(const_iterator position, const value_type& x) {
    return insert(position, 1, x);
}

T_VECTOR TN_VECTOR::iterator S_VECTOR::insert(const_iterator position, size_type n, const value_type& x) {

    size_type n_before = position - begin(); 
    if (n == 0)
        return begin() + n_before;
    pointer p = _begin + n_before;
    size_type tmp_n = n;
    if (_rest() >= n) {
        pointer tmp_end = _end;
        while (--tmp_end >= p)
            _modify(tmp_end + n , _end, *tmp_end);
        while(tmp_n--)
            _modify(p++, _end, x);
        _end += n;
        return begin() + n_before; 
    }else {
        vector<T> new_vector;
        new_vector.reserve(_good_size(size() + n));
        new_vector.insert(new_vector.begin(), begin(), iterator(p));
        new_vector.insert(new_vector.begin() + n_before, n, x);
        new_vector.insert(new_vector.begin() + n_before + n , iterator(p), end());
        swap(new_vector);
        return begin() + n_before;
    }
}

T_VECTOR template <class InputIterator>
typename ft::enable_if < !ft::is_integral<InputIterator>::value, TN_VECTOR::iterator >::type 
     S_VECTOR::insert(const_iterator position, InputIterator first, InputIterator last) {
     size_type n = static_cast<size_type>(ft::distance(first, last));
    size_type n_before = position - begin(); 
     if (n == 0)
        return iterator(begin() + n_before);
    pointer p = _begin + n_before;
    size_type tmp_n = n;
    if (_rest() >= n) {
        pointer tmp_end = _end;
        while (--tmp_end >= p)
            _modify(tmp_end + n , _end, *tmp_end);
        while(tmp_n--)
            _modify(p++, _end, *first++);
        _end += n;
        return begin() + n_before; 
    }else {
        vector<T> new_vector;
        new_vector.reserve(_good_size(size() + n));
        new_vector.insert(new_vector.begin(), begin(), iterator(p));
        new_vector.insert(new_vector.begin() + n_before, first, last);
        new_vector.insert(new_vector.begin() + n_before + n , iterator(p), end());
        swap(new_vector);
        return begin() + n_before;
    }
}
 
T_VECTOR TN_VECTOR::iterator S_VECTOR::erase(const_iterator position) {
    return erase(position, position+1);
}

T_VECTOR TN_VECTOR::iterator S_VECTOR::erase(const_iterator first, const_iterator last) {
    size_type i = 0;
    pointer p = _begin + (first - begin());
    while(last + i < end()) {
        *(p + i) = *(last + i);
        i++;
    }
    i = last - first;  
    while(i--) 
        _alloc.destroy(--_end);
    return iterator(p);
}
 
T_VECTOR void S_VECTOR::clear() throw() {
    _destroy_content(_begin, _end);
    _end = _begin;
}
 
T_VECTOR void S_VECTOR::resize(size_type sz, const value_type& x) {
    const size_type s = size();
    if (sz < s) {
        _destroy_content(_begin + sz, _end);
        _end = _begin + sz;
    }
    else {
        _append(sz - s, x);
    }
}
 
T_VECTOR void S_VECTOR::swap(vector& x) {
    ft::swap(_begin, x._begin);
    ft::swap(_end, x._end);
    ft::swap(_end_cap, x._end_cap);
    ft::swap(_alloc, x._alloc);
}
 
// allocator
 
T_VECTOR TN_VECTOR::allocator_type S_VECTOR::get_allocator() const throw() { 
    return allocator_type(_alloc);
}

// private functions

T_VECTOR TN_VECTOR::size_type S_VECTOR::_good_size(size_type n, bool _assign) const {
    const size_type ms = max_size();
    if (n > ms)
        throw std::length_error("vector");
    const size_type cap = capacity();
    if (cap >= ms / 2)
        return ms;
    if (_assign)
        return n;
    return ft::max<size_type>(2 * cap, n);
}

T_VECTOR void S_VECTOR::_destroy_content(pointer begin, pointer end) {
    while(end-- != begin)
        _alloc.destroy(end);
}

T_VECTOR void S_VECTOR::_copy_destroy_content(pointer begin, pointer end, pointer new_begin) {
    while (begin != end) {
        _alloc.construct(new_begin, *begin);
        _alloc.destroy(begin);
        begin++;
        new_begin++;
    }
}

T_VECTOR void S_VECTOR::_append(size_type n, const value_type & x, bool _assign) {
    if ( n > _rest())
       reserve(_good_size(size() + n, _assign));
    while(n--) {
        _alloc.construct(_end, x);
        _end++;
    } 
}

T_VECTOR void S_VECTOR::_modify(pointer pos, pointer end, const value_type & x) {
    if (pos >= end) 
        _alloc.construct(pos, x);
    else
        *pos = x;
}

T_VECTOR
template <class InputIterator>
typename ft::enable_if < !ft::is_integral<InputIterator>::value, void >::type 
    S_VECTOR::_append(InputIterator first, InputIterator last) {
    reserve(static_cast<size_type>(ft::distance(first, last)));
    while(first != last) {
        _alloc.construct(_end, *first);
        first++;
        _end++;
    } 
}

T_VECTOR TN_VECTOR::size_type S_VECTOR::_rest() {
    return capacity() - size();
}


// Non-member functions

T_VECTOR bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
    return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

T_VECTOR bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
    return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
} 

T_VECTOR bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
    return !(x == y);
}

T_VECTOR bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
    return y < x;
}

T_VECTOR bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
    return !(x < y);
}

T_VECTOR bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
    return !(y < x);
}

T_VECTOR void swap(vector<T,Allocator>& x, vector<T,Allocator>& y) throw() {
    x.swap(y);
} 

} // end namespace ft
#endif
