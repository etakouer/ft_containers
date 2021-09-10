#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <memory>
#include <functional>
#include "functional.hpp"
#include "algorithm.hpp"
#include "iterator.hpp"
#include "tree.hpp"
#include "utility.hpp"

#define T_MAP template<class Key, class T, class Compare, class Allocator>
#define S_MAP map<Key, T, Compare, Allocator>
#define TN_MAP typename S_MAP

namespace ft {

//// * class map

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<pair<const Key, T> > >
class map
{
    public:

    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
   
    private:
    
    typedef typename Allocator::template rebind<value_type>::other _pair_alloc_type;
    typedef tree<key_type, value_type, selectFirst<value_type>, key_compare, _pair_alloc_type> tree_type;
    tree_type _tree;
 
    public:

    typedef typename tree_type::iterator                   iterator;
    typedef typename tree_type::const_iterator             const_iterator;
    typedef ft::reverse_iterator<iterator>          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    class value_compare : public ft::binary_function<value_type, value_type, bool> {
        friend class map;

        protected:
            key_compare comp;
            value_compare(key_compare c) : comp(c) {};
        
        public:
            bool operator()(const value_type& x, const value_type& y) const {
                return comp(x.first, y.first);
            }
    };

    // construct/copy/destroy:
    explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type());
    template <class InputIterator>
    map (InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type());
    map (const map& x);
    map& operator=(const map& m);
    ~map();

    // iterators:
          iterator begin() throw();
    const_iterator begin() const throw();
          iterator end() throw();
    const_iterator end()   const throw();

          reverse_iterator rbegin() throw();
    const_reverse_iterator rbegin() const throw();
          reverse_iterator rend() throw();
    const_reverse_iterator rend()   const throw();

    // capacity:
    bool      empty()    const throw();
    size_type size()     const throw();
    size_type max_size() const throw();

    // element access:
    mapped_type& operator[](const key_type& k);
    
    // modifiers:
    pair<iterator, bool> insert(const value_type& v);
    iterator insert(const_iterator position, const value_type& v);

    template <class InputIterator>
    typename ft::enable_if < !ft::is_integral<InputIterator>::value, void >::type 
        insert(InputIterator first, InputIterator last);

    void  erase(const_iterator position);
    size_type erase(const key_type& k);
    void  erase(const_iterator first, const_iterator last);
    void clear() throw();

    void swap(map& m);

    // observers:
    allocator_type get_allocator() const throw();
    key_compare    key_comp()      const;
    value_compare  value_comp()    const;

    // map operations:
          iterator find(const key_type& k);
    const_iterator find(const key_type& k) const;

    size_type      count(const key_type& k) const;
          iterator lower_bound(const key_type& k);
    const_iterator lower_bound(const key_type& k) const;

          iterator upper_bound(const key_type& k);
    const_iterator upper_bound(const key_type& k) const;

    pair<iterator,iterator>             equal_range(const key_type& k);
    pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
};

T_MAP bool operator==(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y) {
    return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

T_MAP bool operator< (const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y) {
    return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

T_MAP bool operator!=(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y) 
{ return !(x==y); }

T_MAP bool operator> (const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y)
{ return y < x; }

T_MAP bool operator>=(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y)
{ return !(x < y); }


T_MAP bool operator<=(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y)
{ return !(y < x); }

T_MAP void swap(map<Key, T, Compare, Allocator>& x,
        map<Key, T, Compare, Allocator>& y)
{ x.swap(y); }

//// * implementation

// construct/copy/destroy:

T_MAP S_MAP::map (const key_compare& comp, const allocator_type& alloc) : _tree(comp, _pair_alloc_type(alloc)) {
}

T_MAP 
template <class InputIterator>
S_MAP::map (InputIterator first, InputIterator last,
   const key_compare& comp,
   const allocator_type& alloc) : _tree(comp, _pair_alloc_type(alloc)) {
    insert(first, last);
}

T_MAP S_MAP::map (const map& x) : _tree(x._tree) {
}

T_MAP S_MAP & S_MAP::operator=(const map& m) {
    _tree = m._tree;
    return *this;    
}

T_MAP S_MAP::~map() {
}


// iterators:

T_MAP TN_MAP::iterator S_MAP::begin() throw() {
   return _tree.begin();
}

T_MAP TN_MAP::const_iterator S_MAP::begin() const throw() {
   return _tree.begin();
}

T_MAP  TN_MAP::iterator S_MAP::end() throw() {
   return _tree.end();
}

T_MAP TN_MAP::const_iterator S_MAP::end()   const throw() {
   return _tree.end();
}

T_MAP       TN_MAP::reverse_iterator S_MAP::rbegin() throw() {
    return _tree.rbegin();
}

T_MAP TN_MAP::const_reverse_iterator S_MAP::rbegin() const throw() {
    return _tree.rbegin();
}

T_MAP       TN_MAP::reverse_iterator S_MAP::rend() throw() {
    return _tree.rend();
}

T_MAP TN_MAP::const_reverse_iterator S_MAP::rend()   const throw() {
    return _tree.rend();
}

// capacity:

T_MAP bool      S_MAP::empty()    const throw() {
   return !size();
}

T_MAP TN_MAP::size_type S_MAP::size()     const throw() {
   return _tree.size();
}

T_MAP TN_MAP::size_type S_MAP::max_size() const throw() {
   return _tree.max_size();
}

// element access:

T_MAP TN_MAP::mapped_type& S_MAP::operator[](const key_type& k) {
    return (*((insert(ft::make_pair(k,mapped_type()))).first)).second; 
}

// modifiers:

T_MAP pair<TN_MAP::iterator, bool> S_MAP::insert(const value_type& v) {
    return _tree.insert(v);
}

T_MAP TN_MAP::iterator S_MAP::insert(const_iterator position, const value_type& v) {
   return _tree.insert(position, v);
}

T_MAP
template <class InputIterator>
typename ft::enable_if < !ft::is_integral<InputIterator>::value, void >::type 
S_MAP::insert(InputIterator first, InputIterator last) {
    while (first != last)
        _tree.insert(*(first++));
}

T_MAP void  S_MAP::erase(const_iterator position) {
   _tree.erase(position->first);
}

T_MAP TN_MAP::size_type S_MAP::erase(const key_type& k) {
   return _tree.erase(k);
}

T_MAP void  S_MAP::erase(const_iterator first, const_iterator last) {
    _tree.erase(first, last);
}

T_MAP void S_MAP::clear() throw() {
    _tree.clear();
}


T_MAP void S_MAP::swap(map& m) {
    _tree.swap(m._tree);
}


// observers:

T_MAP TN_MAP::allocator_type S_MAP::get_allocator() const throw() {
    return allocator_type(_tree.get_allocator());
}

T_MAP TN_MAP::key_compare    S_MAP::key_comp()      const {
    return key_compare();
}

T_MAP TN_MAP::value_compare  S_MAP::value_comp()    const {
    return value_compare(key_comp());
}

// map operations:

T_MAP       TN_MAP::iterator S_MAP::find(const key_type& k) {
    return _tree.find(k);
}

T_MAP TN_MAP::const_iterator S_MAP::find(const key_type& k) const {
    return _tree.find(k);
}


T_MAP TN_MAP::size_type      S_MAP::count(const key_type& k) const {
    return (_tree.find(k) == _tree.end()) ? 0 : 1;
}

T_MAP TN_MAP::iterator S_MAP::lower_bound(const key_type& k) {
    return _tree.lower_bound(k);
}

T_MAP TN_MAP::const_iterator S_MAP::lower_bound(const key_type& k) const {
    return _tree.lower_bound(k);
}

T_MAP       TN_MAP::iterator S_MAP::upper_bound(const key_type& k) {
    return _tree.upper_bound(k);
}

T_MAP TN_MAP::const_iterator S_MAP::upper_bound(const key_type& k) const {
    return _tree.upper_bound(k);
}


T_MAP pair<TN_MAP::iterator,TN_MAP::iterator> S_MAP::equal_range(const key_type& k) {
    return _tree.equal_range(k);
}

T_MAP pair<TN_MAP::const_iterator,TN_MAP::const_iterator> S_MAP::equal_range(const key_type& k) const {
    return _tree.equal_range(k);
}

} // end namespace ft
#endif
