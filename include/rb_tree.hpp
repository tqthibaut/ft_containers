#pragma once

#include "node.hpp"
#include "map_iterator.hpp"
#define BLACK_NODE	0
#define RED_NODE	1

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class rb_tree
	{
		public:
			typedef	T								value_type;
			typedef	Compare							key_compare;
			typedef	ft::RBT_Node<value_type>		Node;
			typedef Node*							pointer;
			typedef	Alloc							allocator_type;
			typedef	std::allocator<Node>			node_alloc_type;
			typedef typename	Alloc::size_type	size_type;
			typedef	map_iterator<T>					iterator;
			typedef	map_const_iterator<T>			const_iterator;


			// Members
			Node *				_root;
			Node *				_leaf;
			size_type			_size;
			allocator_type		_alloc;
			node_alloc_type		_node_alloc;
			key_compare			_comp;

		// Member functions
		public:
			// void	print_node()
			//Constructeur, constructeur par copie, destructeur, operateur assignation, et les nodes sont construites
			// par le tree
			rb_tree(key_compare const & compare = key_compare(), allocator_type const & allocator = allocator_type())
				: _root(NULL), _leaf(NULL), _alloc(allocator), _node_alloc(node_alloc_type()), _comp(compare)
				{
					initLeaf();
					_root = _leaf;
					if (_root == _leaf)
					_size = 0;
				};

			rb_tree(rb_tree const & src)
				: _root(NULL), _leaf(NULL), _alloc(src._alloc), _node_alloc(src._node_alloc), _comp(src._comp)
				{
					initLeaf();
					_root = _leaf;
					_size = 0; // Recheck ca, je sais plus pourquoi javais fait ca
					*this = src;
				}

			~rb_tree()
			{
				clear();
				_node_alloc.destroy(_leaf);
				_node_alloc.deallocate(_leaf, 1);
			}

			rb_tree &	operator=(rb_tree const & rhs)
			{
				if (this != &rhs)
				{
					clear();
					const_iterator it_end = rhs.end();
					for (const_iterator it = rhs.begin(); it != it_end; it++)
					{
						insertNode(*it);
					}
				_size = rhs._size;
				}
				return (*this);
			}

			void	clear()
			{
				clear_parser(_root);
				_size = 0;
				_root = _leaf;
			}

			//Min et max en private ?? A tester.
			Node *	minimum(Node * node) const
			{
				while (node->left != _leaf && node->left != NULL)
					node = node->left;
				return (node);
			}

			Node *	maximum(Node * node) const
			{
				while (node->right != _leaf && node->right != NULL)
					node = node->right;
				return (node);
			}

			Node *	insertNode(value_type const & val)
			{
				// std::cout << "insertNode called\n";
				Node *	z = newNode(val, _leaf);
				Node *	y = _leaf;
				Node *	x = _root;
				while (x != _leaf)
				{
					y = x;
					if (_comp(z->data, x->data))
						x = x->left;
					else
						x = x->right;
				}
				z->parent = y;
				if (y == _leaf)
					_root = z;
				else if (_comp(z->data, y->data))
					y->left = z;
				else
					y->right = z;
				// z->left = NULL;
				// z->right = NULL;
				// z->color = RED_NODE;
				rb_insert_fixup(z);
				_size += 1;
				return (z);
			}

			// Iterator returns
			iterator		begin() {return (iterator(minimum(this->_root), _root));}
			const_iterator	begin() const {return (const_iterator(minimum(this->_root), _root));}
			iterator		end() { return iterator(_leaf, _root);}
			const_iterator	end() const { return const_iterator(_leaf, _root);}

			// Getters
			Node *		root() const { return (this->_root);}
			Node *		leaf() const { return (this->_leaf);}
			size_type	size() const { return (this->_size);}
			// size_type	rb_maxsize() const () {return (this->_alloc.max_size());}
			// Setters
			void		setRoot(Node* root) { _root = root;}
			void		setLeaf(Node* leaf) { _leaf = leaf;}
			void		setSize(size_type size) { _size = size;}


		void deleteNode (Node * z) {
			Node *	y = z;
			Node *	x;
			Node *parent = z->parent;
			bool y_color = getColor(y);
			if (z->left == _leaf) {
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right == _leaf) {
				x = z->left;
				transplant(z, z->left);
			}
			else {
				y = minimum(z->right);
				parent = y->parent;
				y_color = getColor(y);
				x = y->right;
				if (y->parent != z) {
					parent = y->parent;
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				else
					parent = y;
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				setColor(y, getColor(z));
			}
			_node_alloc.destroy(z);
			_node_alloc.deallocate(z, 1);
			if (y_color == BLACK_NODE) {
				deleteFixup(x, parent);
			}
			_size -= 1;
		}

		private:

			void	clear_parser(Node * node)
			{
				if (node->left && node->left != _leaf)
					clear_parser(node->left);
				if (node->right && node->right != _leaf)
					clear_parser(node->right);
				if (node != _leaf) {
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
				}
			}

			void	initLeaf()
			{
				// std::cout << "initLeaf Called\n";
				_leaf = _node_alloc.allocate(1);
				_node_alloc.construct(_leaf, Node());
				// _alloc.construct(&_leaf->data, value_type());
				_leaf->parent = NULL;
				_leaf->right = NULL;
				_leaf->left = NULL;
				_leaf->color = BLACK_NODE;
			}

			Node *	newNode(value_type const & val, Node * parent)
			{
				// std::cout << "newNode called \n";
				Node *	tmp = _node_alloc.allocate(1);
				// tmp = _node_alloc.allocate(1);
				_node_alloc.construct(tmp, Node(val));
				//_alloc.construct(&tmp->data, val);
				tmp->parent = parent;
				tmp->right = _leaf;
				tmp->left = _leaf;
				// tmp->color = RED_NODE;
				setColor(tmp, RED_NODE);
				return (tmp);
			}

			void	left_rotate(Node * x)
			{
				Node *	y;
				y = x->right;
				x->right = y->left;
				if (y->left != _leaf)
				{
					// std::cout << "left rotate, and y->left != leaf\n";
					y->left->parent = x;
				}
				y->parent = x->parent;
				if (x->parent == _leaf)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void	right_rotate(Node * x)
			{
				Node *	y;
				y = x->left;
				x->left = y->right;
				if (y->right != _leaf)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == _leaf)
					_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

		void	rb_insert_fixup (Node * z)
		{
			// std::cout << "fixup called\n";
			Node *	uncle;
			while (getColor(z->parent) == RED_NODE)
			{
				if (z->parent == z->parent->parent->left)
				{
					uncle = z->parent->parent->right;
					if (getColor(uncle) == RED_NODE)
					{
						// std::cout << "fixup case 1";
						setColor(z->parent, BLACK_NODE); //		 case 1
						setColor(uncle, BLACK_NODE); //			 case 1
						setColor(z->parent->parent, RED_NODE); //	 case 1
						z = z->parent->parent; //			 case 1
					}
					else
					{
						// std::cout << "fixup case 2";
						if (z == z->parent->right) {
							z = z->parent; //				 case 2
							left_rotate(z); //				 case 2
						}
						// std::cout << "fixup case 3";

						setColor(z->parent, BLACK_NODE); //		 case 3
						setColor(z->parent->parent, RED_NODE); //	 case 3
						right_rotate(z->parent->parent); //	 case 3
					}
				}
				else {
					uncle = z->parent->parent->left;
					if (getColor(uncle) == RED_NODE)
					{
						setColor(z->parent, BLACK_NODE); //		 case 1
						setColor(uncle, BLACK_NODE); //			 case 1
						setColor(z->parent->parent, RED_NODE); //	 case 1
						z = z->parent->parent; //			 case 1
					}
					else {
						if (z == z->parent->left)
						{
							z = z->parent; //				 case 2
							right_rotate(z); //				 case 2
						}
						setColor(z->parent, BLACK_NODE); //		 case 3
						setColor(z->parent->parent, RED_NODE); //	 case 3
						left_rotate(z->parent->parent); //	 case 3
					}
				}
				if (z == _root)
					break;
			}
			setColor(_root, BLACK_NODE); //							 case 0
		}

		void	transplant(Node * a, Node * b)
		{
			if (a->parent == _leaf)
				_root = b;
			else if (a == a->parent->left)
				a->parent->left = b;
			else
				a->parent->right = b;
			b->parent = a->parent;
		};

	// Called only when the deleted node was BLACK_NODE.
	void	deleteFixup (Node * x, Node *parent)
	{
		Node *	s;
		while (x != _root && getColor(x) == BLACK_NODE) {
			if (x != _leaf && x != NULL)
				parent = x->parent;
			if (x == parent->left) { // if x is a left child
				s = parent->right;
				if (getColor(s) == RED_NODE) { // CASE 1
					setColor(s, BLACK_NODE); // sibling is now back
					setColor(parent, RED_NODE); // parent is now RED_NODE
					left_rotate(parent); // rotate parent
					s = parent->right; // assign s to x's new sibling (since x's position changed)
				}
				if (!s || (getColor(s->left) == BLACK_NODE && getColor(s->right) == BLACK_NODE)) { // CASE 2
					setColor(s, RED_NODE); // sibling is now RED_NODE
					x = parent;
				}
				else {
					if (getColor(s->right) == BLACK_NODE) { // CASE 3 - this might be a _leaf
						setColor(s->left, BLACK_NODE); // sibling's left child becomes BLACK_NODE. This may be a _leaf.
						setColor(s, RED_NODE); // sibling becomes RED_NODE
						right_rotate(s);
						s = parent->right; // since we moved sibling, assign to s x's current sibling
					}
					// CASE 4
					setColor(s, getColor(parent)); // sibling becomes the same color as its parent
					setColor(parent, BLACK_NODE); // x's parent becomes BLACK_NODE
					setColor(s->right, BLACK_NODE); // sibling's child becomes BLACK_NODE (may be _leaf)
					left_rotate(parent);
					x = _root; // move x pointer to root, finishing the loop
				}
			}
			else { // same as above, but left and right are flipped
				s = parent->left;
				if (getColor(s) == RED_NODE) {
					setColor(s, BLACK_NODE);
					setColor(parent, RED_NODE);
					right_rotate(parent);
					s = parent->left;
				}

				if (!s || (getColor(s->right) == BLACK_NODE && getColor(s->left) == BLACK_NODE)) {
					setColor(s, RED_NODE);
					x = parent;
				}
				else {
					if (getColor(s->left) == BLACK_NODE) {
						setColor(s->right, BLACK_NODE);
						setColor(s, RED_NODE);
						left_rotate(s);
						s = parent->left;
					}

					setColor(s, getColor(parent));
					setColor(parent, BLACK_NODE);
					setColor(s->left, BLACK_NODE);
					right_rotate(parent);
					x = _root;
				}
			}
			if (x == _leaf)
				break;
		}
		setColor(x, BLACK_NODE);
	};

		void	setColor (Node *node, bool color)
		{
			if (node != NULL && node != _leaf)
				node->color = color;
		}

		bool	getColor (Node *node)
		{
			if (node == NULL || node == _leaf)
				return BLACK_NODE;
			return node->color;
		}

	};
}

