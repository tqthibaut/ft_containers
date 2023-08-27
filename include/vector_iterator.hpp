/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthibaut <tthibaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:58:39 by tthibaut          #+#    #+#             */
/*   Updated: 2023/03/31 14:58:40 by tthibaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "Vector.hpp"


#pragma once

#include "iterator_traits.hpp"

namespace	ft
{
	template <typename T>
	class	vectorIterator
	{

		public:
			typedef typename	std::random_access_iterator_tag		iterator_category;
			typedef T		value_type;
			typedef T*		pointer;
			typedef T&		reference;
			typedef const T*	const_pointer;
			typedef	const T&	const_reference;
			typedef	std::ptrdiff_t	difference_type;
			typedef size_t										size_type;

		private:
			pointer	_ptr;

		public:
			vectorIterator() : _ptr(NULL) {};
			vectorIterator(vectorIterator<T> const & cpy) : _ptr(cpy.getPtr()) { }
			vectorIterator(pointer	ptr) : _ptr(ptr) {};
			vectorIterator & operator=(vectorIterator<T> const & rhs)
			{
				this->_ptr = rhs.getPtr();
				return *this;
			}

			operator vectorIterator<T const>() const { return vectorIterator<T const>(this->_ptr); }

			~vectorIterator() {}

			pointer	getPtr() const {return (this->_ptr);}



		public:
			//prefixe operator
			vectorIterator&	operator++()
			{
				this->_ptr++;
				return *this;
			}
			//post-fix operator
			vectorIterator	operator++(int)
			{
				vectorIterator iteratorcpy = *this;
				++this->_ptr;

				// ++(*this);
				return iteratorcpy;
			}

			//prefixe operator
			vectorIterator&	operator--()
			{
				_ptr--;
				return *this;
			}
			//post-fix operator
			vectorIterator	operator--(int)
			{
				vectorIterator iteratorcpy = *this;
				--this->_ptr;
				return iteratorcpy;
			}

			reference	operator[](difference_type index) const
			{
				return *(*this + index);
			}

			pointer	operator->()
			{
				return _ptr;
			}

			reference	operator*()
			{
				return (*this->_ptr);
			}

			// reference	operator*(int)
			// {
			// 	return *_ptr;
			// }

			bool	operator==(const vectorIterator& other) const
			{
				return (this->_ptr == other.getPtr());
			}

			bool	operator!=(const vectorIterator& other) const
			{
				// return (this->_ptr != other.getPtr());
				return !(operator==(other));
			}

			vectorIterator &	operator+=(difference_type n)
			{
				this->_ptr += n;
				return (*this);
			}

			vectorIterator	operator+(difference_type n) const
			{
				// return vectorIterator(_ptr + n);
				return (this->_ptr + n);
			}

			difference_type		operator+(const vectorIterator & rhs) const
			{
				return (this->_ptr + rhs.getPtr());
			}

			vectorIterator &	operator-=(difference_type n)
			{
				this->_ptr -= n;
				return (*this);
			}

			vectorIterator		operator-(difference_type n) const
			{
				return vectorIterator(_ptr - n);
			}

			difference_type		operator-(const vectorIterator & rhs) const
			{
				return (this->_ptr - rhs.getPtr());
			}

			bool	operator<(const vectorIterator& rhs) const
			{
				return (this->_ptr < rhs.getPtr());
			}

			bool	operator<=(const vectorIterator& rhs) const
			{
				return (this->_ptr <= rhs.getPtr());
			}

			bool	operator>(const vectorIterator& rhs) const
			{
				return (this->_ptr > rhs.getPtr());
			}

			bool	operator>=(const vectorIterator& rhs) const
			{
				return (this->_ptr >= rhs.getPtr());
			}
	};

		template<class T>
		vectorIterator<T> operator+(typename vectorIterator<T>::difference_type n, const vectorIterator<T> &rhs)
		{ return rhs + n; }

		// template<class T>
		// vectorIterator<T> operator-(typename vectorIterator<T>::difference_type n, const vectorIterator<T> &rhs)
		// { return rhs - n; }

		template< typename Iter1, typename Iter2 >
		typename ft::vectorIterator<Iter1>::difference_type operator-(const vectorIterator<Iter1> &lhs, const vectorIterator<Iter2> &rhs)
		{ return (lhs.getPtr() - rhs.getPtr()); }

		template< typename Iter1, typename Iter2 >
		bool operator==(const vectorIterator<Iter1> &lhs, const vectorIterator<Iter2> &rhs)
		{ return (lhs.getPtr() == rhs.getPtr()); }

		template< typename Iter1, typename Iter2 >
		bool operator!=(const vectorIterator<Iter1> &lhs, const vectorIterator<Iter2> &rhs)
		{ return (lhs.getPtr() != rhs.getPtr()); }

		template< typename Iter1, typename Iter2 >
		bool operator<(const vectorIterator<Iter1> &lhs, const vectorIterator<Iter2> &rhs)
		{ return (lhs.getPtr() < rhs.getPtr()); }

		template< typename Iter1, typename Iter2 >
		bool operator>(const vectorIterator<Iter1> &lhs, const vectorIterator<Iter2> &rhs)
		{ return (lhs.getPtr() > rhs.getPtr()); }

		template< typename Iter1, typename Iter2 >
		bool operator>=(const vectorIterator<Iter1> &lhs, const vectorIterator<Iter2> &rhs)
		{ return (lhs.getPtr() >= rhs.getPtr()); }

		template< typename Iter1, typename Iter2 >
		bool operator<=(const vectorIterator<Iter1> &lhs, const vectorIterator<Iter2> &rhs)
		{ return (lhs.getPtr() <= rhs.getPtr()); }

}
