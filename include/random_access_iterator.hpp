#include <iterator>

namespace	ft
{
	// Iterator appelle random access iterator, qui appelle std::iterator_traits
	// et faut trouver un moyen de remplir iterator trait avec les bon type dedans

	template < typename iterator >
	class random_access_iterator
	{
		protected:
			typedef	std::iterator_traits<iterator>		traits_type;

		public:
			typedef				iterator										iterator_type;
			typedef	typename	std::random_access_iterator_tag		iterator_category;
			typedef	typename		traits_type::value_type									value_type;
			typedef	typename		traits_type::difference_type							difference_type;
			typedef	typename		traits_type::pointer									pointer;
			typedef	typename		traits_type::reference									reference;



		protected:
			iterator			_current;

		public:
			random_access_iterator() : _current(iterator()) { }
			random_access_iterator(const iterator& i) : _current(i) { }
	};

}



/*					STACK OVERFLOW ANSWER
	- Choose type of iterator which fits your container: input, output, forward etc.
	- Use base iterator classes from standard library. For example, std::iterator with
	random_access_iterator_tag.These base classes define all type definitions required by STL and
	do other work.

To avoid code duplication iterator class should be a template class and be parametrized by "value type", "pointer type", "reference type" or all of them (depends on implementation).

*/
