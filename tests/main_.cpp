#include <iostream>
#include <string>
#include <deque>

#ifndef FT //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
    #define NSP "std"
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
	#include "set.hpp"
    #define NSP "ft"
#endif

#include <stdlib.h>

#define N 10000
#define MAX_RAM 1294967296
#define BUFFER_SIZE 8096

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
    public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
    std::cout << "Test " << NSP << " : " << std::endl;
	const int seed = atoi(argv[1]);
	srand(seed);

    std::cout << "seed is " << seed << std::endl;
	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::vector<Buffer> copy_vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;
	ft::set<int> set_int;

    std::cout << "- push_back " << COUNT << " elements in vector_buffer" << std::endl;
	for (int i = 0; i < COUNT; i++) {
		vector_buffer.push_back(Buffer());
	}

    std::cout << "- modify " << COUNT << " elements in vector_buffer" << std::endl;
	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = i;
	}

    copy_vector_buffer = vector_buffer;
    std::cout << "- swap vector_buffer with empty vector";
	ft::vector<Buffer>().swap(copy_vector_buffer);
	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			copy_vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
        std::cout << " OK" << std::endl;
		//NORMAL ! :P
	}

    std::cout << "- insert " << COUNT << " elements in map_int & set_int ";
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
		set_int.insert(i);
	}
    std::cout << std::endl;
    std::cout << "- sum random value from map, set and vector: ";
	int sum_map = 0;
	int sum_vec = 0;
	int sum_set = 0;
	for (int i = 0; i < N; i++)
	{
		int access = rand() % (COUNT - 1) ;
		sum_map += map_int[access];
		sum_vec += vector_buffer[access].idx;
		sum_set += *(set_int.find(access));
	}

    std::cout << "sum_map = "  << sum_map << ", sum_set = " <<  sum_set << ", sum_vec = " <<  sum_vec << " (should be constant with the same seed)" << std::endl;
	{
		ft::map<int, int> map_copy = map_int;
        std::cout << "[map_copy = map_int] =>" << ((map_copy == map_int) ? "same :)" : "not same :(" ) << std::endl;
		ft::set<int> set_copy = set_int;
        std::cout << "[set_copy = set_int] =>" << ((set_copy == set_int) ? "same :)" : "not same :(" ) << std::endl;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);

	std::cout << "MutantStack : ";
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++) {
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}
