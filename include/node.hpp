#pragma once
#include <iostream>

namespace ft
{

	template<class T>
	class RBT_Node 
	{
		public:
			typedef T	value_type;

			value_type		data;
			RBT_Node *		parent;
			RBT_Node *		left;
			RBT_Node *		right;
			bool		color; // 0 == black, 1 == red
			
			RBT_Node() : data(), parent(NULL), left(NULL), right(NULL) {};
			// {std::cout << "A node was created and allocated\n";};
			RBT_Node(RBT_Node const & src)
				: data(src.data), parent(src.parent), left(src.left), right(src.right), color(src.color) {};
			RBT_Node(value_type const & val) : data(val), parent(NULL), left(NULL), right(NULL) {};
			~RBT_Node() {};

			RBT_Node &	operator= (RBT_Node const & rhs) 
			{
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->right = rhs.right;
				this->data = rhs.data;
				this->color = rhs.color;
				//std::cout << "Operator = of Node called\n";
				return *this;
			}
			// bool operator==(const BST_Node& nd)
			// {
			// 	if (value == nd.value)
			
			//		return (true);
			// 	return (false);
			// }
	};

};