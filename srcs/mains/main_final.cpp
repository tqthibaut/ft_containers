#include <iostream>
#include <string>
#include <deque>
#include <ctime>

// #include <iostream>
// #include "../include/color_define.hpp"
// #include <iomanip>
// #include <utility>

// #ifndef STD
// # define NAMESPACE ft
// # include "map.hpp"
// # include "vector.hpp"
// # define cout std::cout
// #else
// # define NAMESPACE std
// # include <vector>
// # include <map>
// #endif


#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

template <class Key, class T>
void	print_status_map(ft::map<Key, T>& lst)
{
	for (typename ft::map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}

template <class T>
void	print_status_vector(ft::vector<T>& lst)
{
	for (typename ft::vector<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

int main()
{

	time_t start, end;
	time(&start);

	clock_t t = clock();


	// Constructors
	std::cout << "***		CONSTRUCTORS		***\n";
	ft::vector<int> JOHN;
	ft::vector<int> BOB(5, 8);
	std::cout << "vector<int> BOB(5, 8) : ";
	for (size_t i = 0; i < BOB.size(); i++)
		std::cout << BOB[i] << ' ';
	std::cout << '\n';
	// for (vector<int>::iterator it = BOB.begin(); it <= BOB.end(); it++)
	// 	cout << *it << '|';
	//cout << "BOB END == "<<*(BOB.end());
	std::cout << '\n';
	std::cout << "vector<int> JOHN  (empty)\n";
	std::cout << "vector<int> MIKE(BOB) --> construction par copie\n";
	ft::vector<int> MIKE(BOB);
	std::cout << "Empty (JOHN) is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	std::cout << "BOB is empty? " << BOB.empty() << '\n';
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	std::cout << "MIKE STATUS:"; print_status_vector(MIKE);
	std::cout << "JOHN STATUS:"; print_status_vector(JOHN);
	std::cout << "BOB STATUS:"; print_status_vector(BOB);


	// RESIZE
	size_t	bob_resize = 2;
	std::cout << "\n***			RESIZE			***\n";
	BOB.resize(bob_resize);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";

	size_t	mike_resize = 9;
	bob_resize = 0;

	BOB.resize(bob_resize);
	std::cout << "BOB is empty now ? " << BOB.empty() << '\n';
	MIKE.resize(mike_resize, 3);
	/*
	*/
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_resize)
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;
	std::cout << "MIKE STATUS:"; print_status_vector(MIKE);
	std::cout << "JOHN STATUS:"; print_status_vector(JOHN);
	std::cout << "BOB STATUS:"; print_status_vector(BOB);

		// RESERVE
	std::cout << "\nRESERVE\n";

	size_t	john_reserve = 5;
	size_t	bob_reserve = 3;
	size_t	mike_reserve = 83;

	JOHN.reserve(john_reserve);
	BOB.reserve(bob_reserve);
	MIKE.reserve(mike_reserve);
	/*
	*/
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= john_reserve)
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_reserve)
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_reserve)
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	std::cout << "MIKE STATUS:"; print_status_vector(MIKE);
	std::cout << "JOHN STATUS:"; print_status_vector(JOHN);
	std::cout << "BOB STATUS:"; print_status_vector(BOB);

		//AT
	std::cout << "\n***			AT			***\n";
	try
	{
		std::cout << MIKE.at(2) << '\n';
		std::cout << MIKE.at(87) << '\n';
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		std::cout << "OOR error caught\n";
	}
	//std::cout << "Mike.at(2) == " << MIKE.at(2) << std::endl;
	std::cout << "MIKE STATUS:"; print_status_vector(MIKE);
	std::cout << "JOHN STATUS:"; print_status_vector(JOHN);
	std::cout << "BOB STATUS:"; print_status_vector(BOB);

	// FRONT / BACK
	std::cout << "\n***	***		FRONT / BACK		***	***\n";
	std::cout << "front() of MIKE : " << MIKE.front() << '\n';
	std::cout << "back() of MIKE : " << MIKE.back() << '\n';
	std::cout << "front() of BOB : " << BOB.front() << '\n';
	std::cout << "back() of BOB : " << BOB.back() << '\n';
	std::cout << "MIKE STATUS:"; print_status_vector(MIKE);
	std::cout << "JOHN STATUS:"; print_status_vector(JOHN);
	std::cout << "BOB STATUS:"; print_status_vector(BOB);

		//ASSIGN : Replaces the contents with count copies of value value
	std::cout << "\n***			ASSIGN			***\n";
	BOB.assign(42, 7);

	// 	//ASSIGN RANGE : Replaces the contents with copies of those in the
	// 	// range [first, last). The behavior is undefined if either argument is an iterator into *this.
	// std::cout << "\n***			ASSIGN RANGE			***\n";
	// vector<int>	assign_range;
	// assign_range.assign(8, 5);
	// assign_range.assign(BOB.begin() + 1, BOB.end() - 2);

	//EMPTY
	std::cout << "\n***			EMPTY			***\n";
	std::cout << "BOB is empty ? " << BOB.empty() << '\n';
	std::cout << "BOB at(41) : " << BOB.at(41) << '\n';

	//PUSH/POP_BACK
	std::cout << "\n***			PUSH/POP_BACK			***\n";
	std::cout << "MIKE STATUS:"; print_status_vector(MIKE);
	std::cout << "JOHN STATUS:"; print_status_vector(JOHN);
	std::cout << "BOB STATUS:"; print_status_vector(BOB);
	std::cout << "BOB.push_back(53)" << std::endl;
	BOB.push_back(53);
	std::cout << "last elem of BOB : " << BOB.back() << '\n';
	BOB.pop_back();
	std::cout << "last elem of BOB : " << BOB.back() << '\n';

	std::cout << "MIKE STATUS:"; print_status_vector(MIKE);
	std::cout << "JOHN STATUS:"; print_status_vector(JOHN);
	std::cout << "BOB STATUS:"; print_status_vector(BOB);

		//INSERT
	std::cout << "\n***			INSERT			***\n";
	ft::vector<int>	insert_in_me;
	for (int i = 0; i < 15; i++)
		insert_in_me.push_back(i);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		std::cout << insert_in_me.at(i) << ' ';
	std::cout << '\n';

	ft::vector<int>::iterator	tmp;
	tmp = insert_in_me.begin() + 4;
	insert_in_me.insert(tmp, 8, 42);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		std::cout << insert_in_me.at(i) << ' ';
	std::cout << '\n';

	ft::vector<int>::const_iterator const_it(insert_in_me.begin());
	std::cout << "Const it : " << std::endl;
	std::cout << *const_it << '\n';

		//INSERT
	std::cout << "\n***			INSERT			***\n";
	// ft::vector<int>	insert_in_me;
	for (int i = 0; i < 15; i++)
		insert_in_me.push_back(i);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		std::cout << insert_in_me.at(i) << ' ';
	std::cout << '\n';

	ft::vector<int>::iterator	tmp_it;
	tmp_it = insert_in_me.begin() + 4;
	insert_in_me.insert(tmp_it, 0, 78);
	insert_in_me.insert(tmp_it, 9, 78);
	print_status_vector(insert_in_me);

	//INSERT RANGE
	std::cout << "\n***			INSERT RANGE			***\n";
	ft::vector<int>	insert_range;
	ft::vector<int>	insert_bis;

	for (int i = 0; i < 6; i++)
		insert_bis.push_back(3 * i);
	for (size_t i = 0; i < insert_bis.size(); i++)
		std::cout << "VECT TO INSERT == " << insert_bis[i] << ' ';
	std::cout << '\n';

	insert_range.insert(insert_range.begin() + 5, insert_in_me.begin(), insert_in_me.end());
	print_status_vector(insert_range);
	std::cout << '\n';


	//ERASE
	std::cout << "\n***			ERASE			***\n";
	ft::vector<int>	erase_in_me;
	for (int i = 0; i < 15; i++)
		erase_in_me.push_back(2 * i);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			std::cout << ' ';
		std::cout << erase_in_me.at(i) << ' ';
	}
	std::cout << '\n';

	erase_in_me.erase(erase_in_me.begin() + 7);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			std::cout << ' ';
		std::cout << erase_in_me.at(i) << ' ';
	}
	std::cout << '\n';

	erase_in_me.erase(erase_in_me.begin() + 2, erase_in_me.begin() + 6);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			std::cout << ' ';
		std::cout << erase_in_me.at(i) << ' ';
	}
	std::cout << '\n';

	//SWAP
	std::cout << "\n***			SWAP			***\n";
	print_status(BOB);
	print_status(MIKE);
	BOB.swap(MIKE);
	/*
	*/
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	MIKE.swap(JOHN);
	/*
	*/
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	//CLEAR
	std::cout << "\n***			CLEAR			***\n";
	JOHN.clear();
	MIKE.clear();
	print_status(MIKE);
	print_status(JOHN);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	//NON MEMBER Functions
	std::cout << "\n***		NON MEMBER functions		***\n";
	swap(BOB, MIKE);
	/*
	*/
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "INSUFFICIENT CAPACITY\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	//RELATIONAL OPERATORS
	std::cout << "\n***		RELATIONAL OPERATORS		***\n";
	vector<int> MIKE_2(MIKE);
	std::cout << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	std::cout << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';

	std::cout << "\n***		Real Vector		***\n";
	vector<int> real;
	real.assign(5, 7);
	for (vector<int>::iterator it = real.begin(); it != real.end(); it++)
		std::cout << *it << " ";
	std::cout << '\n';

	std::cout << std::endl;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////MAP///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Constructors
	std::cout << "***		CONSTRUCTORS		***\n";

	Departements.insert(Ain);
	Departements.insert(ft::pair<int, std::string>(78, "Yvelines"));
	Departements.insert(ft::pair<int, std::string>(48, "Lozère"));
	Departements.insert(ft::pair<int, std::string>(78, "PAS BON ERROR"));
	Departements.insert(ft::pair<int, std::string>(-666, "Mordor"));
	Departements.insert(ft::pair<int, std::string>(28, "Mordor"));
	Departements.insert(ft::pair<int, std::string>(60, "Oise"));
	Departements.insert(ft::pair<int, std::string>(39, "Jura"));

	map_iter = Departements.begin();
	while (map_iter != Departements.end())
	{
		std::cout << map_iter->first << ", " << map_iter->second << '\n';
		map_iter++;
	}

	ft::map<int, std::string>				test_copy(Departements);
	ft::map<int, std::string>::iterator	map_iter2;
	map_iter2 = test_copy.begin();
	while (map_iter2 != test_copy.end())
	{
		std::cout << map_iter2->first << ", " << map_iter2->second << '\n';
		map_iter2++;
	}

	// Lookups
	std::cout << "COUNT 78 == |" << Departements.count(78) << "|\n";
	std::cout << "FIND 78 == |" << Departements.find(78)->second << "|\n";

		// Lower, Upper et Equal bound
	std::cout << "LOWER BOUND 35 == |" << Departements.lower_bound(35)->second << "|\n";
	std::cout << "UPPER BOUND 35 == |" << Departements.upper_bound(35)->second << "|\n";
	ft::pair<ft::map<char,int>::iterator, ft::map<char,int>::iterator>	ret;
	ret = Departements.upper_bound(35);
	std::cout << "EQUAL BOUND 35 == lower:|" << ret.first->first << ", "  << ret.first->second << "|; upper|";
	std::cout <<  ret.second->first << ", "  << ret.second->second << "|\n";



	// Modifiers
	std::cout << "***		MODIFIERS		***\n";

		// Erase
	std::cout << "Erase:\n(erase(27+1) + erase(iterator to 78))";
	Departements.erase(28); //par key
	Departements.erase(Departements.find(78)); //par iterateur

	map_iter = Departements.begin();
	std::cout << "DEPARTEMENTS : *****************\n";
	while (map_iter != Departements.end())
	{
		std::cout << map_iter->first << ", " << map_iter->second << '\n';
		map_iter++;
	}

		// Swap
	std::cout << "Swap Departement et copy\n"
	Departements.swap(test_copy.begin());

	map_iter = Departements.begin();
	std::cout << "DEPARTEMENTS : *****************\n";
	while (map_iter != Departements.end())
	{
		std::cout << map_iter->first << ", " << map_iter->second << '\n';
		map_iter++;
	}

	test_copy.clean();
	std::cout << "CLEAN test_copy : Empty ? " << test_copy.empty() << "\n";


	// Observers
	ft::map<int, std::string>::key_compare		mycomp = Departements.key_comp();


	char highest = Departements.rbegin()->first;     // key value of last element

	std::cout << "Departements contains:\n";
	ft::map<char,int>::iterator it = mymap.begin();
	do
	{
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );

	std::cout << '\n';

	std::cout << "Departements contains:\n";

	ft::pair<int, std::string> highest = *Departements.rbegin();          // last element

	ft::map<int, std::string>::iterator it = Departements.begin();
	do
	{
		std::cout << it->first << " => " << it->second << '\n';
	}
	while ( Departements.value_comp()(*it++, highest) );

	//
	ft::map<char,int> foo,bar;
	foo['a']=100;
	foo['b']=200;
	bar['a']=10;
	bar['z']=1000;

	// foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////STACK///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Constructors
	std::cout << "***		CONSTRUCTORS		***\n";
	ft::stack<float>		stack_float;
	std::cout << "STACK_FLOAT" << print_status(stack_float);

	ft::vector<std::string>		vector_string;
	vector_string.push_back("Booba");
	vector_string.push_back("Kaaris");
	vector_string.push_back("PNL");
	vector_string.push_back("LaFouine");
	vector_string.push_back("Oxmo");
	std::cout << "VECT_STRNG == " << print_status(stack_float);
		// Construction par copie
	ft::stack<std::string>		stack_string(vector_string);

	// MODIFIERS & OTHERS
	stack_float.push(7.8);
	stack_float.push(4.2);
	print_status(stack_float);
	stack_float.pop();
	ft::stack<std::string>	stack_string2;
	ft::stack<std::string> stack_string2 = stack_string;
	std::cout << "stack_str == stack_str2 ? --> " << (stack_string == stack_string2) << "\n";
	std::cout << "stack_str >= stack_str2 ? --> " << (stack_string >= stack_string2) << "\n";
	std::cout << "stack_str <= stack_str2 ? --> " << (stack_string <= stack_string2) << "\n";
	std::cout << "stack_str != stack_str2 ? --> " << (stack_string != stack_string2) << "\n";
	stack_string2.pop();
	std::cout << "STACK_STRING2 after pop : ";
	print_status(stack_string2);
	std::cout << "stack_str == stack_str2 ? --> " << (stack_string == stack_string2) << "\n";
	std::cout << "stack_str >= stack_str2 ? --> " << (stack_string >= stack_string2) << "\n";
	std::cout << "stack_str <= stack_str2 ? --> " << (stack_string <= stack_string2) << "\n";
	std::cout << "stack_str != stack_str2 ? --> " << (stack_string != stack_string2) << "\n";
	std::cout << "stack_str >= stack_str2 ? --> " << (stack_string > stack_string2) << "\n";
	std::cout << "stack_str <= stack_str2 ? --> " << (stack_string < stack_string2) << "\n";

	time(&end);

	// Calculating total time taken by the program.
	double time_taken = double(end - start);
	std::cout << "Time taken by program is : " << std::fixed << time_taken;
	std::cout << " sec " << std::endl;


	t = clock() - t;
	std::cout << "\n\nTemps d'execution du programme : " << (((float)t/CLOCKS_PER_SEC) * 1000) << " millisecondes."<< std::endl;

	return(0);
}

