#include "common_test.hpp"

#define FIRST int
#define SECOND int
#define COMP ft::greater<FIRST>

bool fncomp (FIRST lhs, FIRST rhs) {return lhs < rhs;}
bool fncomp1 (FIRST lhs, FIRST rhs) {return lhs > rhs;}

struct classcomp {
  bool operator() (const FIRST & lhs, const FIRST & rhs) const
  {return lhs < rhs;}
};

void f0() {
    cout << C_G << "# F0 : " << "greater / []" << C_W << endl;

    NSP::map<FIRST,SECOND, bool (*)(FIRST, FIRST) > map5(fncomp1); // function pointer as Compare

    map5.insert(NSP::make_pair(FIRST(1),SECOND(100)));
    map5.insert(NSP::make_pair(FIRST(2),SECOND(200)));
    map5.insert(NSP::make_pair(FIRST(3),SECOND(300)));
    map5.insert(NSP::make_pair(FIRST(4),SECOND(400)));

    map5[FIRST(1)]=10;
    map5[FIRST(2)]=20;
    map5[FIRST(3)]=30;
    map5[FIRST(4)]=40;
    map5[FIRST(4)]=80;
  
     NSP::map<FIRST,SECOND, bool(*)(FIRST,FIRST)>::iterator it = map5.begin(); 
    while(it != map5.end()) {
        cout << *it++ << endl;
    }  

    cout << endl;
    print_map(map5, "map5");

    cout << "erase : " << map5.erase(FIRST(0)) << endl;
    
    print_map(map5, "map5");
    NSP::map<FIRST,SECOND, bool(*)(FIRST,FIRST)> map6 (fncomp1);
    map6 = map5; // function pointer as Compare
    print_map(map6, "map6");

}


void f1(){
    cout << C_G << "# F1 : " << "Contructor / reverse" << C_W << endl;
    NSP::map<FIRST,SECOND> map1;

    print_map<NSP::map<FIRST, SECOND> >(map1, "map1");

    map1[FIRST(1)]=10;
    map1[FIRST(2)]=30;
    map1[FIRST(3)]=30;
    map1[FIRST(4)]=40;
    map1[FIRST(5)]=50;
    map1[FIRST(6)]=60;
    map1[FIRST(7)]=70;

    print_map(map1, "map1");

    NSP::map<FIRST,SECOND> map2 (map1.begin(), --map1.end());
    print_map(map2, "map2");

    NSP::map<FIRST,SECOND> map3 (map2);
    print_map(map3, "map3");

    NSP::map<FIRST,SECOND>::reverse_iterator it = map3.rbegin();
    while(it != map3.rend())
    {
        it++;
        it--;
        ++it;
        --it;
        if(it != map3.rend())
            cout << *it++ << endl;
    }
    cout << endl;

    it = map3.rbegin();
    for(int i=0; i<5 ;i++)
        cout << *++it << endl;

    cout << endl;
    it = map3.rend();
    while(it != map3.rbegin())
    {
        it--;
        it++;
        --it;
        ++it;
        if(it != map3.rbegin())
            cout << *--it << endl;
    }
    cout << endl;

    it = map3.rend();
    --it;
    for(int i=0; i<5 ;i++)
        cout << *it-- << endl;

}


void f2(){
    cout << C_G << "# F2 : " << "Inserti erase" << C_W << endl;

    NSP::map<FIRST,SECOND, classcomp> map4;  
    for(int i =0; i < 6; i++) {
        cout << ((map4.insert(NSP::make_pair(FIRST(i), SECOND(i*10)))).first)->first;
        print_map(map4, "map4");
    }
    
    for(int i = 0; i < 9; i++) {
        cout << map4.erase(i);
        print_map(map4, "map4");
    }

    NSP::map<FIRST,SECOND> mymap;
    // first insert function version (single parameter):
    NSP::pair<FIRST, SECOND> pr(FIRST(1), SECOND(100)); 
    cout << endl << "insert 1 :" << endl;
    mymap.insert (pr);
    
    print_map(mymap, "mymap");

    mymap.insert ( NSP::pair<FIRST, SECOND>(FIRST(2), SECOND(200)) );

    print_map(mymap, "mymap");

    NSP::pair<NSP::map<FIRST,SECOND>::iterator,bool> ret;
    ret = mymap.insert ( NSP::pair<FIRST,SECOND>(FIRST(5), SECOND(500)) );
    if (ret.second==false) {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << '\n';
    }

    // second insert function version (with hint position):
    NSP::map<FIRST,SECOND>::iterator it = mymap.end();
    cout << endl << "insert 2 :" << endl;
    mymap.insert (it, NSP::pair<FIRST,SECOND>(FIRST(7), SECOND(700)));  // max efficiency inserting
    print_map(mymap, "mymap insert2");

    cout << endl << "insert 3 :" << endl;
    mymap.insert (it, NSP::pair<FIRST,SECOND>(FIRST(4), SECOND(400)));  // no max efficiency inserting
    print_map(mymap, "mymap");

    // third insert function version (range insertion):
    NSP::map<FIRST,SECOND> anothermap;
    cout << endl << "insert 4 :" << endl;
    anothermap.insert(mymap.begin(),mymap.find(FIRST(4)));
    print_map(anothermap, "anothermap");

}

void f3 ()
{
    cout << C_G << "# F3 : " << "up low bound" << C_W << endl;
    typedef NSP::map<FIRST,SECOND,COMP > type_map;
    type_map mymap;
    type_map::iterator itlow,itup;

    mymap[FIRST(0)]=0;
    mymap[FIRST(2)]=20;
    mymap[FIRST(4)]=40;
    mymap[FIRST(6)]=60;
    mymap[FIRST(8)]=80;

    print_map(mymap);
    FIRST x = 6;
    itlow=mymap.lower_bound (FIRST(x));  // itlow points to b
    itup=mymap.upper_bound (FIRST(x));   // itup points to e (not d!)
    cout << "low " << x << " " << *itlow << " up " << *itup << '\n';
    
    if (COMP()((*itup).first, (*itlow).first))
        mymap.erase(itup,itlow);        // erases [itlow,itup)
    else
        mymap.erase(itlow, itup);        // erases [itlow,itup)
    print_map(mymap);
    //cout << "max_size depend implemantation: " << myset.max_size() << endl;  
}

void f4 ()
{
    cout << C_G << "# F4 : " << "equal rang" << C_W << endl;
    typedef NSP::map<FIRST,SECOND, COMP > type_map;
    type_map mymap;

    mymap[FIRST(0)]=0;
    mymap[FIRST(2)]=20;
    mymap[FIRST(4)]=40;
    mymap[FIRST(6)]=60;
    mymap[FIRST(8)]=80;

    print_map(mymap);
    NSP::pair<type_map::iterator, type_map::iterator> p;
    FIRST x = 8;
    p = mymap.equal_range(FIRST(x));
    
     if( p.first != mymap.end())
    cout << "low " << x << " " << *p.first << '\n';
     if( p.second != mymap.end())
    cout << "up " << x << " " << *p.second << '\n';
   
    mymap.erase(p.first, p.second);        // erases [itlow,itup)
    print_map(mymap);
    
}

void f5 ()
{
    cout << C_G << "# F5 : " << "swap clear" << C_W << endl;
    typedef NSP::map<FIRST,SECOND, std::less<FIRST> > type_map;
    type_map map1;
    
    for(int i =0; i< 10; i++)
        map1[i] = i*10;
    print_map(map1, "map1");
    
    typedef NSP::map<FIRST,SECOND, std::less<FIRST> > type_map;
    type_map map2;
    
    for(int i =10; i< 20; i++)
        map2[i] = i*10;
    print_map(map2, "map2");

    map1.swap(map2);

    print_map(map1, "map1 map.swap");
    print_map(map2, "map2 map.swap");

    swap(map1, map2);
    
    print_map(map1, "map1 swap(a,b)");
    print_map(map2, "map2 swap(a,b)");

   
    map2.clear();

    cout << (map2 == map1) << endl;
    print_map(map1, "map1");
    print_map(map2, "map2 clear");
    
    map2 = map1;
    cout << (map2 == map1) << endl;
}


void f6 () {
    cout << C_G << "# F6 : " << "relational op" << C_W << endl;
    NSP::map<char,int> foo,bar;
    foo['a']=100;
    foo['b']=200;
    bar['a']=10;
    bar['z']=1000;

        cout << "foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}})\n : ";
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
    NSP::map<char,int> mymap;
    NSP::map<char,int>::key_compare mycomp = mymap.key_comp();
    mymap['a']=100;
    mymap['b']=200;
    mymap['c']=300;
    std::cout << "mymap contains:\n";
    char c_highest = mymap.rbegin()->first;     // key value of last element
    NSP::map<char,int>::iterator it = mymap.begin();
    do {
        std::cout << it->first << " => " << it->second << '\n';
    } while ( mycomp((*it++).first, c_highest) );

    std::cout << '\n';

    NSP::pair<char,int> highest = *mymap.rbegin();          // last element

    it = mymap.begin();
    do {
        std::cout << it->first << " => " << it->second << '\n';
    } while ( mymap.value_comp()(*it++, highest) );
}

void f8 () {
    cout << C_G << "# F8 : " << "find / count" << C_W << endl;
    NSP::map<char,int> mymap;
    NSP::map<char,int>::iterator it;

    mymap['a']=50;
    mymap['b']=100;
    mymap['c']=150;
    mymap['d']=200;

    it = mymap.find('b');
    if (it != mymap.end())
        mymap.erase (it);

    // print content:
    std::cout << "elements in mymap:" << '\n';
    std::cout << "a => " << mymap.find('a')->second << '\n';
    std::cout << "c => " << mymap.find('c')->second << '\n';
    std::cout << "d => " << mymap.find('d')->second << '\n';
    mymap ['a']=101;
    mymap ['c']=202;
    mymap ['f']=303;
    
    char c;
    for (c='a'; c<'h'; c++)
    {
        std::cout << c;
        if (mymap.count(c)>0)
            std::cout << " is an element of mymap.\n";
        else 
            std::cout << " is not an element of mymap.\n";
    }
}

void f9 () {
    cout << C_G << "# F9 : " << "allocator" << C_W << endl;
    int psize;
    NSP::map<const char, const int> mymap;
    NSP::pair<const char,const int>* p;

    //  allocate an array of 5 elements using mymap's allocator:
    p=mymap.get_allocator().allocate(5);

    // assign some values to array
    psize = sizeof(NSP::map<const char,const int>::value_type)*5;

    std::cout << "The allocated array has a size of " << psize / sizeof(p)<< " \n";

    mymap.get_allocator().deallocate(p,5);

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
