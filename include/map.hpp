/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthibaut <tthibaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:27:44 by tthibaut          #+#    #+#             */
/*   Updated: 2023/03/31 14:57:28 by tthibaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <functional>
#include "rb_tree.hpp"
#include "map_iterator.hpp"
#include "utils.hpp"
#include "pair.hpp"
#include "enable_if.hpp"
#include "ReverseIterator.hpp"


namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair< const Key, T > > >
	class map
	{

		public :
			typedef			Key						key_type;
			typedef			T						mapped_type;
			typedef			ft::pair<const key_type, mapped_type>	value_type;
			typedef			Compare					key_compare;
			typedef			Alloc				allocator_type;
			typedef	typename	Alloc::reference			reference;
			typedef	typename	Alloc::const_reference			const_reference;
			typedef	typename	Alloc::pointer	pointer;
			typedef	typename	Alloc::const_pointer	const_pointer;
			//typedef typename 	Alloc::difference_type			difference_type;
			// cest probablement une meilleur pratique de définir la size avec l'allocateur
			//typedef typename	Alloc::size_type				size_type;

			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {};
				public:
					// These member types are obtained via publicly inheriting
					// std::binary_function<value_type, value_type, bool>.
					// on a donc comp qui se crée en utilisant std::less
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					value_compare () : comp() {};
					bool operator() (value_type const & x, value_type const & y) const {
						return comp(x.first, y.first);}
			};

			//typedef			std::pair<const Key, T>	value_type;
			typedef			std::size_t				size_type;
			typedef	typename		std::ptrdiff_t			difference_type;
			typedef			ft::RBT_Node< value_type >			Node;
			typedef rb_tree<value_type, value_compare, Alloc>									tree_type;
			typedef typename rb_tree<value_type, value_compare, Alloc>::iterator				iterator;
			typedef typename rb_tree<value_type, value_compare, Alloc>::const_iterator			const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;



		protected :
			rb_tree<value_type, value_compare, Alloc>		_rbtree;
			allocator_type									_alloc;
			key_compare										_comp;
			value_compare									_value_comp;


	/*							***	MEMBER FUNCTIONS ***							*/

		public:
			//map()
			explicit map( const key_compare& comp = key_compare(), allocator_type const &  alloc = allocator_type() )
				: _rbtree(), _alloc(alloc), _comp(comp) {};

			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc())
				: _rbtree(), _alloc(alloc), _comp(comp)
			{
				insert(first, last);
			};
			map( const map& other ) : _rbtree(other._rbtree), _alloc(other._alloc), _comp(other._comp)
			{
				// initLeaf()
			};
			~map() {};

			map& operator=( const map& other ) {this->_rbtree = other._rbtree; return *this;}
			allocator_type get_allocator() const { return this->_alloc;}

				//Element Access
			mapped_type& at( const Key& key ) {
				iterator	tmp = find(key);
				if (tmp == this->end())
					throw (std::out_of_range("map::at = out of range"));
				return (tmp->second);
			};

			const mapped_type& at( const Key& key ) const {
				const_iterator tmp = find(key);
				if (tmp == this->end())
					throw std::out_of_range("map::at = out of range !");
				return (tmp->second);
			}

			mapped_type & operator[]( const Key& key ) { return(insert(ft::make_pair(key, mapped_type())).first->second);}


				// Iterators
			iterator begin() { return iterator(_rbtree.minimum(_rbtree._root), _rbtree._root); }
			const_iterator begin() const { return (const_iterator(_rbtree.minimum(_rbtree._root), _rbtree._root)) ;}
			iterator end() {return _rbtree.end();}
			const_iterator end() const {return _rbtree.end();}
			reverse_iterator rbegin() {return reverse_iterator(_rbtree.end());}
			const_reverse_iterator rbegin() const {return const_reverse_iterator(_rbtree.end());}
			reverse_iterator rend() {return reverse_iterator(_rbtree.begin());}
			const_reverse_iterator rend() const {return const_reverse_iterator(_rbtree.begin());}

				// Capacity
			bool empty() const {return (!size());}
			size_type size() const {return (_rbtree.size());};
			size_type max_size() const {std::allocator<Node> tmp; return tmp.max_size();}
			// size_type max_size() const { return this->_rbtree._node_alloc.max_size();}
			// size_type max_size() const { return this->_alloc.max_size();}

				// Modifiers
			void clear() { _rbtree.clear();}

			ft::pair<iterator, bool> insert( const value_type& value )
			{
				iterator	it = find(value.first);
				if (it != end())
					return ft::make_pair(it, false);
				return ft::make_pair(iterator(_rbtree.insertNode(value), _rbtree.root()), true);
			}

			iterator insert( iterator pos, const value_type& value )
			{
				(void)pos;
				iterator	it = find(value.first);
				if (it != end())
					return it;
				return iterator(_rbtree.insertNode(value), _rbtree.root());
			}

			template< class InputIt >
			void insert( InputIt first, InputIt last)
			{
				for (; first != last; first++)
					this->insert(*(first));
			}


			void erase( iterator pos ) { _rbtree.deleteNode(pos.getNode());}
			void erase( iterator first, iterator last )
			{
				if (first == this->begin() && last == this->end())
					this->clear();
				else
				{
					while (first != last)
						this->erase(first++);
				}
			}
			size_type erase( const Key& key )
			{
				iterator it = find(key);
				if (it == end())
					return 0;
				else
					_rbtree.deleteNode(it.getNode());
					//_rbtree.deleteNode(it._current);
				return 1;
			}

			void swap( map& other )
			{
				Node *	root_tmp = _rbtree.root();
				Node *	leaf_tmp = _rbtree.leaf();
				size_type	size_temp = _rbtree.size();

				_rbtree._root = other._rbtree.root();
				_rbtree._leaf = other._rbtree.leaf();
				_rbtree._size = other._rbtree.size();

				other._rbtree._root = root_tmp;
				other._rbtree._leaf = leaf_tmp;
				other._rbtree._size = size_temp;
			}

				// Lookup
			size_type count( const Key& key ) const { return (find(key) != end()); }
			iterator find( const Key& key )
			{
				Node *	node = _rbtree.root();
				if (node == _rbtree.leaf())
					return iterator(node, _rbtree.root());
				while (node->data.first != key && node != _rbtree.leaf())
				{
					if (_comp(node->data.first, key))
						node = node->right;
					else
						node = node->left;
				}
				if (node == _rbtree.leaf())
					return end();
				else
					return iterator(node, _rbtree.root());
			}

			const_iterator find( const Key& key ) const
			{
				Node *	node = _rbtree.root();
				if (node == _rbtree.leaf())
					return const_iterator(node, _rbtree.root());
				while (node->data.first != key && node != _rbtree.leaf())
				{
					if (_comp(node->data.first, key))
						node = node->right;
					else
						node = node->left;
				}
				if (node == _rbtree.leaf())
					return end();
				else
					return const_iterator(node, _rbtree.root());
			}

			ft::pair<iterator,iterator> equal_range( const Key& key ) {
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}
			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}
			iterator lower_bound( const Key& key )
			{
				for (iterator it = this->begin(); it != this->end(); it++)
					if (!_comp((*it).first, key))
						return (it);
				return (this->end());
			}
			const_iterator lower_bound( const Key& key ) const
			{
				for (const_iterator it = this->begin(); it != this->end(); it++)
					if (!_comp((*it).first, key))
						return (it);
				return (this->end());
			}
			iterator upper_bound( const Key& key )
			{
				for (iterator it = this->begin(); it != this->end(); it++)
					if (_comp(key, (*it).first))
						return (it);
				return (this->end());
			}
			const_iterator upper_bound( const Key& key ) const
			{
				for (const_iterator it = this->begin(); it != this->end(); it++)
					if (_comp(key, (*it).first))
						return (it);
				return (this->end());
			}

				//Observers
			key_compare key_comp() const {return this->_comp;}
			value_compare value_comp() const { return this->_value_comp;}




	};
			//Non-member Functions
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		typename ft::map<Key, T, Compare, Alloc>::const_iterator itr = rhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator itl = lhs.begin();
		while (itr != rhs.end())
		{
			if (!(*itr == *itl))
				return false;
			itr++;
			itl++;
		}
		return true;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs )
	{ return !(lhs == rhs) ;}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs )
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs )
	{ return !(rhs < lhs); }

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs )
	{ return rhs < lhs; }

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs )
	{ return !(lhs < rhs); }

	template< class Key, class T, class Compare, class Alloc >
	void swap(ft::map<Key, T, Compare, Alloc> &x, ft::map<Key, T, Compare, Alloc> &y)
	{ return x.swap(y); }
}


	/*
		Pseudo-code du pdf sur les algorithmes, retranscris en C++. J'ai pas BAC+7 en maths j'allais pas reinventer
		ca depuis 0, je laisse ca a des gens avec un cerveau bien moins lisse que le mien.
	*/

	// template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T>> >
	// iterator find( const Key& key )
	// {
	// 	map<Key, T>::iterator x = this->begin();
	// 	while(*x != key && *x != NULL)
	// 	{
	// 		if (key < *x)
	// 			x = x.left;
	// 		else
	// 			x = x.right;
	// 	}
	// 	return (x);
	// }


	// template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T>> >
	// std::pair<iterator, bool> insert( const value_type& value )
	// {
	// 	map<Key, T>::iterator	x = tree.root;
	// 	map<Key, T>::iterator	y = NULL;
	// 	Node					to_insert(value);
	// 	while (x != NULL)
	// 	{
	// 		y = x;
	// 		if (to_insert.value < x.key)
	// 			x = x.left;
	// 		else
	// 			x = x.right
	// 	}
	// 	to_insert.p = y;
	// 	if (y == NULL)
	// 		tree.root = to_insert;
	// 	else if (to_insert < y.key)
	// 		y.left = to_insert;
	// 	else
	// 		y.right = to_insert;
	// }

// 	iterator erase( iterator pos )
// 	{
// 		transplant(iterator receiver, iterator implant);

// 	}

// 	/*
// 		TRANSPLANT put a subtree (implantee) next to the receiver
// 		and change its parent accordingly (either left or right child)
// 	*/
// 	void	transplant(iterator receiver, iterator implantee)
// 	{
// 		if (receiver.p == NULL)
// 			this->begin() = implantee;
// 		else if (receiver == receiver.p.left)
// 			receiver.p.left = implantee;
// 		else
// 			receiver.p.right = implantee;

// 		if (implantee != NULL)
// 			implantee.p = receiver.p;
// 	}
// }

/*
INTRO

A red-black tree is a binary search tree with one extra bit of storage per node: its
color, which can be either RED or BLACK . By constraining the node colors on any
simple path from the root to a leaf, red-black trees ensure that no such path is more
than twice as long as any other, so that the tree is approximately balanced.


PROPERTIES:

A red-black tree is a binary tree that satisﬁes the following red-black properties:
1. Every node is either red or black.
2. The root is black.
3. Every leaf ( NIL ) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant leaves contain the
same number of black nodes.

ROTATION
left_rotate_pseudocode(tree T, node x): (si x != T.nil && root.parent == T.nil)
node y = x.right;	//set y
x.right = y.left; //turn y's left subtree into x's right subtree
if (y.left != T.null)
	y.left.p = x;
y.p = x.p;
if (x.p == T.null)
	T.root = y;
else if (x == x.p.left)
	x.p.left = y;
else
	x.p.right = y;
y.left = x;
x.p = y;

right_rotate_pseudocode(tree T, node x): (si x != T.nil && root.parent == T.nil)
node y = x.left;	//set y
x.left = y.right; //turn x's left subtree into x's right subtree
if (y.right != T.null)
	y.right.p = x;
y.p = x.p;
if (x.p == T.null)
	T.root = y;
else if (x == x.p.right)
	x.p.right = y;
else
	x.p.left = y;
y.right = x;
x.p = y;


INSERTION:
On insere une cle z dans le red/black tree, et on lui donne la couleur rouge.
Apres on fixe les couleurs avec rb-insert-fixup.

rb-insert(T, z)
{
	y = T.null;
	x = T.root;
	while (x != T.null)
	{
		y = x;
		if (z.key < x.key)
			x = x.left;
		else
			x = x.right;
	}

	z.p = y;
	if (y == T.null)
		t.root = z;
	else if (z.key < y.key)
		y.left = z;
	else
		y.right = z;

	z.left = T.null;
	z.right = T.null;
	z.color = RED;
	rb-insert-fixup(T,z)
}


INSERT-FIXUP:
3 grandes etapes:
	1. Quelles proprietes on niff en mettant une node rouge a un endroit de l'arbre
	2. But de la boucle while ?
	3. Les trois cas possibles.

note : case 2 et 3 sont similaires, juste que case 2 rajoute une rotation pour se
transformer en case 3.

rb-insert-fixup(T, z)
{
	while (z.p.color == RED)
	{
		if (z.p == z.p.p.left)
		{
			y = z.p.p.right;
			if (y.color == RED)
			{
				z.p.color = BLACK;				// case 1
				y.color = BLACK;				// case 1
				z.p.p.color = RED;				// case 1
				z = z.p.p;						// case 1
			}
			else if (z == z.p.right)
			{
				z = z.p;						// case 2
				left_rotate_pseudocode(T, z);	// case 2
			}
			//ICI JE SUIS PAS SUR SI LE ELSE EST BON
			else {

			z.p.color = BLACK;					// case 3
			z.p.p.color = RED;					// case 3
			right_rotate_pseudocode(T, z.p.p)	// case 3
			}
		}
		else
		{
			y = z.p.p.left;
			if (y.color == RED)
			{
				z.p.color = BLACK;				// case 1
				y.color = BLACK;				// case 1
				z.p.p.color = RED;				// case 1
				z = z.p.p;						// case 1
			}
			else if (z == z.p.left)
			{
				z = z.p;						// case 2
				right_rotate_pseudocode(T, z);	// case 2
			}
			//IDEM QUEN HAUT
			else {

			z.p.color = BLACK;					// case 3
			z.p.p.color = RED;					// case 3
			left_rotate_pseudocode(T, z.p.p)	// case 3
			}
		}

	}
}


DELETION RED/BLACK TREE:
Deja, on utilise le transplant de larbre binaire que l'on modifie un peu.
rb-transplant(T, u, v)
{
	if (u.p == T.NULL)
		T.root = v;
	else if (u == u.p.left)
		u.p.left = v;
	else
		u.p.right = v;
	v.p = u.p;
}

rb-delete(T, z)
{
	y = z;
	// on a besoin de garder la couleur d'origine de y au cas ou il y
	// aurait un chgt de couleur a faire a la fin (delete-fixup)
	y-original-color = y.color;
	if (z.left == T.null)
	{
		x = z.right;
		rb-transplant(T, z, z.right);
	}
	else if (z.right == T.null)
	{
		x = z.left;
		rb-transplant(T, z, z.left);
	}
	else
	{
		y = tree-minimum(z.right)
		y-original-color = y.color;
		x = y.right;
		if (y.p == z)
			x.p = y;
		else
		{
			rb-transplant(T, y, y.right);
			y.right.p = y;
		}
		rb-transplant(T, z, y)
		y.left = z.left;
		y.left.p = y;
		y.color = z.color;
	}

	if (y-original-color == BLACK)
		rb-delete-fixup(T, x);
}


rb-delete-fixup(T, x)
{
	while (x != T.root && x.color == BLACK)
	{
		if (x == x.p.left)
		{
			w = x.p.right;
			if (w.color == RED)
			{
				w.color = BLACK;							// case 1
				x.p.color = RED;							// case 1
				left-rotate(T, x.p);						// case 1
				w = x.p.right;								// case 1
			}
			if (w.left.color == BLACK && w.right.color == BLACK)
			{
				w.color = RED;								// case 2
				x = x.p;									// case 2
			}
			else
			{
				if (w.right.color == BLACK)
				{
					w.left.color = BlACK;					// case 3
					w.color = RED;							// case 3
					right-rotate(T, w);						// case 3
					w = x.p.right;							// case 3
				}
				w.color = x.p.color;						// case 4
				x.p.color = BLACK;							// case 4
				w.right.color = BLACK;						// case 4
				left_rotate_pseudocode(T, x.p);				// case 4
				x = T.root;									// case 4
			}
		}
		else
		{
			w = x.p.left;
			if (w.color == RED)
			{
				w.color = BLACK;
				x.p.color = RED;
				right-rotate(T, x.p);
				w = x.p.right;
			}
			if (w.right.color == BLACK && w.left.color == BLACK)
			{
				w.color = RED;
				x = x.p;
			}
			else
			{
				if (w.left.color == BLACK)
				{
					w.right.color = BlACK;
					w.color = RED;
					left-rotate(T, w);
					w = x.p.left;
				}
				w.color = x.p.color;
				x.p.color = BLACK;
				w.left.color = BLACK;
				left_rotate_pseudocode(T, x.p);
				x = T.root;
			}
		}
	}
	x.color = BLACK;
}

*/
