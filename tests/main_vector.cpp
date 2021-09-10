#include "common_test.hpp"

#define CLASS int

void f0(){
    cout << C_G << "# F0 insert compatibility iter (input/random) (std/ft)" << C_W << endl;
    NSP::vector<CLASS> vector0(2,5);
    print_vector(vector0, "vector0");
    NSP::vector<CLASS> myvector(2,CLASS(1));
    std::list<CLASS> vector2(5,CLASS(2));
    print_vector(myvector, "myvector");
    cout << "insert :" << endl;
    myvector.insert(myvector.begin(), vector2.begin(), vector2.end());
    cout << "---" << endl;
    print_vector(myvector, "myvector");
}

void f1(){
    cout << C_G << "# F1 reserve push_back clear" << C_W << endl;
    NSP::vector<CLASS> vector1;
    try {
        vector1.reserve(vector1.max_size()+1);
    }
    catch (const std::exception & e) {
        cout << "error: " << e.what() << '\n';
    } 
    for (int i=1; i<=5; i++)
        vector1.push_back(CLASS(i));
    print_vector(vector1);
    vector1.clear();
    print_vector(vector1);
    vector1.push_back(CLASS(1));
    vector1.push_back(CLASS(2));
    print_vector(vector1);
}

void f2() {
    cout << C_G << "# F2 resize" << C_W << endl;
    NSP::vector<CLASS> vector1(5,CLASS(1));
    vector1.resize(4, CLASS(0));
    print_vector(vector1);
    vector1.resize(8);
    print_vector(vector1);
    NSP::vector<CLASS> vector2(vector1.begin(), vector1.end());
    print_vector(vector2, "vector2");
    NSP::vector<CLASS> vector3(vector2);
    print_vector(vector3, "vector3");
}

void f3(){
    cout << C_G << "# F3 assign / push_back" << C_W << endl;
    NSP::vector<CLASS> vector1(1, CLASS(5));
    print_vector(vector1, "vector1");
    vector1.reserve(5);
    print_vector(vector1, "vector1");
    cout << endl <<"assign" << endl;
    #ifdef Darwin
    try {
        vector1.assign(vector1.max_size(), CLASS(6));
    } catch(std::exception const & e) {
        std::cout << e.what() << endl;
    }
    #endif
    print_vector(vector1, "vector1");
    vector1.assign(4, CLASS(0));
    print_vector(vector1, "vector1");
    NSP::vector<CLASS> vector2 = vector1;
    print_vector(vector2, "vector2");
    NSP::vector<CLASS> vector3;
    vector3 = vector1;
    print_vector(vector3, "vector3");
    NSP::vector<CLASS> vector4(vector2.begin() + 1, vector2.end() - 1);
    print_vector(vector4, "vector3");
    vector1.push_back(CLASS(1));
    vector1.pop_back();
    vector1.pop_back();
    print_vector(vector1, "vector1");
}

void f4() {
    cout << C_G << "# F4 insert" << C_W << endl;
    NSP::vector<CLASS> myvector;
    myvector.push_back(CLASS(1));
    myvector.push_back(CLASS(2));
    print_vector(myvector, "myvector");
    NSP::vector<CLASS>::iterator it;

    cout << endl << "insert n cap < " << endl;
    it = myvector.insert (myvector.begin() + 1 , 3 ,CLASS(66) );
    cout << "it : {" << *it << "}" << endl;
    print_vector(myvector, "myvector");

    myvector.reserve(8);

    cout << endl << "insert n cap > " << endl;
    it = myvector.insert (myvector.begin() , 2 ,CLASS(77) );
    cout << "it : {" << *it << "}" << endl;
    print_vector(myvector, "myvector");

    NSP::vector<CLASS> vector1(3, CLASS(1));

    cout << endl << "insert first last cap < " << endl;
    it = myvector.insert(myvector.begin() + 2, vector1.begin(), vector1.end());
    cout << "it : {" << *it << "}" << endl;
    print_vector(myvector, "myvector");

    myvector.insert (it,2,CLASS(300));

    print_vector(myvector, "myvector");

    it = myvector.begin();

    NSP::vector<CLASS> anothervector (2,CLASS(400));
    myvector.insert (it+2,anothervector.begin(),anothervector.end());

    print_vector(myvector, "myvector");

    CLASS myarray [] = { CLASS(501), CLASS(502), CLASS(503) };
    myvector.insert (myvector.begin(), myarray, myarray+3);

    print_vector(myvector, "myvector");

}

void f5() {
    cout << C_G << "# F5 is_enable is_integral " << C_W << endl;
    NSP::vector<int> myvector;
    myvector.assign(10,10);
    print_vector(myvector);
    myvector.insert(myvector.begin(),myvector.begin(), myvector.end());
}
 
void f6() {
    cout << C_G << "# F6 == > < => <= swap" << C_W << endl;
    NSP::vector<CLASS> foo (3,CLASS(100)); 
    NSP::vector<CLASS> bar (3,CLASS(200));

    cout << endl << "compare : \n";
    if (foo==bar) cout << "foo and bar are equal\n";
    if (foo!=bar) cout << "foo and bar are not equal\n";
    if (foo< bar) cout << "foo is less than bar\n";
    if (foo> bar) cout << "foo is greater than bar\n";
    if (foo<=bar) cout << "foo is less than or equal to bar\n";
    if (foo>=bar) cout << "foo is greater than or equal to bar\n";
    cout << endl; 
    cout << "swap :"<< endl; 
    foo.swap(bar);
}

void f7(){
    cout << C_G << "# F7 erase" << C_W << endl;

    NSP::vector<CLASS> myvector;
    for (int i=1; i<=10; i++) myvector.push_back(CLASS(i));
    print_vector(myvector);

    cout << "erase one :\n";
    myvector.erase (myvector.begin() + 3);
    cout << endl;

    cout << "erase first last:\n";
    myvector.erase (myvector.begin(), myvector.begin() + 1);
    cout << endl;

    cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size(); ++i)
        cout << ' ' << myvector[i];
    cout << '\n';
}

void f8(){
    cout << C_G << "# F8 reverse_iterator front back " << C_W << endl;
    NSP::vector<CLASS> myvector;
    for (int i=1; i<=5; i++) myvector.push_back(CLASS(i));

    cout << *(++myvector.begin()) << endl;

    for(NSP::vector<CLASS>::reverse_iterator it = myvector.rbegin();
            it != myvector.rend(); ++it)
    cout << *it << endl;
    cout << myvector.back() << endl;
    cout << myvector.front() << endl;
}

void f9(){
    cout << C_G << "# F9 [ ]" << C_W << endl;
    NSP::vector<CLASS> myvector (10);   // 10 zero-initialized elements
    NSP::vector<CLASS>::size_type sz = myvector.size();

    // assign some values:
    for (unsigned i=0; i<sz; i++) myvector[i]=i;

    // reverse vector using operator[]:
    for (unsigned i=0; i<sz/2; i++)
    {
        CLASS temp;
        temp = myvector[sz-1-i];
        myvector[sz-1-i]=myvector[i];
        myvector[i]=temp;
    }
    print_vector(myvector);
}

int main() {
    cout <<  C_G << TNSP << C_W << endl << endl;
    f0();
    f1();
    f2();
    f3();
    f4();
    f5();
    f6();
    f7();
    f8();
}
