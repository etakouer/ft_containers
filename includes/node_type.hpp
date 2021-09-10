#ifndef NODE_TYPE_HPP
#define NODE_TYPE_HPP

#include <cstddef>
namespace ft {

enum Node_color {BLACK = 0, RED = 1};
enum Dir {RIGHT = 0, LEFT = 1};

template<class T>
struct node_type {
    typedef node_type* node_ptr;
    typedef node_type const * const_node_ptr;
    T data;
    node_ptr parent;
    node_ptr left;
    node_ptr right;
    Node_color color;
    node_type(T d = T(), node_ptr p = NULL, node_ptr l = NULL, 
            node_ptr r = NULL, Node_color c = BLACK ) : 
        data(d), parent(p), left(l), right(r), color(c) { }

    T * addr_data() {
       // if (left == NULL && right == NULL)
         //   return NULL;
        return &data;
    }
    T const * addr_data() const {
        //if (left == NULL && right == NULL)
          //  return NULL;
        return &data;
    }

    node_ptr child(bool dir) {
        if (dir == LEFT)
            return left;
        else
            return right;
    }
    
    node_ptr grandparent() {
        if (parent == NULL)
            return NULL;
        return parent->parent;
    }

    node_ptr brother() {
        if (parent == NULL)
            return NULL;
        if (this == parent->left)
            return parent->right;
        else
            return parent->left;
    }

    node_ptr oncle() {
        node_ptr gp = grandparent();
        if (gp == NULL)
            return NULL;
        return parent->brother();
    }

};

template <class T>
bool is_null_node(node_type<T>* x) {
    return (x->left == NULL && x->right == NULL);
}
 
template <class T>
node_type<T>*  node_minimum(node_type<T>* node) {
    while (!is_null_node(node->left)) {
        node = node->left;
    }
    return node;
}

template <class T>
node_type<T>*  node_maximum(node_type<T>* node) {
    while (!is_null_node(node->right)) {
        node = node->right;
    }
    return node;
}

template <class T>
static node_type<T>* _get_root(node_type<T>* x) {
    if(x->parent == NULL)
        return x;
    return _get_root(x->parent);
}
 

template <class T>
static node_type<T>* _node_increment(node_type<T>* x) throw () {
    if(!x || is_null_node(x))
        return x;
    if(x == node_maximum(_get_root(x)))
        return x->right;

    if (!is_null_node(x->right)) {
        return node_minimum(x->right);
    }

    while (x->parent && x == x->parent->right) {
        x = x->parent;
    }
    return x->parent;
}

template <class T>
node_type<T>* node_increment(node_type<T>* x) throw ()
{
    return _node_increment(x);
}

template <class T>
const node_type<T>* node_increment(const node_type<T>* x) throw ()
{
    return _node_increment(const_cast<node_type<T>*>(x));
}

template <class T>
static node_type<T>* _node_decrement(node_type<T>* x) throw ()
{
     if(!x)
        return x;
    if (is_null_node(x))
        return x->parent;
    if (!is_null_node(x->left)) {
        return node_maximum(x->left);
    }
    while (x->parent && x == x->parent->left) {
        x = x->parent;
    }
    return x->parent;
}

template <class T>
node_type<T>* node_decrement(node_type<T>* x) throw () {
    return _node_decrement(x);
}

template <class T>
const node_type<T>* node_decrement(const node_type<T>* x) throw () {
    return _node_decrement(const_cast<node_type<T>*>(x));
}

} // end namespace ft

#endif
