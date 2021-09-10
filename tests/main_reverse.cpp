#include "common_test.hpp"

int main () {

    cout << TNSP << endl;

    NSP::vector<int> myvector;
    for (int i=1; i<=10; i++) myvector.push_back(i);

    NSP::vector<int>::iterator from (myvector.begin());           
    NSP::vector<int>::iterator until (myvector.end());           

    int i = 5; 

    {
    NSP::reverse_iterator<NSP::vector<int>::iterator> rev_until (from);   
    NSP::reverse_iterator<NSP::vector<int>::iterator> rev_from (until); 
 
    cout << "myvector:";
    while (rev_from != rev_until)
        cout << ' ' << *rev_from++;
    cout << '\n';
    }
    
    {    
    NSP::reverse_iterator<NSP::vector<int>::iterator> rev_until (from);   
    NSP::reverse_iterator<NSP::vector<int>::iterator> rev_from (until); 

    cout << "from : " << *(rev_from)<< " = " << *(until - 1) << endl;
    cout << "until - 1 : " << *(rev_until - 1) << " = " << *(from) << endl;

    cout << "from + " << i << " : " << *(rev_from + i) << endl;
    cout << "until - " << i << " : " << *(rev_until - i) << endl;

    cout << "from += " << i << " : " << *(rev_from += i);
    cout << '\n';
    cout << "until -= " << i << " : " << *(rev_until -= i);
    cout << '\n';
    }
    {
    NSP::reverse_iterator<NSP::vector<int>::iterator> rev_from (until); 
    cout << "from [" << i << "] : " << rev_from[i] ;
    cout << '\n';
    }
    {
    
    cout << " -> " ;
    cout << '\n';

    std::map<int,string> numbers;
    numbers.insert (std::make_pair(1,"one"));
    numbers.insert (std::make_pair(2,"two"));
    numbers.insert (std::make_pair(3,"three"));

    typedef std::map<int,string>::iterator map_iter;

    NSP::reverse_iterator<map_iter> rev_end (numbers.begin());

    NSP::reverse_iterator<map_iter> rev_iterator (numbers.end());

    for ( ; rev_iterator != rev_end ; ++rev_iterator )
        cout << rev_iterator->first << ' ' << rev_iterator->second << '\n';
    cout << "== : " << (rev_iterator == rev_end);
    cout << '\n';
    }
    {
    NSP::vector<int> myvector;
    for (int i=0; i<10; i++) myvector.push_back(i);

    NSP::reverse_iterator<NSP::vector<int>::iterator> from(myvector.end()),until( myvector.begin());

    cout << "myvector has " << (until-from) << " elements.\n";
    cout << " from > until " << (from > until) << "\n";
    cout << " from < until " << (from < until) << "\n";
    cout << " from <= until " << (from <= until) << "\n";
    cout << " from >= until " << (from >= until) << "\n";
    cout << " from == until " << (from == until) << "\n";

    }
    return 0;
}
