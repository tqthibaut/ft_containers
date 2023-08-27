/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthibaut <tthibaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:56:19 by tthibaut          #+#    #+#             */
/*   Updated: 2023/03/31 16:44:28 by tthibaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <exception>
#include <stdexcept>
#include "vector_iterator.hpp"
#include "ReverseIterator.hpp"
#include "enable_if.hpp"
#include "utils.hpp"
//#include "random_access_iterator.hpp"

namespace ft
{

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		/*							***	TYPEDEF AND STUFF ***							*/
		public :
			typedef				T									value_type;
			typedef				Alloc								allocator_type;
			typedef	typename	allocator_type::reference			reference;
			typedef	typename	allocator_type::const_reference		const_reference;
			typedef	typename	allocator_type::pointer				pointer;
			typedef	typename	allocator_type::const_pointer		const_pointer;
			typedef		ft::vectorIterator<value_type>					iterator;
			typedef		ft::vectorIterator< const value_type >			const_iterator;
			typedef		ft::reverse_iterator<iterator>				reverse_iterator;
			typedef		ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef	typename	ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef		size_t							size_type;

		private:
			allocator_type	_alloc;
			pointer			_begin;
			pointer			_end;
			size_type		_size;
			size_type		_capacity;


		/*							*** CONSTRUCTORS AND DESTRUCTOR***									*/
		public:
			// Default constructor
			explicit vector (const allocator_type & alloc = allocator_type())
				: _alloc(alloc), _begin(NULL), _end(NULL), _size(0), _capacity(0) { };
			// Fill constructor
			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _begin(NULL), _end(NULL), _size(n), _capacity(n)
			{
				//std::cout << "size_t constructor called\n";
				if (n > max_size())
					throw std::length_error("vector::not enough capacity");
				if (n > 0)
				{
					_begin = _alloc.allocate(_size);
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_begin + i, val);
					_end = _begin + _size;
				}
				return;
			}
			// Copy constructor
			vector(const vector& x) : _begin(NULL), _end(NULL), _size(0), _capacity(0)
			{
				this->_alloc = x.get_allocator();
				this->_size = x.size();
				this->_capacity = x.size();
				if (x.size() > 0)
				{
					this->_begin = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < x.size(); i++)
						_alloc.construct(_begin + i, x.at(i));
					_end = _begin + x.size();
				}
				return;
			}

			template< class InputIterator >
			vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::_value, void **>::type = 0 ) :
				_alloc(alloc), _begin(NULL), _end(NULL), _size(0), _capacity(0)
			{
				if (first != last)
					this->reserve(1);
				size_type i = 0;
				for (; first != last; first++)
				{
					if (i == this->_capacity)
						this->reserve(this->_capacity * 2);
					this->_alloc.construct(this->_begin + i++, *first);
					this->_size++;
				}
				this->_end = _begin + _size;
				this->shrink_to_fit();
			}

			// void	getNothing(){return;}

			virtual ~vector()
			{
				// this->clear();
				// std::cout << "Destroy from vector destructor called\n";
				for (size_t i = 0;  i < _size; i++)
					this->_alloc.destroy(this->_begin + i);
		// std::cout << "Dealloc vector destructor\n";
				if (_capacity > 0)
					_alloc.deallocate(_begin, _capacity);
			}

			vector& operator= (const vector& x)
			{
				if (this != &x)
					assign(x.begin(), x.end());
				return (*this);

				// if (this == &x)
				// 	return (*this);
				// for (size_type i = 0; i < _size; i++)
				// 	_alloc.destroy(_begin + i);

				// if (x.size() > _capacity)
				// {
				// 	_alloc.deallocate(_begin, _capacity);
				// 	_capacity = x.size();
				// 	_begin = _alloc.allocate(_capacity);
				// }

				// _size = x.size();
				// for (size_type i = 0; i < _size; i++)
				// 	_alloc.construct(_begin + i, x[i]);

				// return (*this);

				// if (this == &x)
				// 	return (*this);

				// if (_size)
				// {
				// 	for (size_type i = 0 ; i < _size ; i++)
				// 		_alloc.destroy(_begin + i);
				// 	// std::cout << "DEstroy operator = called";
				// }

				// if (x._size > _capacity)
				// {
				// 	_alloc.deallocate(_begin, _capacity);
				// 	_capacity = x._size;
				// 	_begin = _alloc.allocate(_capacity);
				// }

				// _size = x._size;
				// for (size_type i = 0 ; i < _size ; i++)
				// 	_alloc.construct(_begin + i, x[i]);
				// _end = _begin + _size;
				// return (*this);
			};

		/*							*** MEMBER FUNCTIONS						*/
			// pointer	get_begin(void) {return (this->_begin);}

			//void assign( size_type count, const T& value );
			// template< class InputIt >
			// void assign( InputIt first, InputIt last );
			allocator_type get_allocator() const { return(_alloc); }
			template <class inputIt>
			void	assign (inputIt first, inputIt last, typename ft::enable_if<!ft::is_integral<inputIt>::_value, void **>::type = 0)
			{
				this->clear();
				insert(this->begin(), first, last);

				// size_type	n = 0;
				// //std::distance du pauvre
				// for (inputIt cpy = first; cpy != last && n < this->max_size(); cpy++)
				// 	n++;

				// if (n > _capacity)
				// 	this->reserve(n);
				// for (size_type i = 0; i < _size; i++)
				// 	_alloc.destroy(_begin + i);
				// for (size_type i = 0; i < n; i++)
				// 	_alloc.construct(_begin + i, *first++);
				// _size = n;
				// _end = _begin + _size;

			}

		/*							*** ELEMENT ACCESS ***									*/

			reference	at( size_type pos ) {
				if (pos >= _size)
					throw std::out_of_range("vector::at -> index out of range !");
				return (*(this->_begin + pos));
			}
			const_reference	at( size_type pos ) const {
				if (pos >= _size)
					throw std::out_of_range("vector::at -> index out of range !");
				return (*(this->_begin + pos));
			}
			reference		operator[](size_type i) { return (*(this->_begin + i));}
			const_reference operator[]( size_type i ) const { return (*(this->_begin + i));}
			reference			front() {return (*begin());}
			const_reference		front() const {return(*begin());}
			reference			back()			{return (*(end() - 1));}
			const_reference		back() const	{return (*(end() - 1));}
			value_type*			data() {return (_begin);}
			const value_type*	data() const {return (_begin);}

			/*						*** ITERATORS ***											 */
			iterator		begin()				{return (iterator(this->_begin));}
			const_iterator	begin() const		{return const_iterator(this->_begin);}
			iterator		end()				{return(iterator(this->_begin + _size));}
			const_iterator	end() const			{return(const_iterator(this->_begin + _size));}
			reverse_iterator		rbegin() 	{return (reverse_iterator(this->end())); }
			const_reverse_iterator	rbegin() const 	{return (const_reverse_iterator(this->end())); }
			reverse_iterator	rend() 			{	return(reverse_iterator(this->begin()));}
			const_reverse_iterator	rend() const 			{	return(const_reverse_iterator(this->begin()));}


			/*						*** CAPACITY ***											*/
			bool		empty() const	{ return((this->_size == 0) ? 1 : 0);}
			size_type	size() const			{return (this->_size);}
			size_type	max_size() const	{return (this->_alloc.max_size());}
			void		reserve(size_type n)
			{
				if (n > _alloc.max_size())
					throw std::length_error("vector::reserve");
				if (n <= _capacity)
					return;
				if (n > _capacity)
				{
					// size_t	len = _check_size(n);
					pointer	new_start = _alloc.allocate(n);
					// pointer new_finish = new_start;

				for (size_type i = 0; i < n; i++)
				{
					if (i < _size)
					{
						_alloc.construct(new_start + i, *(_begin + i));
						_alloc.destroy(_begin + i);
						// std::cout << "DEstroy reserve called\n";
					}
				}

					if (_capacity != 0)
						_alloc.deallocate(_begin, capacity());
					_capacity = n;
					_begin = new_start;
					_end = _begin + _size;
				}
			}
			size_type	capacity() const	{return (this->_capacity);}


			/*						*** MODIFIERS ***											*/
			void	clear()
			{
				if (this->_size)
				{
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_begin + i);
					// std::cout << "destroy clear called \n";
					_size = 0;
					_end = _begin;
				}
			}

			iterator insert( iterator pos, const T& value )
			{
				difference_type decalage = pos - begin();
				if (_capacity < _size + 1)
					reserve(reserve_calc (_size + 1));
				iterator current_it = end();
				pos = begin() + decalage;
				if (_size && pos != current_it)
				{
					_alloc.construct(_begin + _size, *(--current_it));
					for (; current_it != pos; current_it--)
						*current_it = *(current_it - 1);
					_alloc.destroy(_begin + (pos - begin()));
				}
				_alloc.construct(_begin + (pos - begin()), value);
				_size++;
				_end = _begin + _size;
				return(begin() + decalage);
			}

			// Inserts count copies of the value before pos
			void insert( iterator pos, size_type count, const T& value )
			{
				difference_type	decalage = pos - begin();
				if (count == 0)
					return;
				if (_capacity < _size + count)
					reserve(reserve_calc(_size + count));
				iterator	current_it = end() + (count - 1);
				pos = begin() + decalage;
				// copy (construct) content from the new end to the old end
				while (current_it >= end() && current_it >= pos + count)
				{
					_alloc.construct(_begin + (current_it - begin()), *(current_it - count));
					current_it--;
				}
				// assign the previously constructed values to their new
				// position + n
				while (current_it >= pos + count)
				{
					*current_it = *(current_it - count);
					current_it--;
				}
				// destroys the old values and constructs the inserted values
				while(current_it >= pos)
				{
					if (current_it < end())
					{
						_alloc.destroy(_begin + (current_it - begin()));
						// std::cout << "Destroy insert range called\n";
					}
					_alloc.construct(_begin + (current_it - begin()), value);
					current_it--;
				}
				_size += count;
				return;
			}
//				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = true)
			template <class InputIterator>
			void	insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::_value, void **>::type = 0)
			{
				if (last == first)
					return;
				size_type n = 0;

				vector<T, Alloc> v_tmp(first, last);
				n = v_tmp.size();
				// std::cout << "n de insert it, it == " << n << "\n";
				if (n == 0)
					return;

				difference_type pos = position - begin();
				if (_capacity < _size + n)
					reserve(reserve_calc(_size + n));
				position = begin() + pos;
				iterator ite_cur = this->end() + (n - 1);
				while (ite_cur >= this->end() && ite_cur >= position + n)
				{
					_alloc.construct(_begin + (ite_cur - begin()), *(ite_cur - n));
					ite_cur--;
				}
				while (ite_cur >= position + n)
				{
					*ite_cur = *(ite_cur - n);
					ite_cur--;
				}
				iterator new_last = v_tmp.end();

				while (ite_cur >= position)
				{
					if (ite_cur < end())
					{
						_alloc.destroy(_begin + (ite_cur - begin()));
						// std::cout << "destroy insert triple iterator\n";
					}
					new_last--;
					_alloc.construct(_begin + (ite_cur - begin()), *new_last);
					ite_cur--;
				}
				_size += n;
				_end = _begin + _size;
				return;
			}

			void pop_back() {_alloc.destroy(_begin + _size - 1); _size--;}
			void 		resize (size_type n, value_type val = value_type());
			void	assign( size_t count, const value_type& value )
			{
				clear();
				if (count == 0)
					return;
				if (count > capacity())
				{
					if (_capacity)
						_alloc.deallocate(_begin, _capacity);
					_capacity = count;
					_begin = _alloc.allocate(_capacity);
					// reserve(reserve_calc(count));
				}
				for (std::size_t n = 0; n < count; n++)
				{
					_alloc.construct(_begin + n, value);
				}
				_size = count;
				_end = _begin + count;
				return;
			}

		private :

			void	_erase_at_end(pointer _pos)
			{
				//std::cout << "_erase_at_end called with int" << *_pos << std::endl;
				_destroy(_pos, _end);
				this->_end = _pos;
			}

			void	_destroy(pointer first, pointer last)
			{
				for (;first != last; first++)
				{
					_alloc.destroy(first);
					std::cout << "_destroy called\n";
				}
			}

			size_type	reserve_calc(size_type n)
			{
				size_type	s = _size *2;
				if (n <= s)
				{
					if (s <= _alloc.max_size())
						return (s);
					return (_alloc.max_size());
				}
				return (n);
		// Trop lent :0
				// if (n <= _size * 2)
				// {
				// 	if (_size * 2 <= _alloc.max_size())
				// 		return (_size * 2);
				// 	else
				// 		return (_alloc.max_size());
				// }
				// 	return(n);
			}


		protected :
			void	_range_check(size_type n) {if (n >= this->size()) throw std::out_of_range("Out of range");}
			void	_vector_fill(iterator end, size_type diff_size, value_type val);
			void	_vector_fill(iterator first, iterator last);
			void	_vector_fill(const_iterator first, const_iterator last);
			void	_vector_fill_at_end(iterator first, iterator last);

			// size_type	reserve_calc(size_type n);

		public :

			iterator	erase( iterator pos )
			{
				// LOL la std elle segfault si on erase un truc vide
				// if (this->empty())
				// 	return (pos);
				for (size_type i = pos - begin(); i < _size - 1; i++)
				{
					// *(_begin + i) = *(_begin + i + 1);
					_begin[i] = _begin[i + 1];
				}
				_size--;
				_alloc.destroy(_begin + _size);
				// std::cout << "destroy erase single \n";
				this->_end = _begin + _size;
				return(pos);
			}

			// Removes the elements in the range [first, last).
			iterator erase (iterator first, iterator last)
			{
				// Par contre la ya un check, cest nimporte quoi
				if (this->empty() || last <= first)
					return (first);

				iterator	current_it = first;
				difference_type	diff_it = last - first;
				iterator	end_it = this->end();
				// std::cout << "diff it == " << diff_it << "\n";
				// std::cout << "size == " << size() << "\n";
				// std::cout << "ITE_END - 1 == " << *(end_it -1) << "\n";



				for (; (current_it + 1) != end_it - diff_it + 1; current_it++)
				{
					// std::cout << "CURRENT IT * == " << *current_it << "\n";
					*current_it = *(current_it + diff_it);
				}
				for (difference_type i = 0; i != diff_it; i++)
				{

					// std::cout << "TO DESTROY NUMBER == " << _size - 1 + i << "\n";
					_alloc.destroy(_begin + _size - 1 - i);
					// std::cout << "erase range iterator called \n";
				}

				_size -= diff_it;
				this->_end = _begin + _size;
				return (first);
			}


			void push_back (const value_type& val)
			{
				if (this->_capacity == 0)
				{
					this->reserve(1);
				}

				else if (_capacity <= _size)
					this->reserve(_capacity ? _capacity * 2 : 1);
				_alloc.construct(_begin + _size, val);
				_end++;
				_size++;
			}

			void swap( vector& other )
			{
				size_type tmp_size = other._size;
				size_type tmp_capacity = other._capacity;
				pointer tmp_begin = other._begin;

				other._size = this->_size;
				other._capacity = this->_capacity;
				other._begin = this->_begin;

				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
				this->_begin = tmp_begin;
			}

		private:
			size_t	_check_size(size_type n)
			{
				if (n > max_size() - size())
				{
					// std::cout << "Check size\n";
					throw (std::length_error("Too big\n"));
				}
				size_t len = size() + std::max(size(), n);
				return ((len < size()) || (len > max_size()) ? max_size() : len);
			}

			size_t	_check_init_size(size_type n)
			{
				if (n > max_size())
				{
					// std::cout << "Check init size\n";

					throw (std::length_error("cannot create std::vector larger than max_size()"));
				}
				return (n);
			}

			void shrink_to_fit( void )
			{
				if (_capacity != _size)
				{
					pointer tmp = _alloc.allocate(_size);
					iterator it = begin();
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(tmp + i, *it);
						it++;
					}
					size_type size = _size;
					clear();
					_alloc.deallocate(_begin, _capacity);
					_begin = tmp;
					_size = size;
					_end = _begin + _size;
					_capacity = size;
				}
			}
	};


/*																						*/
/*									END OF CLASS DECLARATION							*/
/*																						*/

	template < class T, class Alloc >
	inline void	vector<T, Alloc>::resize(size_type n, value_type val)
	{
		if (n > _alloc.max_size())
			throw std::length_error("vector::resize");
		if (n == _size)
			return;
		if (n < _size)
		{
			for (size_type i = n; i < _size; i++)
				_alloc.destroy(_begin + i);
		}

		else if (n > _size)
		{
			if (n > _capacity)
				reserve(reserve_calc(n));
			//std::cout << "SIZE BEFORE RESERVE == " << this->_size << std::endl;
			for (size_type i = _size; i < n; i++)
				_alloc.construct(_begin + i, val);
			//std::cout << "SIZE AFTER RESERVE == " << this->_size << std::endl;
		}
			_size = n;
			_end = _begin + n;
	}

	template <class T, class Alloc >
	inline void	vector<T, Alloc>::_vector_fill(iterator end, size_type diff_size, value_type val)
	{
		if (diff_size <= 0)
			return;
		for (size_type i = 0; i < diff_size; i++)
			_alloc.construct(&(*(end + i)), val);
		return;
	}

	template <class T, class Alloc >
	inline void	vector<T, Alloc>::_vector_fill(iterator first, iterator last)
	{
		int	i = 0;
		for (;first != last; first++, i++)
			_alloc.construct(first._ptr, *last);
		//_end++;
	}

	template <class T, class Alloc >
	inline void	vector<T, Alloc>::_vector_fill(const_iterator first, const_iterator last)
	{
		int	i = 0;
		for (;first != last; first++, i++)
			_alloc.construct(&(*first), *last);
		//_end++;
	}

	template <class T, class Alloc >
	inline void	vector<T, Alloc>::_vector_fill_at_end(iterator first, iterator last)
	{
		for (iterator it = this->end();first != last;first++, it++, _end++)
			_alloc.construct(&(*it), *first);
		//_end++;
	}

	template <class T, class Alloc>
  	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (size_t i = 0; i < lhs.size(); i++)
			{
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}
		return false;
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return !(lhs == rhs); }

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (rhs < lhs); }

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return !(lhs > rhs); }

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return !(lhs < rhs); }

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{ x.swap(y); }

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2) || (first2 == last2))
				return false;
			first1++;
			first2++;
		}
		return (first2 == last2);
	}
}

#endif
