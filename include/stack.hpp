#pragma once

#include "vector.hpp"

namespace ft
{
	template< class T, typename type = vector<T> >
	class stack
	{
		public:
			typedef typename type::value_type			value_type;
			typedef typename type::reference			reference;
			typedef typename type::const_reference	const_reference;
			typedef typename type::size_type			size_type;
			typedef type								container_type;

		public :
		//	explicit	stack() : c() { }
			//explicit stack( const vector& cont) : c(cont) {}
			explicit stack( const container_type& cont  = container_type()) : c(cont) {}
			//explicit	stack(const std::deque<T> )

			stack& operator=( const stack& other ) {c = other.c; return (*this);}

			bool				empty() const	{ return c.empty(); }
			size_type			size() const	{ return c.size(); }
			reference			top()			{ return c.back(); }
			const_reference		top() const		{ return c.back(); }
			void				push(const value_type& __x)	{ c.push_back(__x); }
			void				pop()			{c.pop_back();}

		public:
			friend bool				operator==(const stack<T, type>& x, const stack<T, type>& y)	{ return x.c == y.c; }
			friend bool				operator!=(const stack<T, type>& x, const stack<T, type>& y)	{ return x.c != y.c; }
			friend bool				operator<(const stack<T, type>& x, const stack<T, type>& y)	{ return x.c < y.c; }
			friend bool				operator<=(const stack<T, type>& x, const stack<T, type>& y)	{ return x.c <= y.c; }
			friend bool				operator>(const stack<T, type>& x, const stack<T, type>& y)	{ return x.c > y.c; }
			friend bool				operator>=(const stack<T, type>& x, const stack<T, type>& y)	{ return x.c >= y.c; }

		//  See queue::c for notes on this name <-- COM du code source
		protected:
			container_type	c;
	};

	// template< class T, typename deque = std::deque<T> >
	// class stack
	// {
	// 	public:
	// 		typedef typename std::deque			value_type;
	// 		typedef typename std::deque			reference;
	// 		typedef typename std::deque	const_reference;
	// 		typedef typename std::deque			size_type;
	// 		typedef std::deque								container_type;

	// 	public :
	// 	//	explicit	stack() : c() { }
	// 		explicit stack( const deque& cont) : c(cont) {}
	// 		stack( const container_type& other  = container_type()) : c(other) {}

	// 		stack& operator=( const stack& other ) {c = other.c; return (*this)};

	// 		bool				empty() const	{ return c.empty(); }
	// 		size_type			size() const	{ return c.size(); }
	// 		reference			top()			{ return c.back(); }
	// 		const_reference		top() const		{ return c.back(); }
	// 		void				push(const value_type& __x)	{ c.push_back(__x); }
	// 		void				pop()			{c.pop_back();}

	// 	public:
	// 		friend bool				operator==(const stack<T, vector>& x, const stack<T, vector>& y)	{ return x.c == y.c; }
	// 		friend bool				operator!=(const stack<T, vector>& x, const stack<T, vector>& y)	{ return x.c != y.c; }
	// 		friend bool				operator<(const stack<T, vector>& x, const stack<T, vector>& y)	{ return x.c < y.c; }
	// 		friend bool				operator<=(const stack<T, vector>& x, const stack<T, vector>& y)	{ return x.c <= y.c; }
	// 		friend bool				operator>(const stack<T, vector>& x, const stack<T, vector>& y)	{ return x.c > y.c; }
	// 		friend bool				operator>=(const stack<T, vector>& x, const stack<T, vector>& y)	{ return x.c >= y.c; }

	// 	//  See queue::c for notes on this name <-- COM du code source
	// 	protected:
	// 		deque	c;
	// };

}
