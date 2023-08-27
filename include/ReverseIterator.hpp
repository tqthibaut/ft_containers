//#include "Vector.hpp"

#pragma once

#include "iterator_traits.hpp"

namespace	ft
{
	//reverse iterator prend un itérateur en "arg" de template!
	// Il se construit donc juste sur l'iterateur == surcouche d'iterateur
	template <class Iterator>
	class reverse_iterator 
	{
		protected:
			typedef iterator_traits<Iterator>			traits_type;
			
		public:
			typedef Iterator							iterator_type;
			typedef ft::iterator_traits<Iterator>		traits;
			typedef typename traits::iterator_category	iterator_category;
			typedef typename traits::value_type			value_type;
			typedef typename traits::difference_type	difference_type;
			typedef typename traits::pointer			pointer;
			typedef typename traits::reference			reference;

		reverse_iterator () : _base() {};
		explicit reverse_iterator (iterator_type it) : _base(it) {};
	template <class Iter>
		reverse_iterator (reverse_iterator<Iter> const & rev_it) : _base(rev_it.base()) {};

		~reverse_iterator () {};

		template<class Iter>
		reverse_iterator & operator=(const reverse_iterator<Iter> & rhs)
		{
			this->_base = rhs.base();
			return *this;
		}

		iterator_type base () const {return _base;};

		/********* Operator Overloads ***********/
		reference			operator*	() const					{
			iterator_type tmp(_base);
			tmp--;
			return *tmp;
		}
		reverse_iterator	operator+	(difference_type n) const	{return reverse_iterator(_base - n);};
		reverse_iterator &	operator++	()							{_base--; return *this;};
		reverse_iterator	operator++	(int)						{reverse_iterator temp = *this; ++(*this); return temp;};
		reverse_iterator &	operator+=	(difference_type n)			{_base -= n; return *this;};
		reverse_iterator	operator-	(difference_type n) const	{return reverse_iterator(_base + n);};
		reverse_iterator &	operator--	()							{_base++; return *this;};
		reverse_iterator	operator--	(int)						{reverse_iterator temp = *this; --(*this); return temp;};
		reverse_iterator &	operator-=	(difference_type n)			{_base += n; return *this;};
		pointer				operator->	() const					{return &(operator*());};
		reference			operator[]	(difference_type n)			{return base()[-n -1];};

	private:
		iterator_type	_base;
};


template <class Iterator, class Iterator2>
bool	operator== (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator2> const & rhs) {
	return lhs.base() == rhs.base();
}

template <class Iterator, class Iterator2>
bool	operator!= (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator2> const & rhs) {
	return lhs.base() != rhs.base();
}

template <class Iterator, class Iterator2>
bool	operator< (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator2> const & rhs) {
	return lhs.base() > rhs.base();
}

template <class Iterator, class Iterator2>
bool	operator<= (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator2> const & rhs) {
	return lhs.base() >= rhs.base();
}

template <class Iterator, class Iterator2>
bool	operator> (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator2> const & rhs) {
	return lhs.base() < rhs.base();
}

template <class Iterator, class Iterator2>
bool	operator>= (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator2> const & rhs) {
	return lhs.base() <= rhs.base();
}

template <class Iterator>
reverse_iterator<Iterator>	operator+ (typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> const & rev_it) {
	return rev_it + n;
}

template <class Iterator, class Iterator2>
typename reverse_iterator<Iterator>::difference_type operator- (reverse_iterator<Iterator> const & lhs, reverse_iterator<Iterator2> const & rhs) {
	return rhs.base() - lhs.base();
}



// template< typename T, class Alloc>
// class	vector;

// // reverse iterator prend un 
// template <typename vector>
// class	vectorReverseIterator
// {
// 	public:
// 	typedef		ft::vectorReverseIterator< vector >					reverse_iterator;
// 	typedef	typename vector::value_type		value_type;
// 	typedef typename vector::pointer		pointer;
// 	typedef	typename vector::reference		reference;
// 	typedef	typename vector::difference_type	difference_type;
// 	// typedef	typename vector::iterator<vector<value_type>	iterator;

// 	public:
// 		vectorReverseIterator(pointer	ptr) : _ptr(ptr) {}

// 	private:
// 		pointer	_ptr;

// 	public:
// 		//prefixe operator
// 		vectorReverseIterator&	operator++()
// 		{
// 			_ptr--;
// 			return *this;
// 		}
// 		//post-fix operator
// 		vectorReverseIterator&	operator++(int)
// 		{
// 			vectorReverseIterator iteratorcpy = *this;
// 			--(*this);
// 			return iteratorcpy;
// 		}

// 		//prefixe operator
// 		vectorReverseIterator&	operator--()
// 		{
// 			_ptr++;
// 			return *this;
// 		}
// 		//post-fix operator
// 		vectorReverseIterator&	operator--(int)
// 		{
// 			vectorReverseIterator iteratorcpy = *this;
// 			++(*this);
// 			return iteratorcpy;
// 		}

// 		reference	operator[](int	index)
// 		{
// 			return *(_ptr + index);
// 		}

// 		pointer	operator->()
// 		{
// 			return _ptr;
// 		}

// 		reference	operator*()
// 		{
// 			return *_ptr;
// 		}

// 		reference	operator*(int)
// 		{
// 			return *_ptr;
// 		}

// 		bool	operator==(const vectorReverseIterator& other) const
// 		{
// 			return (this->_ptr == other._ptr);
// 		}

// 		bool	operator!=(const vectorReverseIterator& other) const
// 		{
// 			return (this->_ptr != other._ptr);
// 		}

// 		reference	operator+=(difference_type n)
// 		{
// 			_ptr -= n;
// 			return (*this);
// 		}

// 		reverse_iterator	operator+(difference_type n)
// 		{
// 			return iterator(_ptr + n);
// 		}

// 		reference	operator-=(difference_type n)
// 		{
// 			_ptr += n;
// 			return (*this);
// 		}

// 		reverse_iterator		operator-(difference_type n)
// 		{
// 			return iterator(_ptr + n);
// 		}

// 		bool	operator<(const reverse_iterator& rhs)
// 		{
// 			return (this->_ptr < rhs._ptr);
// 		}

// 		bool	operator>(const reverse_iterator& rhs)
// 		{
// 			return (this->_ptr > rhs._ptr);
// 		}

// };

}

