#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <limits>
#include "functional.hpp"
#include "algorithm.hpp"
#include "utility.hpp"
#include "iterator.hpp"
#include "tree_iterator.hpp"
#include "node_type.hpp"

#define T_TREE template<typename Key, typename Val, typename KeyVal, typename Compare, typename Alloc >
#define S_TREE tree<Key, Val, KeyVal, Compare, Alloc>
#define TN_TREE typename S_TREE

namespace ft {

template<typename Key, typename Val = Key, typename KeyVal = ft::identity<Val>,
           typename Compare = std::less<Key>, typename Alloc = std::allocator<Val> >
class tree {

    public:

        typedef Key 			        key_type;
        typedef Val 			        value_type;
        typedef node_type<value_type>   node_tree;
        typedef typename node_tree::node_ptr node_ptr;
        typedef typename Alloc::template rebind<node_tree>::other allocator_type;
        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef Compare                 key_is_less;
        typedef KeyVal                  key_of;

        typedef ft::tree_iterator<value_type>       iterator;
        typedef ft::tree_const_iterator<value_type> const_iterator;
        typedef ft::reverse_iterator<iterator>       reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


    protected:

        node_ptr        _root;
        node_ptr        _NULL;
        KeyVal          _get_key;
        key_is_less     _is_less;
        allocator_type  _alloc;
        node_ptr        _begin;
        node_ptr        _end;
        size_type       _size;

    private:

        template<class F>
        void _postfix(node_ptr x, F f);
       
        node_ptr _create_node(node_tree const & v);
        void _remove_node(node_ptr node);

        const_iterator _find(node_ptr node, key_type const & key) const; 
        
        void _rotate(node_ptr x, bool dir);
        void _left_rotate(node_ptr x); 
        void _right_rotate(node_ptr x); 
        void _transplant(node_ptr x, node_ptr y);

        void  _print(node_ptr const & root, std::string const & padding, 
                bool right, bool brother) const;

        bool _is_left(node_ptr const & x) const;
        bool _is_before(value_type const & data1, value_type const & data2) const;
        bool _is(node_ptr x, bool dir);
        node_ptr _get_parent_leaf(node_ptr x, value_type const & data);
        
        void _fix_insert(node_ptr new_node);
        void _fix_erase(node_ptr x);
        
        void _update_tree_in(node_ptr const & new_node);
        void _update_tree_del(node_ptr const & del_node);

        const_iterator _upper_bound(const key_type& key) const;
        const_iterator _lower_bound(const key_type& key) const;

    public:
        explicit tree (const key_is_less& comp = key_is_less(),
              const allocator_type& alloc = allocator_type());
        tree(const tree & t);
        tree & operator=(const tree& t);
        ~tree();

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;

        pair<iterator, bool> insert(value_type const & data); 
        iterator insert(const_iterator position, value_type const & data); 

        size_type erase(key_type const & key); 
        void erase(const_iterator position); 
        void  erase(const_iterator first, const_iterator last);

        void clear();
        void swap(tree & t);

        iterator find(key_type const & key);
        const_iterator find(key_type const & key) const;

        iterator lower_bound(const key_type& key);
        const_iterator lower_bound(const key_type& k) const;
        iterator upper_bound(const key_type& k);
        const_iterator upper_bound(const key_type& k) const;;

        allocator_type get_allocator() const;
        pair<iterator,iterator> equal_range(const key_type& k);
        pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

        size_type size() const;
        size_type max_size() const;

        iterator root();
        const_iterator root() const;
        void print() const; 
};

T_TREE S_TREE::tree(const key_is_less & comp, const allocator_type& alloc) : 
    _get_key(KeyVal()), _is_less(comp), _alloc(alloc), _size(0) {
    _NULL = _create_node(node_tree());
    _begin = _end = _root = _NULL;
}

T_TREE S_TREE::tree(const tree & t) : _get_key(t._get_key), _is_less(t._is_less), _alloc(t._alloc), _size(t._size) {
    _NULL = _create_node(node_tree());
    _begin = _end = _root = _NULL;
    *this = t;
}


T_TREE S_TREE & S_TREE::operator=(const tree& t) {
    if (&t != this) {
        clear();
        const_iterator it = t.begin();
        while(it != t.end())
            insert(*(it++));
    }
    return *this;
}

T_TREE S_TREE::~tree(){
    clear();
    _remove_node(_NULL);
}

T_TREE TN_TREE::iterator S_TREE::begin() {
    return iterator(_begin);
}

T_TREE TN_TREE::iterator S_TREE::end() {
    return iterator(_end);
}

T_TREE TN_TREE::const_iterator S_TREE::begin() const {
    return const_iterator(_begin);
}

T_TREE TN_TREE::const_iterator S_TREE::end() const {
    return const_iterator(_end);
}

T_TREE TN_TREE::reverse_iterator S_TREE::rbegin() {
    return reverse_iterator(end());
}

T_TREE TN_TREE::reverse_iterator S_TREE::rend() {
    return reverse_iterator(begin());
}

T_TREE TN_TREE::const_reverse_iterator S_TREE::rbegin() const {
    return const_reverse_iterator(end());
}

T_TREE TN_TREE::const_reverse_iterator S_TREE::rend() const {
    return const_reverse_iterator(begin());
}

T_TREE void S_TREE::clear() {
    _postfix(_root, &tree::_remove_node);
    _NULL->parent = NULL;  
    _NULL->left = NULL;  
    _NULL->right = NULL;  
    _NULL->color = BLACK;  
    _begin = _end = _root = _NULL;
    _size = 0;
}

T_TREE void S_TREE::swap(tree & t) {
    ft::swap(_root, t._root);
    ft::swap(_begin, t._begin);
    ft::swap(_end, t._end);
    ft::swap(_size, t._size);
    ft::swap(_NULL, t._NULL);
}

T_TREE TN_TREE::iterator S_TREE::find(key_type const & key) {
    return  _find(_root, key).it_const_cast();
}

T_TREE TN_TREE::const_iterator S_TREE::find(key_type const & key) const {
    return _find(_root, key);    
}

T_TREE TN_TREE::const_iterator S_TREE::_lower_bound(const key_type& key) const {
    const_iterator it = find(key);
    const_iterator next = (it == end()) ? begin() : it;
    while(next != end()) {
        if (!_is_less(_get_key(*next), key))
            return next;
        next++;
    }
    return end();
}


T_TREE TN_TREE::iterator S_TREE::lower_bound(const key_type& key) {
    return _lower_bound(key).it_const_cast();
}

T_TREE TN_TREE::const_iterator S_TREE::lower_bound(const key_type& key) const {
    return _lower_bound(key);
}

T_TREE TN_TREE::const_iterator S_TREE::_upper_bound(const key_type& key) const {
    const_iterator it = find(key);
    const_iterator next = (it == end()) ? begin() : it;
    while(next != end()) {
        if (_is_less(key, _get_key(*next)))
            return next;
        next++;
    }
    return end();
}

T_TREE TN_TREE::iterator S_TREE::upper_bound(const key_type& key) {
    return _upper_bound(key).it_const_cast();
}

T_TREE TN_TREE::const_iterator S_TREE::upper_bound(const key_type& key) const {
    return _upper_bound(key);
}

T_TREE TN_TREE::allocator_type S_TREE::get_allocator() const {
    return allocator_type(_alloc);
}

T_TREE pair<TN_TREE::iterator, TN_TREE::iterator> S_TREE::equal_range(const key_type& key) {
    return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

T_TREE pair<TN_TREE::const_iterator, TN_TREE::const_iterator> S_TREE::equal_range(const key_type& key) const {
    return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
}

T_TREE
void  S_TREE::_print(node_ptr const & root, std::string const & padding, 
        bool right, bool brother) const {
    static const char * _RESET = "\033[0m";
    static const char * _RED = "\033[31m";
    if (root == _NULL) {
        if (brother)
            std::cout << padding << (right ? "├──·" : "└──·") << std::endl;
        return;
    }
    std::cout << padding << ((root == _root) ? "───" : (right ? "├──" : "└──"));
    std::cout << ((root->color == BLACK) ? "" : _RED) << "*" << _RESET << _get_key(root->data);
    if (root != _root ) std::cout << ":" << _get_key(root->parent->data);
    else std::cout << ":" << root->parent;
    std::cout << std::endl;
    _print(root->right, padding + (right ? "│   " : "    "), 
            true, root->left != _NULL);
    _print(root->left, padding + (right ? "│   " : "    ") , 
            false, root->right != _NULL);
}

T_TREE
void  S_TREE::print() const {
    std::cout << "size = " << _size << std::endl;
    std::cout << "_NULL (L:"<< _NULL->left << ", R:" << _NULL->right << ", P:" ;
    if (_NULL->parent != NULL) std::cout <<  _get_key(_NULL->parent->data);
    else std::cout << _NULL->parent;
    std::cout << ")" << std::endl;
    _print(_root, "", false, false);
}

T_TREE
template <class F>
void S_TREE::_postfix(node_ptr node, F f) {
    if (node != _NULL) {
        _postfix(node->left, f);
        _postfix(node->right, f);
        (this->*f)(node);
    }
}

T_TREE
bool S_TREE::_is_before(value_type const & data1, value_type const & data2) const {
    return _is_less(_get_key(data1), _get_key(data2));
}
 
T_TREE TN_TREE::const_iterator S_TREE::_find(node_ptr node, key_type const & key) const {
    if (node == _NULL)
        return end();
    if (!_is_less(_get_key(node->data), key) && !_is_less(key,_get_key(node->data))) 
        return const_iterator(node);
    if (_is_less(key, _get_key(node->data)))
        return _find(node->left, key);
    return _find(node->right, key);
}

T_TREE bool S_TREE::_is(node_ptr x, bool dir) {
    if (dir == LEFT)
        return _is_left(x);
    else
        return !_is_left(x);
}

T_TREE void S_TREE::_fix_insert(node_ptr new_node) {
    // node is red , parent is red ?
    while (new_node->parent && new_node->parent->color == RED) {
        // parent is red , oncle is red ?
        if (new_node->oncle()->color == RED) {
            // push blackness down from grandparent
            new_node->parent->color = BLACK;
            new_node->oncle()->color = BLACK;
            new_node->grandparent()->color = RED;
            new_node = new_node->grandparent();
        }else { 
            bool dir = _is(new_node->parent, LEFT);
            // node and parent are different ?
            if (_is(new_node, !dir)) {
                // rotate parent
                new_node = new_node->parent;
                _rotate(new_node, dir);
            }
            // rotate grandparent
            new_node->parent->color = BLACK;
            new_node->grandparent()->color = RED;
            _rotate(new_node->grandparent(), !dir);
        }
    }
    _root->color = BLACK;
} 

T_TREE void S_TREE::_update_tree_in(node_ptr const & new_node){
    if (size() == 1) {
        _begin = _root;
        _end->parent = _root;
    }
    else {
        if (_is_before(new_node->data, _begin->data))
           _begin = new_node;
        if (_is_before(_end->parent->data, new_node->data))
           _end->parent = new_node;
    }
    _end->left = _end->right = NULL;
    _NULL->color = BLACK;
}


T_TREE TN_TREE::size_type S_TREE::size() const{
    return _size;
}

T_TREE TN_TREE::size_type S_TREE::max_size() const{
    return ft::min<size_type>(_alloc.max_size(), std::numeric_limits<difference_type>::max());
}


T_TREE TN_TREE::iterator S_TREE::insert(const_iterator position, value_type const & data) {
    (void)position;
    return insert(data).first;
}

T_TREE
TN_TREE::node_ptr S_TREE::_get_parent_leaf(node_ptr x, value_type const & data) {
    node_ptr parent;
    while (x != _NULL) {
        parent = x;
        if (_is_before(x->data, data))
            x = x->right;
        else if (_is_before(data, x->data))
            x = x->left;
        else
            return x;
   }
   return parent;
}

T_TREE pair<TN_TREE::iterator, bool> S_TREE::insert(value_type const & data) { 
    node_ptr new_node = _create_node(node_tree(data, NULL, _NULL, _NULL, RED));
    node_ptr tmp = _end->parent;
    _end->parent = NULL;
    if (_root == _NULL) {
        new_node->color = BLACK;
        _root = new_node;
    } else {
        node_ptr parent_leaf = _get_parent_leaf(_root, data); 
        new_node->parent = parent_leaf;
        if (_is_before(parent_leaf->data, data))
            parent_leaf->right = new_node;
        else if (_is_before(data, parent_leaf->data))
            parent_leaf->left = new_node;
        else {
            _end->parent = tmp;
            _remove_node(new_node);
            return pair<iterator, bool>(iterator(parent_leaf), false);
        }
        _fix_insert(new_node);
    }
    _size++;
    _end->parent = tmp;
    _update_tree_in(new_node);
    return pair<iterator, bool>(iterator(new_node), true);
}

T_TREE void S_TREE::_transplant(node_ptr x, node_ptr y) {
    if (x->parent == NULL) {
        _root = y;
    } else if (_is(x, LEFT)) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->parent = x->parent;
}

T_TREE  void S_TREE::_fix_erase(node_ptr fix_node) {
    while (fix_node != _root && fix_node->color == BLACK) {
        bool dir = _is_left(fix_node);
        node_ptr bro_node = fix_node->brother();
        // bro is red
        if (bro_node->color == RED) {
          bro_node->color = BLACK;
          fix_node->parent->color = RED;
          _rotate(fix_node->parent, dir);
          bro_node = fix_node->brother();
        }
        // bro is black and its both children are black
        if (bro_node->left->color == BLACK && bro_node->right->color == BLACK) {
          bro_node->color = RED;
          fix_node = fix_node->parent;
        } else {
          // bro is black and its right child is black and !dir child is red
          if (bro_node->child(!dir)->color == BLACK) {
            bro_node->child(dir)->color = BLACK;
            bro_node->color = RED;
            _rotate(bro_node, !dir);
            bro_node = fix_node->brother();
          } 
          // bro is black and its dir child is red
          bro_node->color = fix_node->parent->color;
          fix_node->parent->color = BLACK;
          bro_node->child(!dir)->color = BLACK;
          _rotate(fix_node->parent, dir);
          fix_node = _root;
        }
    }
    fix_node->color = BLACK;
}

T_TREE void S_TREE::erase(const_iterator position) {
    erase(_key_of(*position));
}

T_TREE void  S_TREE::erase(const_iterator first, const_iterator last) {
    while (first!=last) {
        erase(_get_key(*first++));
    }
}

T_TREE void S_TREE::_update_tree_del(node_ptr const & del_node){
    if (size() == 0) {
        _begin = _NULL;
        _end->parent = NULL;
    }
    else {
        if (_begin == del_node) 
            _begin = node_minimum(_root);
        if (_end->parent == del_node) 
            _end->parent = node_maximum(_root);
    }
    _NULL->left = _NULL->right = NULL;
    _NULL->color = BLACK;
}


T_TREE TN_TREE::size_type S_TREE::erase(key_type const & key) {
    iterator it = find(key);
    node_ptr tmp = _end->parent;
    _end->parent = NULL;
    if (it == end())
        return false;
    node_ptr del_node = it._node_ptr;
    node_ptr fix_node;
    Node_color original_color;

    if (del_node->left == _NULL) {
        original_color = del_node->color;
        fix_node = del_node->right;
        _transplant(del_node, del_node->right);
    } else if (del_node->right == _NULL) {
        original_color = del_node->color;
        fix_node = del_node->left;
        _transplant(del_node, del_node->left);
    } else {
        node_ptr min_node = node_minimum(del_node->right); 
        original_color = min_node->color;
        fix_node = min_node->right;

        _transplant(min_node, min_node->right);
        min_node->right = del_node->right;
        min_node->right->parent = min_node;

        _transplant(del_node, min_node);
        min_node->left = del_node->left;
        min_node->left->parent = min_node;
        min_node->color = del_node->color;
    }

    _size--;
    if (original_color == BLACK)
       _fix_erase(fix_node);
    _end->parent = tmp;
    _update_tree_del(del_node);
    _remove_node(del_node);
   return true; 
}

T_TREE void S_TREE::_remove_node(node_ptr node) {
   _alloc.destroy(node);
   _alloc.deallocate(node, 1);
}

T_TREE TN_TREE::node_ptr S_TREE::_create_node(node_tree const & v) {
    node_ptr node = _alloc.allocate(1);
    _alloc.construct(node, v);
    return node;
}

T_TREE bool S_TREE::_is_left(node_ptr const & x) const {
            return x->parent->left == x;
}

T_TREE void S_TREE::_left_rotate(node_ptr x) {
    node_ptr y = x->right;
    x->right = y->left;
    if (y->left != _NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        _root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

T_TREE void S_TREE::_right_rotate(node_ptr x) {
    node_ptr y = x->left;
    x->left = y->right;
    if (y->right != _NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        _root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

T_TREE void S_TREE::_rotate(node_ptr x, bool dir) {
    if (dir == LEFT)
        _left_rotate(x);
    else
        _right_rotate(x);
}

T_TREE TN_TREE::iterator S_TREE::root() {
    return iterator(_root);
}

T_TREE TN_TREE::const_iterator S_TREE::root() const {
    return const_iterator(_root);
}

} // end namespace
#endif
