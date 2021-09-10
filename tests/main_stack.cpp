#include "common_test.hpp"

#define CLASS A

void f1(){
    cout << C_G << "# F1 : constructor" << C_W << endl;
    std::deque<CLASS> mydeque (3,CLASS(100));         
    NSP::vector<CLASS> myvector (2,CLASS(200)); 

    NSP::stack<CLASS> first; 
    NSP::stack<CLASS,std::deque<CLASS> > second (mydeque); 

    NSP::stack<CLASS, NSP::vector<CLASS> > third; 
    NSP::stack<CLASS, NSP::vector<CLASS> > fourth (myvector);

    std::cout << "size of first: " << first.size() << '\n';
    std::cout << "size of second: " << second.size() << '\n';
    std::cout << "size of third: " << third.size() << '\n';
    std::cout << "size of fourth: " << fourth.size() << '\n';
}

void f2() {
    cout << C_G << "# F2 empty" << C_W << endl;
    NSP::stack<CLASS> mystack;
    CLASS sum (0);

    for (int i=1;i<=10;i++) mystack.push(CLASS(i));

    while (!mystack.empty())
    {
        sum += mystack.top();
        mystack.pop();
    }

    std::cout << "total: " << sum << '\n';
}

void f3(){
    cout << C_G << "# F3 size" << C_W << endl;
    NSP::stack<CLASS> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i=0; i<5; i++) myints.push(CLASS(i));
    std::cout << "1. size: " << myints.size() << '\n';

    myints.pop();
    std::cout << "2. size: " << myints.size() << '\n';
}

void f4() {
    cout << C_G << "# F4 top" << C_W << endl;
    NSP::stack<CLASS> mystack;

    mystack.push(CLASS(10));
    mystack.push(CLASS(20));

    mystack.top() -= CLASS(5);

    std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

void f5() {
    cout << C_G << "# F5 pop push" << C_W << endl;
    NSP::stack<CLASS> mystack;

    for (int i=0; i<5; ++i) mystack.push(CLASS(i));

    std::cout << "Popping out elements...";
    while (!mystack.empty())
    {
        std::cout << ' ' << mystack.top();
        mystack.pop();
    }
    std::cout << '\n';
}

void f6() {
    cout << C_G << "# F6 operator " << C_W << endl;
    NSP::vector<CLASS> f (3,CLASS("100")); 
    NSP::vector<CLASS> b (3,CLASS("200"));
    NSP::stack<CLASS, NSP::vector<CLASS> > foo (f); 
    NSP::stack<CLASS, NSP::vector<CLASS> > bar (b);
    cout  << "compare : \n";
    if (foo==bar) cout << "foo and bar are equal\n";
    if (foo!=bar) cout << "foo and bar are not equal\n";
    if (foo< bar) cout << "foo is less than bar\n";
    if (foo> bar) cout << "foo is greater than bar\n";
    if (foo<=bar) cout << "foo is less than or equal to bar\n";
    if (foo>=bar) cout << "foo is greater than or equal to bar\n";
    cout << endl; 
}

int main() {
    cout <<  C_G << TNSP << C_W << endl << endl;
    f1();
    f2();
    f3();
    f4();
    f5();
    f6();
}
