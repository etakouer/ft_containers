#include "common_test.hpp"

#define FIRST A
#define SECOND int

void f1(){
    cout << C_G << "# F1 : " << "constructor , = , make_pair" << C_W << endl;

    NSP::pair<FIRST, SECOND> pr(FIRST("a"), SECOND(100)); 
    cout << pr << endl;;
    pr.first = FIRST("b");
    NSP::pair<FIRST, SECOND> pr1(pr); 
    cout << pr1 << endl;;
    NSP::pair<FIRST, SECOND> pr2;
    pr2 = NSP::make_pair(FIRST("c"), SECOND(300));
    pr1 = pr2;
    cout << pr1 << endl;;
    cout << pr2 << endl;;
}

void f2(){
    cout << C_G << "# F2 : " << "Reltional operators" << C_W << endl;
    
    NSP::pair<int,char> foo (10,'z');
    NSP::pair<int,char> bar (90,'a');

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n"; 
}

int main() {
    cout <<  C_G << TNSP << C_W << endl << endl;
    f1();
    f2();
}
