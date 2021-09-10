#ifndef TREE_ITERATOR
#define TREE_ITERATOR

#include "iterator.hpp"
#include "node_type.hpp"

namespace ft {

template<typename T>
struct tree_iterator
{
    typedef T  value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t                  difference_type;

    typedef typename node_type<T>::node_ptr  type_node_ptr;
    type_node_ptr _node_ptr;

    tree_iterator() : _node_ptr() { }
    
    explicit tree_iterator(type_node_ptr x) : _node_ptr(x) { }

    reference operator*() const { return *(_node_ptr->addr_data()); }

    pointer operator->() const { return _node_ptr->addr_data(); }

    tree_iterator<T>& operator++() {
            _node_ptr = node_increment(_node_ptr);
            return *this;
        }

     tree_iterator<T> operator++(int) {
            tree_iterator<T> tmp = *this;
            _node_ptr = node_increment(_node_ptr);
            return tmp;
        }

    tree_iterator<T>& operator--() {
            _node_ptr = node_decrement(_node_ptr);
            return *this;
        }

    tree_iterator<T> operator--(int) {
            tree_iterator<T> tmp = *this;
            _node_ptr = node_decrement(_node_ptr);
            return tmp;
        }

    bool operator==(const tree_iterator<T>& x) const { return _node_ptr == x._node_ptr; }

    bool operator!=(const tree_iterator<T>& x) const { return _node_ptr != x._node_ptr; }

};

template<typename T>
struct tree_const_iterator
{
    typedef T  value_type;
    typedef const T& reference;
    typedef const T* pointer;
    typedef bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t                  difference_type;
    
    typedef tree_iterator<T>    iterator;
    typedef typename node_type<T>::const_node_ptr type_node_ptr;
    
    type_node_ptr _node_ptr;

    tree_const_iterator() 
        : _node_ptr() { }

   explicit tree_const_iterator(type_node_ptr x) 
        : _node_ptr(x) { }

    tree_const_iterator(const iterator& it) 
        : _node_ptr(it._node_ptr) { }

    iterator
      it_const_cast()
      { return iterator(const_cast<typename node_type<T>::node_ptr>(_node_ptr)); }
 
    reference operator*() const { return *(_node_ptr->addr_data()); }

    pointer operator->() const { return  _node_ptr->addr_data(); }

    tree_const_iterator<T>& operator++() {
            _node_ptr = node_increment(_node_ptr);
            return *this;
        }

    tree_const_iterator<T> operator++(int) {
            tree_const_iterator<T> tmp = *this;
            _node_ptr = node_increment(_node_ptr);
            return tmp;
        }

    tree_const_iterator<T>& operator--() {
            _node_ptr = node_decrement(_node_ptr);
            return *this;
        }

    tree_const_iterator<T> operator--(int) {
            tree_const_iterator<T> tmp = *this;
            _node_ptr = node_decrement(_node_ptr);
            return tmp;
        }

    bool operator==(const tree_const_iterator<T>& x) const { return _node_ptr == x._node_ptr; }

    bool operator!=(const tree_const_iterator<T>& x) const { return _node_ptr != x._node_ptr; }
};

template<typename T>
inline bool operator==(const tree_iterator<T>& x, const tree_const_iterator<T>& y)
{ return x._node_ptr == y._node_ptr; }

template<typename T>
inline bool operator!=(const tree_iterator<T>& x, const tree_const_iterator<T>& y)
{ return x._node_ptr != y._node_ptr; }

} // end namespace ft

#endif
