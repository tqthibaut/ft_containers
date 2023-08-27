/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthibaut <tthibaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:58:26 by tthibaut          #+#    #+#             */
/*   Updated: 2023/03/31 14:58:29 by tthibaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

namespace ft
{
	// class random_access_iterator_tag
	// {
	// };
	// class bidirectional_iterator_tag
	// {
	// };
	// class forward_iterator_tag
	// {
	// };
	// class input_iterator_tag
	// {
	// };
	// class output_iterator_tag
	// {
	// };

	// template <bool is_valid, typename T>
	// struct valid_iterator_tag_res
	// {
	// 	typedef T type;
	// 	const static bool value = is_valid;
	// };

	// template <typename T>
	// struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T>
	// {
	// };

	// template <>
	// struct is_input_iterator_tagged<ft::random_access_iterator_tag>
	// 	: public valid_iterator_tag_res<true, ft::random_access_iterator_tag>
	// {
	// };

	// template <>
	// struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
	// 	: public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag>
	// {
	// };

	// template <>
	// struct is_input_iterator_tagged<ft::forward_iterator_tag>
	// 	: public valid_iterator_tag_res<true, ft::forward_iterator_tag>
	// {
	// };

	// template <>
	// struct is_input_iterator_tagged<ft::input_iterator_tag>
	// 	: public valid_iterator_tag_res<true, ft::input_iterator_tag>
	// {
	// };

	// template <typename T>
	// struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T>
	// {
	// };

	// template <>
	// struct is_ft_iterator_tagged<ft::random_access_iterator_tag>
	// 	: public valid_iterator_tag_res<true, ft::random_access_iterator_tag>
	// {
	// };

	// template <>
	// struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>
	// 	: public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag>
	// {
	// };

	// template <>
	// struct is_ft_iterator_tagged<ft::forward_iterator_tag>
	// 	: public valid_iterator_tag_res<true, ft::forward_iterator_tag>
	// {
	// };

	// template <>
	// struct is_ft_iterator_tagged<ft::input_iterator_tag>
	// 	: public valid_iterator_tag_res<true, ft::input_iterator_tag>
	// {
	// };

	// template <>
	// struct is_ft_iterator_tagged<ft::output_iterator_tag>
	// 	: public valid_iterator_tag_res<true, ft::output_iterator_tag>
	// {
	// };

	// template <class InputIterator1, class InputIterator2>
	// bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
	// 							 InputIterator2 first2, InputIterator2 last2)
	// {
	// 	while (first1 != last1)
	// 	{
	// 		if (first2 == last2)
	// 			return false;
	// 		if (*first1 < *first2)
	// 			return true;
	// 		if (*first2 < *first1)
	// 			return false;
	// 		first1++;
	// 		first2++;
	// 	}
	// 	return (first2 != last2);
	// }

	// template <class InputIterator1, class InputIterator2>
	// bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	// {
	// 	/* on teste si vector 1 < vector 2 !*/
	// 	while (first1 != last1)
	// 	{
	// 		/* if vector 2 is empty OR 1 des valeurs de vector 2 est inférieure à la valeur de vector 1 -> vector 1 est supérieur !*/
	// 		if (first2 == last2 || *first2 < *first1)
	// 			return false;
	// 		else if (*first1 < *first2)
	// 			return true;
	// 		first1++;
	// 		first2++;
	// 	}
	// 	return (first2 != last2);
	// }

	// template <class InputIterator1, class InputIterator2, class Compare>
	// bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	// {
	// 	while (first1 != last1) {
	// 		if (first2 == last2)
	// 			return false;
	// 		if (comp(*first1, *first2))
	// 			return true;
	// 		if (comp(*first2, *first1))
	// 			return false;
	// 		first1++;
	// 		first2++;
	// 	}
	// 	return (first2 != last2);
	// }

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

};
