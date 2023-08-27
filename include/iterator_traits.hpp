#pragma once

#include <iterator>
#include <cstddef>

namespace ft {

	// struct random_access_iterator_tag : public std::random_access_iterator_tag {};

	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t							difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t							difference_type;
		typedef T									value_type;
		typedef const T*									pointer;
		typedef const T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

/*
	Appel d'iterator categorie permettant aux fonctions exterieurs de
	vérifier et de retourner le taf std::iterator correspondant.
*/
	// template<typename Iter>
    // typename iterator_traits<Iter>::iterator_category
    // iterator_category(const Iter&)
    // {
	// 	return (typename iterator_traits<Iter>::iterator_category());
	// }
};
