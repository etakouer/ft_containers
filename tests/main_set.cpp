#include "common_test.hpp"

#define FIRST int
#define COMP ft::less<FIRST>

bool fncomp (FIRST lhs, FIRST rhs) {return lhs < rhs;}
bool fncomp1 (FIRST lhs, FIRST rhs) {return lhs > rhs;}

struct classcomp {
  bool operator() (const FIRST & lhs, const FIRST & rhs) const
  {return lhs < rhs;}
};

void f0() {
    cout << C_G << "# F0 : " << "greater / []" << C_W << endl;

    NSP::set<FIRST, bool (*)(FIRST, FIRST) > set5(fncomp1); // function pointer as Compare

    set5.insert(FIRST(1));
    set5.insert(FIRST(2));
    set5.insert(FIRST(3));
    set5.insert(FIRST(4));

     NSP::set<FIRST, bool(*)(FIRST,FIRST)>::iterator it = set5.begin(); 
    while(it != set5.end()) {
        cout << *it++ << endl;
    }  

    cout << endl;
    print_map(set5, "set5");

    cout << "erase : " << set5.erase(FIRST(0)) << endl;
    
    print_map(set5, "set5");
    NSP::set<FIRST, bool(*)(FIRST,FIRST)> set6 (fncomp1);
    set6 = set5; // function pointer as Compare
    print_map(set6, "set6");

}


void f1(){
    cout << C_G << "# F1 : " << "Contructor / reverse" << C_W << endl;
    NSP::set<FIRST> set1;

    print_map<NSP::set<FIRST> >(set1, "set1");

    set1.insert(FIRST(1));
    set1.insert(FIRST(2));
    set1.insert(FIRST(3));
    set1.insert(FIRST(4));
    set1.insert(FIRST(5));
    set1.insert(FIRST(6));
    set1.insert(FIRST(7));

    print_map(set1, "set1");

    NSP::set<FIRST> set2 (set1.begin(), --set1.end());
    print_map(set2, "set2");

    NSP::set<FIRST> set3 (set2);
    print_map(set3, "set3");

    NSP::set<FIRST>::reverse_iterator it = set3.rbegin();
    while(it != set3.rend())
    {
        it++;
        it--;
        ++it;
        --it;
        if(it != set3.rend())
            cout << *it++ << endl;
    }
    cout << endl;

    it = set3.rbegin();
    for(int i=0; i<5 ;i++)
        cout << *++it << endl;

    cout << endl;
    it = set3.rend();
    while(it != set3.rbegin())
    {
        it--;
        it++;
        --it;
        ++it;
        if(it != set3.rbegin())
            cout << *--it << endl;
    }
    cout << endl;

    it = set3.rend();
    --it;
    for(int i=0; i<5 ;i++)
        cout << *it-- << endl;

}


void f2(){
    cout << C_G << "# F2 : " << "Inserti erase" << C_W << endl;

    NSP::set<FIRST, classcomp> set4;  
    for(int i =0; i < 6; i++) {
        cout << *(set4.insert(FIRST(i)).first);
        print_map(set4, "set4");
    }
    
    for(int i = 0; i < 9; i++) {
        cout << set4.erase(i);
        print_map(set4, "set4");
    }

    NSP::set<FIRST> myset;
    // first insert function version (single parameter):
    cout << endl << "insert 1 :" << endl;
    myset.insert (FIRST(1));
    
    print_map(myset, "myset");

    myset.insert (FIRST(2));

    print_map(myset, "myset");

    NSP::pair<NSP::set<FIRST>::iterator,bool> ret;
    ret = myset.insert (FIRST(5));
    if (ret.second==false) {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << *ret.first << '\n';
    }

    // second insert function version (with hint position):
    NSP::set<FIRST>::iterator it = myset.end();
    cout << endl << "insert 2 :" << endl;
    myset.insert (it, FIRST(7));  // max efficiency inserting
    print_map(myset, "myset insert2");

    cout << endl << "insert 3 :" << endl;
    myset.insert (it, FIRST(4));  // no max efficiency inserting
    print_map(myset, "myset");

    // third insert function version (range insertion):
    NSP::set<FIRST> anothermap;
    cout << endl << "insert 4 :" << endl;
    anothermap.insert(myset.begin(),myset.find(FIRST(4)));
    print_map(anothermap, "anothermap");

}

void f3 ()
{
    cout << C_G << "# F3 : " << "up low bound" << C_W << endl;
    typedef NSP::set<FIRST,COMP > type_map;
    type_map myset;
    type_map::iterator itlow,itup;

    myset.insert(FIRST(0));
    myset.insert(FIRST(2));
    myset.insert(FIRST(4));
    myset.insert(FIRST(6));
    myset.insert(FIRST(8));

    print_map(myset);
    FIRST x = 6;
    itlow=myset.lower_bound (FIRST(x));  // itlow points to b
    itup=myset.upper_bound (FIRST(x));   // itup points to e (not d!)
    cout << "low " << x << " " << *itlow << " up " << *itup << '\n';
    
    if (COMP()((*itup), (*itlow)))
        myset.erase(itup,itlow);        // erases [itlow,itup)
    else
        myset.erase(itlow, itup);        // erases [itlow,itup)
    print_map(myset);
    //cout << "max_size depend implemantation: " << myset.max_size() << endl;  
}

void f4 ()
{
    cout << C_G << "# F4 : " << "equal rang" << C_W << endl;
    typedef NSP::set<FIRST, COMP > type_map;
    type_map myset;

    myset.insert(FIRST(0));
    myset.insert(FIRST(2));
    myset.insert(FIRST(4));
    myset.insert(FIRST(6));
    myset.insert(FIRST(8));

    print_map(myset);
    NSP::pair<type_map::iterator, type_map::iterator> p;
    FIRST x = 8;
    p = myset.equal_range(FIRST(x));
    
     if( p.first != myset.end())
    cout << "low " << x << " " << *p.first << '\n';
     if( p.second != myset.end())
    cout << "up " << x << " " << *p.second << '\n';
   
    myset.erase(p.first, p.second);        // erases [itlow,itup)
    print_map(myset);
    
}

void f5 ()
{
    cout << C_G << "# F5 : " << "swap clear" << C_W << endl;
    typedef NSP::set<FIRST, std::less<FIRST> > type_map;
    type_map set1;
    
    for(int i =0; i< 10; i++)
        set1.insert(i);
    print_map(set1, "set1");
    
    typedef NSP::set<FIRST, std::less<FIRST> > type_map;
    type_map set2;
    
    for(int i =10; i< 20; i++)
        set2.insert(i);
    print_map(set2, "set2");

    set1.swap(set2);

    print_map(set1, "set1 map.swap");
    print_map(set2, "set2 map.swap");

    swap(set1, set2);
    
    print_map(set1, "set1 swap(a,b)");
    print_map(set2, "set2 swap(a,b)");

   
    set2.clear();

    cout << (set2 == set1) << endl;
    print_map(set1, "set1");
    print_map(set2, "set2 clear");
    
    set2 = set1;
    cout << (set2 == set1) << endl;
}


void f6 () {
    cout << C_G << "# F6 : " << "relational op" << C_W << endl;
    NSP::set<char> foo,bar;
    foo.insert('a');
    foo.insert('b');
    bar.insert('a');
    bar.insert('z');

        cout << "foo ({{a},{b}}) vs bar ({a},{z}})\n : ";
        if (foo==bar) std::cout << "foo and bar are equal\n";
        if (foo!=bar) std::cout << "foo and bar are not equal\n";
        if (foo< bar) std::cout << "foo is less than bar\n";
        if (foo> bar) std::cout << "foo is greater than bar\n";
        if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
        if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void f7()
{
    cout << C_G << "# F7 : " << "key_comp value_compare" << C_W << endl;
    NSP::set<char> myset;
    NSP::set<char>::key_compare mycomp = myset.key_comp();
    myset.insert('a');
    myset.insert('b');
    myset.insert('c');
    std::cout << "myset contains:\n";
    char c_highest = *myset.rbegin();     // key value of last element
    NSP::set<char,int>::iterator it = myset.begin();
    do {
        std::cout << *it <<  '\n';
    } while ( mycomp((*it++), c_highest) );

    std::cout << '\n';

    char highest = *myset.rbegin();          // last element

    it = myset.begin();
    do {
        std::cout << *it  << '\n';
    } while ((myset.value_comp())(*(it++), highest));
}

void f8 () {
    cout << C_G << "# F8 : " << "find / count" << C_W << endl;
    NSP::set<char> myset;
    NSP::set<char>::iterator it;

    myset.insert('a');
    myset.insert('b');
    myset.insert('c');
    myset.insert('d');

    it = myset.find('b');
    if (it != myset.end())
        myset.erase (it);

    // print content:
    std::cout << "elements in myset:" << '\n';
    std::cout << "a => " << *myset.find('a') << '\n';
    std::cout << "c => " << *myset.find('c') << '\n';
    std::cout << "d => " << *myset.find('d') << '\n';
    myset.insert('a');
    myset.insert('c');
    myset.insert('f');
    
    char c;
    for (c='a'; c<'h'; c++)
    {
        std::cout << c;
        if (myset.count(c)>0)
            std::cout << " is an element of myset.\n";
        else 
            std::cout << " is not an element of myset.\n";
    }
}

void f9 () {
    cout << C_G << "# F9 : " << "allocator" << C_W << endl;
    int psize;
    NSP::set<char> myset;
    char * p;

    //  allocate an array of 5 elements using myset's allocator:
    p = myset.get_allocator().allocate(5);

    // assign some values to array
    psize = sizeof(NSP::set<char>::value_type) * 5;

    std::cout << "The allocated array has a size of " << psize << " \n";

    myset.get_allocator().deallocate(p,5);

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
    f9();
}
