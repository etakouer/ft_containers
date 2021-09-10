#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <cassert>

#define T_STACK template <class T, class Container>
#define S_STACK stack<T, Container>
#define TN_STACK typename S_STACK

#include "type_traits.hpp"

namespace ft {

//// * class stack

template <class T, class Container = ft::vector<T> >
class stack
{
    public:
        typedef Container                                container_type;
        typedef typename container_type::value_type      value_type;
        typedef typename container_type::reference       reference;
        typedef typename container_type::const_reference const_reference;
        typedef typename container_type::size_type       size_type;
        _static_assert((ft::is_same<T, value_type>::value), "container type and value_type are not same !");

    protected:

        container_type c;

    public:
        explicit stack(const container_type& c = container_type());
        stack& operator=(const stack& q);
        ~stack();

        bool empty() const;
        size_type size() const;

        reference top();
        const_reference top() const;

        void push(const value_type& x);
        void pop();
        
        template <class T1, class C1>
        friend bool operator==(const stack<T1, C1>& x, const stack<T1, C1>& y);
        template <class T1, class C1>
        friend bool operator< (const stack<T1, C1>& x, const stack<T1, C1>& y);

};

T_STACK bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y);
T_STACK bool operator> (const stack<T, Container>& x, const stack<T, Container>& y);
T_STACK bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y);
T_STACK bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y);

//// * implemtation

T_STACK S_STACK::stack(const container_type& cc) : c(cc) {
}

T_STACK stack<T, Container>& S_STACK::operator=(const stack& s) {
    c = s.c;
}

T_STACK S_STACK::~stack() {
}

T_STACK bool S_STACK::empty() const {
   return c.empty();
}

T_STACK TN_STACK::size_type S_STACK::size() const {
    return c.size();
}

T_STACK TN_STACK::reference S_STACK::top() {
    return c.back();
}

T_STACK TN_STACK::const_reference S_STACK::top() const {
    return c.back();
}

T_STACK void S_STACK::push(const value_type& x) {
    c.push_back(x);
}

T_STACK void S_STACK::pop() {
    c.pop_back();
}

T_STACK bool operator==(const stack<T, Container>& x, const stack<T, Container>& y) {
   return  x.c == y.c;
}

T_STACK bool operator< (const stack<T, Container>& x, const stack<T, Container>& y) {
   return x.c < y.c;
}

T_STACK bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y) {
   return !(x == y);
}

T_STACK bool operator> (const stack<T, Container>& x, const stack<T, Container>& y) {
    return y < x;
}

T_STACK bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y) {
    return !(x < y);
}

T_STACK bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y) {
    return !(y < x);
}

} // end namespace ft
#endif
