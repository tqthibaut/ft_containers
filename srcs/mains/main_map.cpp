#include <iostream>
#include <string>
#include <deque>
#include <ctime>

// # ------ GRIS ------ #
#define GRAY "\033[90m"
#define REALGRAY "\033[38;2;128;128;128m"
#define SILVER "\033[38;2;192;192;192m"
#define LIGHTSLATEGRAY "\033[38;2;119;136;153m"
// # ------ ROUGE ------ #
#define RED "\033[91m"
#define ORANGE "\033[38;2;255;165;0m"
#define FIREBRICK "\033[38;2;178;34;34m"
#define INDIANRED "\033[38;2;205;92;92m"
//  # ------ VERT ------ #
#define GREEN "\033[92m"
#define LIMEGREEN "\033[38;2;50;205;50m"
#define FORESTGREEN "\033[38;2;34;139;34m"
#define SPRINGGREEN "\033[38;2;0;255;127m"
// # ------ JAUNE ------ #
#define YELLOW "\033[93m"
#define KHAKI "\033[38;2;240;230;140m"
#define REALYELLOW "\033[38;2;255;255;0m"
#define GOLD "\033[38;2;255;215;0m"
// # ------ BLEU ------ #
#define BLUE "\033[94m"
#define REALBLUE "\033[38;2;0;0;255m"
#define DEEPSKYBLUE "\033[38;2;0;191;255m"
#define ROYALBLUE "\033[38;2;65;105;225m"
// # ------ VIOLET ------ #
#define PURPLE "\033[95m"
#define FUCHSIA "\033[38;2;255;0;255m"
#define DARKVIOLET "\033[38;2;148;0;211m"
#define DARKMAGENTA "\033[38;2;139;0;139m"
// # ------ CYAN ------ #
#define CYAN "\033[96m"
#define AQUAMARINE "\033[38;2;127;255;212m"
#define PALETURQUOISE "\033[38;2;175;238;238m"
#define TEAL "\033[38;2;0;128;128m"
//# ------ RESET ------ #
#define RESET "\033[0m"

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


#ifndef FT //CREATE A REAL STL EXAMPLE
	#define FT 0
	#include "../../include/map.hpp"
	#include "../../include/stack.hpp"
	#include "../../include/vector.hpp"
#else
	namespace ft = std;
	#include <stack>
	#include <map>
	#include <vector>
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
void	print_status_map(ft::map<Key, T>& lst, std::string tree_name)
{
	std::cout << YELLOW << "\ncontenu de >" << tree_name << "< :\n" << RESET;
	for (typename ft::map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << ' ' << it->second << ", ";
	std::cout << '\n';
}

template<typename T>
void show_v(ft::vector<T> & v)
{
	std::cout << "v = { ";
	//for (int n : v)
	//    std::cout << n << ", ";
	for (typename ft::vector<T>::iterator i = v.begin(); i != v.end(); i++)
		std::cout << *i << ", ";
	std::cout << "}; \n";
};

template<typename T>
void show_v(std::string str, ft::vector<T> & v)
{
	std::cout << str <<" = { ";
	//for (int n : v)
	//    std::cout << n << ", ";
	for (typename ft::vector<T>::iterator i = v.begin(); i != v.end(); i++)
		std::cout << *i << ", ";
	std::cout << "}; \n";
};


template <typename T>
void print(ft::stack<T> v)
{
	std::cout << "Stack size : " << v.size();
	if (v.size() > 0)
		std::cout << " top = " << v.top();
	std::cout << std::endl;
}


int main()
{
	if (FT == 0)
		std::cout << "NAMESPACE == FT\n\n";
	else
		std::cout << "NAMESPACE == STD\n\n";

	time_t start, end;
	time(&start);

	clock_t t = clock();

	std::cout << "................................................" << std::endl;
	std::cout << "....................VECTOR......................" << std::endl;
	std::cout << "................................................" << std::endl;

	// Create a vector containing integers
	ft::vector<int> v;
	ft::vector<int> vEmpty;

	// Add two more integers to vector
	v.push_back(25);
	v.push_back(13);
	v.push_back(7);

	// Print out the vector
	// std::cout << "v = { ";
	// for (int n : v)
	//     std::cout << n << ", ";
	// std::cout << "}; \n";
	std::cout << "v = { ";
	for (ft::vector<int>::size_type i = 0; i != v.size(); i++)
		std::cout << v[i] << ", ";
	std::cout << "}; \n";

	std::cout << "check Template function : show_v: " ; show_v(v);

//	std::cout << "v[0] = " << v[0] << std::endl;
//	std::cout << "v[1] = " << v[1] << std::endl;

//	NS::vector<int> v2 = v;

//	std::cout << "v2[0] = " << v2[0] << std::endl;





	ft::vector<int> u;

	u.push_back(1);
	u.push_back(2);
	u.push_back(3);
	u.push_back(4);
	u.push_back(5);
	u.push_back(6);
	u.push_back(7);
	u.push_back(8);
	u.push_back(9);

		/*
		MEMBER FUNCTIONS
		~~~~~~~~~~~~~~~~
		(constructor)
		(destructor)
		operator= (assign content)
		*/

	std::cout << "Copy constructor (range)  : "; show_v(u);
	std::cout << "Copy constructor (range)  : "; ft::vector<int> w(u.begin(), u.end()); show_v("w", w);


		/*
		Iterators:
		~~~~~~~~~~
		begin			v	const	v
		end				v	const	v
		rbegin			v	const	v
		rend			v	const	v
		cbegin			x (c++11)
		cendy			x (c++11)
		crbegin			x (c++11)
		crend			x (c++11)
		*/

	std::cout << "check Iterators : begin   : " << *(v.begin()) << "\n";
	std::cout << "check Iterators : end     : " << *(v.end() - 1) << "\n";
	std::cout << "check Iterators : rbegin  : " << *(v.rbegin()) << "\n";
	std::cout << "check Iterators : rend    : " << *(v.rend() - 1) << "\n";
	std::cout << "................................................" << std::endl;

		/*
		Capacity:
		~~~~~~~~~
		size			v
		max_size		v
		resize			v
		capactity		v
		empty			v
		reserve			v
		shrink_to_fit	x (c++11)
		*/

	std::cout << "check Capacity : size             : " << (v.size()) << "\n";
	std::cout << "check Capacity : capacity         : " << (v.capacity()) << "\n";
	std::cout << "check Capacity : max_size         : " << (v.max_size()) << "\n";
	std::cout << "check Capacity : resize-1 (5)     : "; (v.resize(5)); show_v(v);
	std::cout << "check Capacity : capacity         : " << (v.capacity()) << "\n";
	std::cout << "check Capacity : resize-2 (2)     : "; (v.resize(2)); show_v(v);
	std::cout << "check Capacity : capacity         : " << (v.capacity()) << "\n";
	std::cout << "check Capacity : resize-3 (7,1)   : "; (v.resize(7, 1)); show_v(v);
	std::cout << "check Capacity : capacity         : " << (v.capacity()) << "\n";
	std::cout << "check Capacity : resize-4 (9,2)   : "; (v.resize(9, 2)); show_v(v);
	std::cout << "check Capacity : capacity         : " << (v.capacity()) << "\n";
	std::cout << "check Capacity : resize-5         : size : " << (v.size()) << "\n";
	std::cout << "check Capacity : capacity         : " << (v.capacity()) << "\n";
	std::cout << "check Capacity : empty-1          : " << (v.empty()) << "\n";
	std::cout << "check Capacity : empty-2          : " << (vEmpty.empty()) << "\n";
	std::cout << "check Capacity : reserve (8)      : " ; (v.reserve(8)); show_v(v);
	std::cout << "check Capacity : capacity         : " << (v.capacity()) << "\n";
	std::cout << "check Capacity : reserve (25)     : " ; (v.reserve(25)); show_v(v);
	std::cout << "check Capacity : capacity         : " << (v.capacity()) << "\n";
	std::cout << "................................................" << std::endl;

		/*
		Element access:
		~~~~~~~~~~~~~~~
		operator[]		v	const	v
		at				v	const	v
		front			v	const	v
		back			v	const	v
		data			v	const	v
		*/

	std::cout << "check Access : operator[] ([1])   : " << (v[1]) << "\n";
	std::cout << "check Access : at (1)             : " << (v.at(1)) << "\n";
	std::cout << "check Access : front              : " << (v.front()) << "\n";
	std::cout << "check Access : back               : " << (v.back()) << "\n";
	std::cout << "check Access : data               : " << (v.data()) << "\n";
	std::cout << "check Access : assign[]           : " ; (v[2]=42) ; show_v(v);
	std::cout << "................................................" << std::endl;

		/*
		Modifiers:
		~~~~~~~~~~
		assign				fill	v	range	v
		push_back		v
		pop_back		v
		insert			v	fill	v	range	v
		erase			v	range	v
		swap			v
		clear			v
		emplace			x (c++11)
		emplace_back	x (c++11)
		*/

	std::cout << "check Modifiers : assign u "; show_v("u", u);
	std::cout << "check Modifiers : assign u - capacity : " << (u.capacity()) << " size : " << (u.size()) << "\n";
	std::cout << "check Modifiers : assign u "; show_v(v);
	std::cout << "check Modifiers : assign v - capacity : " << (v.capacity()) << " size : " << (v.size()) << "\n";
	v.assign(5, 0);
	show_v(v);
	std::cout << "check Modifiers : assign v.assign(5,0)    :";
	std::cout << "check Modifiers : assign u "; show_v(v);
	std::cout << "check Modifiers : assign v - capacity : " << (v.capacity()) << " size : " << (v.size()) << "\n";

	std::cout << std::endl;

	std::cout << "check Modifiers : pop_back        : " ; (v.pop_back()) ; show_v(v);
	std::cout << "check Modifiers : insert (p1,7)   : " ; (v.insert(v.begin() + 1, 7)) ; show_v(v);
	std::cout << "check Capacity  : capacity        : " << (v.capacity()) << " size : " << (v.size()) << "\n";;
	std::cout << "check Modifiers : insert (p4,4,8) : " ; (v.insert(v.begin() + 4, 4, 8)) ; show_v(v);
	std::cout << "check Capacity  : capacity        : " << (v.capacity()) << " size : " << (v.size()) << "\n";
	std::cout << "check Modifiers : insert (p4,10,9) : " ; (v.insert(v.begin() + 4, 10, 9)) ; show_v(v);
	std::cout << "check Capacity  : capacity        : " << (v.capacity()) << " size : " << (v.size()) << "\n";
	std::cout << "check Modifiers : insert (p4,45,3) : " ; (v.insert(v.begin() + 4, 45, 3)) ; show_v(v);
	std::cout << "check Capacity  : capacity        : " << (v.capacity()) << " size : " << (v.size()) << "\n";

	// NS::vector<int> u;

	// u.push_back(1);
	// u.push_back(2);
	// u.push_back(3);
	// u.push_back(4);
	// u.push_back(5);
	// u.push_back(6);
	// u.push_back(7);
	// u.push_back(8);
	// u.push_back(9);

	std::cout << "check Modifiers : insert (p4,b,e) : " ; (v.insert(v.begin() + 4, v.begin(), v.end())) ; show_v(v);
	std::cout << "check Capacity  : capacity        : " << (v.capacity()) << " size : " << (v.size()) << "\n";
	std::cout << "check Modifiers : vEmpty size = " << vEmpty.size() << std::endl;
//  std::cout << "check Modifiers : pop_back        : " ; (vEmpty.pop_back()) ; show_v("vEmpty", vEmpty); //segfault with std
	std::cout << "check Modifiers : erase (1)       : " ; (v.erase(v.begin() + 1)) ; show_v(v);
	std::cout << "check Modifiers : erase (1,3)     : " ; (v.erase(v.begin() + 1, v.begin() + 3)) ; show_v(v);
	std::cout << "check Modifiers : erase - size    : " << (v.size()) << std::endl;
//    std::cout << "check Modifiers : erase (3,1)     : " ; (v.erase(v.begin() + 3, v.begin() + 1)) ; show_v(v);  //undefined behavior
//    std::cout << "check Modifiers : erase - size    : " << (v.size()) << std::endl;
	std::cout << "check Modifiers : swap            : " ; (v.swap(vEmpty)) ; show_v("vEmpty", vEmpty); show_v(v);
	v.swap(vEmpty); show_v(v);
	std::cout << "check Modifiers : clear           : " ; (v.clear()) ; show_v(v);
	std::cout << "check Modifiers : clear  (size)   : " << (v.size()) << std::endl;
	std::cout << "................................................" << std::endl;



	/*
	Non-member function overloads:
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	relational operators

		template <class T, class Alloc>  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	swap
	*/

	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (2,200);   // two ints with a value of 200

	std::cout << "check relational op : ==      : "; if (foo==bar) std::cout << "foo and bar are equal";                std::cout << "\n";
	std::cout << "check relational op : !=      : "; if (foo!=bar) std::cout << "foo and bar are not equal";            std::cout << "\n";
	std::cout << "check relational op : <       : "; if (foo< bar) std::cout << "foo is less than bar";                 std::cout << "\n";
	std::cout << "check relational op : >       : "; if (foo> bar) std::cout << "foo is greater than bar";              std::cout << "\n";
	std::cout << "check relational op : <=      : "; if (foo<=bar) std::cout << "foo is less than or equal to bar";     std::cout << "\n";
	std::cout << "check relational op : >=      : "; if (foo>=bar) std::cout << "foo is greater than or equal to bar";  std::cout << "\n";


	std::cout << "................................................" << std::endl;
	std::cout << ".....................MAP........................" << std::endl;
	std::cout << "................................................" << std::endl;

	ft::pair<int, std::string>			Ain(1, "Ain");
	ft::map<int, std::string>			Departements;
	ft::map<int, std::string>::iterator	map_iter;

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
	print_status_map(Departements, "DEPARTEMENTS");

	ft::map<int, std::string>				test_copy(Departements);
	print_status_map(test_copy, "TEST_COPY");

	// Element Access
	std::cout << GREEN << "***************\nELEMENT ACCESS\n***************\n" << RESET;

		// map.at(key) function
	std::cout << "TEST AT FUNCTION:\n";
	std::cout << "1) Departement at 48 == " << Departements.at(48) << "\n";
	std::cout << "2) Departement at 42 == ";
	try {
		std::cout << Departements.at(42) << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "std::out_of_range caught\n";
	}
	std::cout << "3) Departement at 60 == " << Departements.at(60) << "\n";

		// map[key] operator
	std::cout << "\nTEST OPERATOR map[] :\n";
	std::cout << "1) Departement[48] == " << Departements[48] << "\n";
	std::cout << "2) Departement[42] == " << Departements[42] << "\n";
	std::cout << "note: operator[] returns a ref to the map value if something is found, OR insert an empty pair\n";
	std::cout << "2bis) Departement[42] = \"Loire\" == ";
	std::cout << (Departements[42] = "Loire") << "\n";
	std::cout << "3) Departement[60] == " << Departements[60] << "\n";
	print_status_map(Departements, "DEPARTEMENTS");



	// Lookups
	std::cout << GREEN << "***************\nLOOKUPS\n***************\n" << RESET;
	std::cout << "COUNT 78 == |" << Departements.count(78) << "|\n";
	std::cout << "FIND 78 == |" << Departements.find(78)->second << "|\n";

		// Lower, Upper et Equal bound
	std::cout << "LOWER BOUND 35 == |" << Departements.lower_bound(35)->second << "|\n";
	std::cout << "UPPER BOUND 35 == |" << Departements.upper_bound(35)->second << "|\n";




	// Modifiers
	std::cout << GREEN << "***************\nMODIFIERS\n***************\n" << RESET;

		// Erase
	std::cout << TEAL << "Erase:\n" << RESET;
	std::cout << "1) (erase(27+1) + erase(iterator to 78)).";
	Departements.erase(28); //par key
	Departements.erase(Departements.find(78)); //par iterateur
	print_status_map(Departements, "Departements");

		// Swap
	std::cout << TEAL << "\nSwap Departement et test_copy\n" << RESET;
	print_status_map(test_copy, "test_copy");
	Departements.swap(test_copy);
	std::cout << "\nAFTER SWAP:";
	print_status_map(test_copy, "test_copy");


	map_iter = Departements.begin();
	std::cout << "DEPARTEMENTS : *****************\n";
	while (map_iter != Departements.end())
	{
		std::cout << map_iter->first << ", " << map_iter->second << '\n';
		map_iter++;
	}

	test_copy.clear();
	std::cout << "CLEAN test_copy : Empty ? " << test_copy.empty() << "\n";
	print_status_map(test_copy, "test_copy");


	// Observers
	ft::pair<int, std::string> highest = *Departements.rbegin();          // last element
	// ft::map<int, std::string>::key_compare		mycomp = Departements.key_comp();

	std::cout << "Departements contains:\n";
	ft::map<int, std::string>::iterator it = Departements.begin();
	do
	{
		std::cout << it->first << " => " << it->second << '\n';
	} while ( Departements.value_comp()((*it++), highest) );


	// int highest = Departements.rbegin()->first;	// key value of last element
	std::cout << "HIGHEST IN DEPARTEMENT == " << Departements.rbegin()->first << "\n";
	// std::cout << '\n';

	// std::cout << "Departements contains:\n";


	// ft::map<int, std::string>::iterator it = Departements.begin();
	// do
	// {
	// 	std::cout << it->first << " => " << it->second << '\n';
	// }
	// while ( Departements.value_comp()(*it++, highest) );

	//
{	ft::map<char,int> foo,bar;
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
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";}

std::cout << "................................................" << std::endl;
std::cout << "....................STACK......................." << std::endl;
std::cout << "................................................" << std::endl;


	ft::stack<int> v1;
	std::cout << "v1 (empty)	: "; print(v1);

	std::cout << "v1.push(5);\n"; v1.push(5);

	ft::stack<int> v2(v1);
	std::cout << "v2(v1)		: "; print(v2);

	ft::stack<int> v3;
	v3 = v2;
	std::cout << "v3 = v2		: "; print(v3);

	for (int i = 0; i < 1000; i++)
		v1.push(i);
	std::cout << "Loop test		: "; print(v1);
	v1.pop();
	v1.pop();
	v1.pop();
	v1.pop();
	v1.pop();
	v1.pop();
	v1.pop();
	v1.pop();
	std::cout << "pop test		: "; print(v1);

	std::cout << "(v1 == v2)	: " << (v1 == v2) << "\n";
	std::cout << "(v1 != v2)	: " << (v1 != v2) << "\n";
	std::cout << "(v1 < v2)	: " << (v1 < v2) << "\n";
	std::cout << "(v1 <= v2)	: " << (v1 <= v2) << "\n";
	std::cout << "(v1 > v2)	: " << (v1 > v2) << "\n";
	std::cout << "(v1 >= v2)	: " << (v1 >= v2) << "\n";

	time(&end);

	// Calculating total time taken by the program.
	double time_taken = double(end - start);
	std::cout << "Time taken by program is : " << std::fixed
		 << time_taken;
	std::cout << " sec " << std::endl;


	t = clock() - t;
	std::cout << "\n\nTemps d'execution du programme : " << (((float)t/CLOCKS_PER_SEC) * 1000) << " millisecondes."<< std::endl;


}
