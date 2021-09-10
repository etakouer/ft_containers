#ifndef UTILITY_HPP
#define UTILITY_HPP

#define T_PAIR template <class T1, class T2>
#define S_PAIR pair<T1, T2>
#define TN_PAIR typename S_PAIR

namespace ft {

//// * pair

template <class T1, class T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair();
    pair(const T1& x, const T2& y);
    template <class U, class V> pair(const pair<U, V>& p);
    template <class U, class V> pair& operator=(const pair<U, V>& p);
};

T_PAIR bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

T_PAIR bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return !(lhs == rhs);
}

T_PAIR bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

T_PAIR bool operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return rhs < lhs;
}

T_PAIR bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
    return !(lhs < rhs);
}

T_PAIR bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
    return !(rhs < lhs);
}

T_PAIR S_PAIR::pair() : first(), second() {
}

T_PAIR S_PAIR::pair(const T1& x, const T2& y) : first(x), second(y) {
}

T_PAIR
template <class U, class V> 
S_PAIR::pair(const pair<U, V>& p): first(p.first), second(p.second) {
}

T_PAIR
template <class U, class V>
pair<T1, T2>& S_PAIR::operator=(const pair<U, V>& p) {
    first = p.first;
    second = p.second;
    return *this;
}

//// * make_pair

T_PAIR
pair<T1,T2> make_pair (T1 x, T2 y) {
    return ( pair<T1,T2>(x,y) );
}

} // end namespace ft

#endif
