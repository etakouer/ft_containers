#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <memory>
#include <functional>
#include "functional.hpp"
#include "algorithm.hpp"
#include "iterator.hpp"
#include "tree.hpp"
#include "utility.hpp"

#define T_SET template<class Key, class Compare, class Allocator>
#define S_SET set<Key, Compare, Allocator>
#define TN_SET typename S_SET

namespace ft {

//// * class set

template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key> >
class set
{
    public:

    // types:
    typedef Key                                      key_type;
    typedef key_type                                 value_type;
    typedef Compare                                  key_compare;
    typedef key_compare                              value_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    
    private:
    
    typedef tree<key_type, value_type, identity<value_type>, key_compare, allocator_type> tree_type;
    tree_type _tree;
 
    public:

    typedef typename tree_type::const_iterator                   iterator;
    typedef typename tree_type::const_iterator             const_iterator;
    typedef ft::reverse_iterator<const_iterator>          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    // construct/copy/destroy:
    explicit set(const value_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
    template <class InputIterator>
        set(InputIterator first, InputIterator last, const value_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
    set(const set& s);
     ~set();

    set& operator=(const set& s);
 
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

    // modifiers:
    pair<iterator,bool> insert(const value_type& v);
    iterator insert(const_iterator position, const value_type& v);
    template <class InputIterator>
    typename ft::enable_if < !ft::is_integral<InputIterator>::value, void >::type insert(InputIterator first, InputIterator last);

    void  erase(const_iterator position);
    size_type erase(const key_type& k);
    void  erase(const_iterator first, const_iterator last);
    void clear() throw();

    void swap(set& s);
    
    // observers:
    allocator_type get_allocator() const throw();
    key_compare    key_comp()      const;
    value_compare  value_comp()    const;

    // set operations:
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

T_SET
bool
operator==(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y) {
    return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

T_SET
bool
operator< (const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y){
    return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

T_SET
bool
operator!=(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y) 
{ return !(x==y); }

T_SET
bool
operator> (const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y) 
{ return y < x; }

T_SET
bool
operator>=(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y) 
{ return !(x < y); }

T_SET
bool
operator<=(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y) 
{ return !(y < x); }

// specialized algorithms:
T_SET
void
swap(set<Key, Compare, Allocator>& x, set<Key, Compare, Allocator>& y) 
{ x.swap(y); }

//// * implementation

// construct/copy/destroy:

T_SET S_SET::set(const value_compare& comp, const allocator_type& alloc) : _tree(comp, alloc) { 
}

T_SET
template <class InputIterator>
   S_SET::set(InputIterator first, InputIterator last, const value_compare& comp, const allocator_type& alloc) : _tree(comp, alloc) {
    insert(first, last);
}

T_SET S_SET::set(const set& s) : _tree(s._tree) {
}

T_SET  S_SET::~set() {
}

T_SET S_SET & S_SET::operator=(const set& s) {
    _tree = s._tree;
    return *this;
}

// iterators:

T_SET       TN_SET::iterator S_SET::begin() throw() {
    return _tree.begin();
}

T_SET TN_SET::const_iterator S_SET::begin() const throw() {
    return _tree.begin();
}

T_SET       TN_SET::iterator S_SET::end() throw() {
    return _tree.end();
}

T_SET TN_SET::const_iterator S_SET::end()   const throw() {
    return _tree.end();
}

T_SET       TN_SET::reverse_iterator S_SET::rbegin() throw() {
    return _tree.rbegin();
}

T_SET TN_SET::const_reverse_iterator S_SET::rbegin() const throw() {
    return _tree.rbegin();
}

T_SET       TN_SET::reverse_iterator S_SET::rend() throw() {
    return _tree.rend();
}

T_SET TN_SET::const_reverse_iterator S_SET::rend()   const throw() {
    return _tree.rend();
}

// capacity:

T_SET bool      S_SET::empty()    const throw() {
    return !size();
}

T_SET TN_SET::size_type S_SET::size()     const throw() {
    return _tree.size();
}

T_SET TN_SET::size_type S_SET::max_size() const throw() {
    return _tree.max_size();
}

 
// modifiers:

T_SET pair<TN_SET::iterator,bool> S_SET::insert(const value_type& v) {
    return _tree.insert(v);
}

T_SET TN_SET::iterator S_SET::insert(const_iterator position, const value_type& v) {
    return _tree.insert(position, v);
}

T_SET template <class InputIterator>
typename ft::enable_if < !ft::is_integral<InputIterator>::value, void >::type S_SET::insert(InputIterator first, InputIterator last) {
   while (first != last)
    _tree.insert(*(first++));
}
 
T_SET void  S_SET::erase(const_iterator position) {
   _tree.erase(*position);
}

T_SET TN_SET::size_type S_SET::erase(const key_type& k) {
   return _tree.erase(k);
}

T_SET void  S_SET::erase(const_iterator first, const_iterator last) {
    _tree.erase(first, last);
}

T_SET void S_SET::clear() throw() {
    _tree.clear();
}

 
T_SET void S_SET::swap(set& s) {
    _tree.swap(s._tree);
}
 
// observers:

T_SET TN_SET::allocator_type S_SET::get_allocator() const throw() {
    return allocator_type(_tree.get_allocator());
}

T_SET TN_SET::key_compare    S_SET::key_comp()      const {
    return key_compare();
}

T_SET TN_SET::value_compare  S_SET::value_comp()    const {
    return value_compare();    
}
 
// set operations:

T_SET       TN_SET::iterator S_SET::find(const key_type& k) {
    return _tree.find(k);
}

T_SET TN_SET::const_iterator S_SET::find(const key_type& k) const {
    return _tree.find(k);
}

 
T_SET TN_SET::size_type      S_SET::count(const key_type& k) const {
    return (_tree.find(k) == _tree.end()) ? 0 : 1;
}

T_SET       TN_SET::iterator S_SET::lower_bound(const key_type& k) {
    return _tree.lower_bound(k);
}

T_SET TN_SET::const_iterator S_SET::lower_bound(const key_type& k) const {
    return _tree.lower_bound(k);
}
 
T_SET       TN_SET::iterator S_SET::upper_bound(const key_type& k) {
    return _tree.upper_bound(k);
}

T_SET TN_SET::const_iterator S_SET::upper_bound(const key_type& k) const {
    return _tree.upper_bound(k);
}
 
T_SET pair<TN_SET::iterator, TN_SET::iterator>             S_SET::equal_range(const key_type& k) {
    return _tree.equal_range(k);
}

T_SET pair<TN_SET::const_iterator, TN_SET::const_iterator> S_SET::equal_range(const key_type& k) const {
    return _tree.equal_range(k);
}

} // end namespace ft

#endif
