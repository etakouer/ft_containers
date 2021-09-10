#include "common_test.hpp"

#define FIRST int
#define SECOND A

bool f(FIRST x, FIRST y) {
    return x>y;
}

void f0() {
    cout << C_G << "# F0 : inset / erase" << C_W << endl;
    typedef ft::tree<FIRST, FIRST, ft::identity<FIRST>, bool (*)(FIRST, FIRST) > type_tree;
     type_tree  tree(f);
     tree.print();
    for(int i = 1; i < 11; i++) {
        tree.insert(i);
        cout << endl;
        tree.print();
    }
    type_tree::iterator it = tree.begin();
    while(it != tree.end())
        cout << *it++ << endl;
  
    std::cout << endl << "After deleting" << endl;
    for(int i = 1; i < 11; i++) {
        tree.erase(i);
        cout << endl;
        tree.print();
    }
 
}

void f1() {
    cout << C_G << "# F1 : pair<> / bool (*f)(T,T)" << C_W << endl;
    typedef ft::tree< FIRST, ft::pair<FIRST, SECOND>, ft::selectFirst<ft::pair<FIRST, SECOND> >, bool(*)(int, int) > type_tree;
    type_tree tree(f);
    tree.insert(ft::make_pair(FIRST(4),SECOND(40)));
    tree.insert(ft::make_pair(FIRST(2),SECOND(20)));
    tree.insert(ft::make_pair(FIRST(3),SECOND(30)));
    tree.insert(ft::make_pair(FIRST(5),SECOND(50)));
    tree.insert(ft::make_pair(FIRST(5),SECOND(50)));
    tree.print();
    tree.erase(FIRST(3));
    std::cout << endl << "After deleting" << endl;
    tree.print();
 }

void f2() {
    cout << C_G << "# F2 : iterator" << C_W << endl;
    typedef ft::tree<FIRST> type_tree;
    type_tree tree;
    for(int i = 1; i < 11; i++) {
        tree.insert(i);
    }
    tree.print();
    type_tree::iterator it = tree.begin();

    while (it != tree.end())
        cout << *(it++) << endl;
    
    it = tree.end();

    while (it != tree.begin())
        cout << *(--it) << endl;

}


int  main(void) {
    f0();
    f1();
    f2();
}
