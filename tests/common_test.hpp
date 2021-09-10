#ifndef COMMON_TEST
#define COMMON_TEST

#ifdef FT 
    #define NSP ft
    #define TNSP "FT"
#else
    #define NSP std
    #define TNSP "STD"
#endif

#include <iostream> 
#include <string>
#include <sstream>

#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"

#include <vector>
#include <stack>
#include <set>
#include <map>
#include <list>

#include "A.hpp"

#define C_G "\033[1;96m"
#define C_W "\033[0;39m"

std::ostream& cout = std::cout;
typedef std::string string;
static string endl = "\n" ;

template<class T>
void print_vector(NSP::vector<T> & vector1, std::string name = "") {
    cout << endl;
    cout << "<" << name << ">" << endl;
    cout << "cap : " << vector1.capacity() << endl;
    cout << "size : " << vector1.size() << endl;
    cout << "[ ";
    for (typename NSP::vector<T>::iterator it = vector1.begin(); it != vector1.end(); it++)
        cout << "{" << *it << "}" << ((it+1 != vector1.end()) ? ", ": "") ;
    cout << " ]" << endl << endl;
}

template <class T1, class T2>
std::ostream & operator<<(std::ostream & o, ft::pair<T1, T2> const & pr) {
    o << "(" << pr.first <<", " << pr.second << ")";    
    return o;
}

template <class T1, class T2>
std::ostream & operator<<(std::ostream & o, std::pair<T1, T2> const & pr) {
    o << "(" << pr.first <<", " << pr.second << ")";    
    return o;
}

template<class Map>
void print_map(Map const & mapy, std::string name = "") {
    cout << endl;
    cout << "<" << name << ">" << endl;
    cout << "size : " << mapy.size() << endl;
    cout << "[ ";
    for (typename Map::const_iterator it = mapy.begin(); it != mapy.end(); it++)
        cout << *it << " " ;
    cout << " ]" << endl << endl;
}

template <typename T>
std::string to_string(T v) {
    std::stringstream ss;
    std::string s;
    ss << v;
    ss >> s;
    return s;
}

#endif
