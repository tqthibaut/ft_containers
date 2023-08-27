#pragma once

#include "node.hpp"
#include <iostream>

namespace	ft
{

	template <class T, class Node = const ft::RBT_Node<T> >
	class map_const_iterator;

	template <class T, class Node = ft::RBT_Node<T> >
	class map_iterator
	{
		// class map_const_iterator<class U>;

		public:
			typedef		T								value_type;
			typedef		T*								pointer;
			typedef		T&								reference;
			typedef		std::ptrdiff_t					difference_type;
			typedef		std::bidirectional_iterator_tag	iterator_category;
			// typedef typename	ft::map_iterator<const value_type>	map_const_iterator;

		protected:
			Node *	_current;
			Node *	_root;
			Node *	_leaf;

			Node *	max(Node *	node)
			{
				while (node->right != _leaf)
					node = node->right;
				return (node);
			}

			Node *	min(Node *	node)
			{
				while (node->left != _leaf)
					node = node->left;
				return (node);
			}

		public:
			map_iterator() : _current(), _root(), _leaf() {}
			map_iterator (map_iterator const & src) : _current(src.getNode()), _root(src.getRoot()), _leaf(src.getLeaf()) { }
			map_iterator(Node * current, Node * root) : _current(current), _root(root)
			{
				if (_root->parent == NULL)
					_leaf = _root;
				else
					_leaf = _root->parent;
			};

			map_iterator &	operator=(map_iterator const & rhs)
			{
				_current = rhs.getNode();
				_root = rhs.getRoot();
				_leaf = rhs.getLeaf();
				return	*this;
			}
			//	Getters
			Node *	getNode() const {return _current;}
			Node *	getRoot() const {return _root;}
			Node *	getLeaf() const {return _leaf;}

			bool	operator==(map_iterator const & rhs) const {return _current == rhs.getNode();}

			template <class U>
			bool	operator==(map_const_iterator<U> const & rhs) const {return _current == rhs.getNode();}

			bool	operator!=(map_iterator const & rhs) const {return _current != rhs.getNode();}
			template <class U>
			bool	operator!=(map_const_iterator<U> const & rhs) const {return _current != rhs.getNode();}
			// bool	operator!=(map_const_iterator const & rhs) const {return _current != rhs._current;}

			reference	operator*() const {return _current->data;}
			//ca marche
			pointer		operator->() const {return &operator*();}


			map_iterator &	operator++()
			{
				if (_current == _leaf)
					_current = min(_root);
				else if (_current->right != _leaf)
					_current = min(_current->right);
				else if (_current->parent != _leaf)
				{
					while (_current->parent != _leaf && _current->parent->right == _current)
						_current = _current->parent;
					if (_current == _current->parent->left)
						_current = _current->parent;
					else
						_current = _leaf;
				}
				else
					_current = _leaf;
				// if (_current != _leaf)
				// 	_current = min(_current->right);
				// Node *	y = _current->parent;

				return *this;
			}

			map_iterator	operator++(int)
			{
				map_iterator	tmp = *this;
				operator++();
				return (tmp);
			}

			map_iterator &	operator--()
			{
				if (_current == _leaf)
					_current = max(_root);
				else if (_current->left != _leaf) {
					_current = max(_current->left);
				}
				else if (_current->parent != _leaf) {
					while (_current->parent != _leaf && _current->parent->left == _current)
						_current = _current->parent;
					if (_current == _current->parent->right)
						_current = _current->parent;
					else
						_current = _leaf;
				}
				else {
					_current = _leaf;
				}
				return *this;
			}

			map_iterator	operator--(int)
			{
				map_iterator	tmp = *this;
				operator--();
				return (tmp);
			}
	};

	template <class T, class Node>
	class map_const_iterator
	{

		public:
			typedef	const T 			value_type;
			typedef	const T*				pointer;
			typedef	const T&				reference;
			typedef	std::ptrdiff_t		difference_type;
			typedef	std::bidirectional_iterator_tag	iterator_category;


		private:
			Node *	_current;
			Node *	_root;
			Node *	_leaf;

			Node *	max(Node * node)
			{
				while (node->right != _leaf)
					node = node->right;
				return (node);
			}

			Node *	min(Node * node)
			{
				while (node->left != _leaf)
					node = node->left;
				return (node);
			}



		public:
			map_const_iterator() : _current(), _root(), _leaf() { }
			map_const_iterator (map_const_iterator const & src) : _current(src.getNode()), _root(src.getRoot()), _leaf(src.getLeaf()) { }
			template <class U>
			map_const_iterator (map_iterator<U> const & src) : _current(src.getNode()), _root(src.getRoot()), _leaf(src.getLeaf()) { }
			map_const_iterator(Node * current, Node * root) :  _current(current), _root(root)
			{
				if (_root->parent == NULL)
					_leaf = _root;
				else
					_leaf = _root->parent;
			};

			Node *	getNode() const {return _current;}
			Node *	getRoot() const {return _root;}
			Node *	getLeaf() const {return _leaf;}
			// comme dhab, la std essaye de move et de move_assign
			template <class U>
			map_const_iterator &	operator=(const map_iterator<U> & rhs)
			{
				_current = rhs.getNode();
				_root = rhs.getRoot();
				_leaf = rhs.getLeaf();
				return	*this;
			}
			map_const_iterator &	operator=(map_const_iterator const & rhs)
			{
				_current = rhs.getNode();
				_root = rhs.getRoot();
				_leaf = rhs.getLeaf();
				return	*this;
			}

			template <class U>
			bool	operator==(map_iterator<U> const & rhs) const {return _current == rhs.getNode();}
			bool	operator==(map_const_iterator const & rhs) const {return _current == rhs.getNode();}
			bool	operator!=(map_const_iterator const & rhs) const {return _current != rhs.getNode();}
			template <class U>
			bool	operator!=(map_iterator<U> const & rhs) const {return _current != rhs.getNode();}

			// bool	operator!=(map_iterator const & rhs) const {return _current != rhs._current;}
			reference	operator*() const { return _current->data; }
			pointer		operator->() const { return &operator*(); }

			map_const_iterator &	operator++()
			{
				if (_current == _leaf)
					_current = min(_root);
				else if (_current->right != _leaf)
					_current = min(_current->right);
				else if (_current->parent != _leaf)
				{
					while (_current->parent != _leaf && _current->parent->right == _current)
						_current = _current->parent;
					if (_current == _current->parent->left)
						_current = _current->parent;
					else
						_current = _leaf;
				}
				else
					_current = _leaf;
				// if (_current != _leaf)
				// 	_current = min(_current->right);
				// Node *	y = _current->parent;

				return *this;
			}

			map_const_iterator	operator++(int)
			{
				map_const_iterator	tmp(*this);
				operator++();
				return tmp;
			}

			map_const_iterator &	operator--()
			{
				if (_current == _leaf)
					_current = max(_root);
				else if (_current->left != _leaf) {
					_current = max(_current->left);
				}
				else if (_current->parent != _leaf) {
					while (_current->parent != _leaf && _current->parent->left == _current)
						_current = _current->parent;
					if (_current == _current->parent->right)
						_current = _current->parent;
					else
						_current = _leaf;
				}
				else {
					_current = _leaf;
				}
				return *this;
			}

			map_const_iterator		operator--(int)
			{
				map_const_iterator	tmp = *this;
				operator--();
				return (tmp);
			}
	};
}
