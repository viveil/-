#pragma once
#define COLOR_RED 1
#define COLOR_BLACK 0
#include"List.h"
#include <stdexcept>
#include <string>
using namespace std;
template<typename keyTape, typename valueTape>
class Map {
public:
	class Node
	{
	public:
		Node(bool color = COLOR_RED, keyTape key = keyTape(), Node* parent = NULL, Node* left = NULL, Node* right = NULL, valueTape value = valueTape()) :color(color), key(key), parent(parent), left(left), right(right), value(value) {}
		keyTape key;
		valueTape value;
		bool color;
		Node* parent;
		Node* left;
		Node* right;
	};
private:
	Node* Root;
	Node* Nil;

	

	void delete_node(Node* find_node)
	{
		Node* node_with_fix, * cur_for_change;
		cur_for_change = find_node;
		bool cur_for_change_original_color = cur_for_change->color;
		if (find_node->left == Nil)
		{
			node_with_fix = find_node->right;
			transplant(find_node, find_node->right);
		}
		else if (find_node->right == Nil)
		{
			node_with_fix = find_node->left;
			transplant(find_node, find_node->left);
		}
		else
		{
			cur_for_change = min(find_node->right);
			cur_for_change_original_color = cur_for_change->color;
			node_with_fix = cur_for_change->right;
			if (cur_for_change->parent == find_node)
			{
				node_with_fix->parent = cur_for_change;
			}
			else
			{
				transplant(cur_for_change, cur_for_change->right);
				cur_for_change->right = find_node->right;
				cur_for_change->right->parent = cur_for_change;
			}
			transplant(find_node, cur_for_change);
			cur_for_change->left = find_node->left;
			cur_for_change->left->parent = cur_for_change;
			cur_for_change->color = find_node->color;
		}
		delete find_node;
		if (cur_for_change_original_color == COLOR_RED)
		{
			this->delete_fix(node_with_fix);
		}
	}

	void transplant(Node* oldNode, Node* newNode)
	{
		if (oldNode->parent == Nil)
		{
			Root = newNode;
		}
		else if (oldNode == oldNode->parent->left)
		{
			oldNode->parent->left = newNode;
		}
		else
		{
			oldNode->parent->right = newNode;
		}
		newNode->parent = oldNode->parent;
	}

	void clear_tree(Node* tree)
	{
		if (tree != Nil)
		{
			clear_tree(tree->left);
			clear_tree(tree->right);
			delete tree;
		}
	}

	

	Node* min(Node* node)
	{
		while (node->left != Nil)
		{
			node = node->left;
		}
		return node;
	}

	Node* max(Node* node)
	{
		while (node->right != Nil)
		{
			node = node->right;
		}
		return node;
	}

	Node* grandparent(Node* current)
	{
		if ((current != Nil) && (current->parent != Nil))
			return current->parent->parent;
		else
			return Nil;
	}

	Node* uncle(Node* current)
	{
		Node* current1 = grandparent(current);
		if (current1 == Nil)
			return Nil; 
		if (current->parent == current1->left)
			return current1->right;
		else
			return current1->left;
	}

	Node* sibling(Node* n)
	{
		if (n == n->parent->left)
			return n->parent->right;
		else
			return n->parent->left;
	}

	Node* find_key(keyTape key)
	{
		Node* node = this->Root;
		while (node != Nil && node->key != key)
		{
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != Nil)
			return node;
		else
			throw std::out_of_range("No key");
	}

	

	void print_helper(Node* root, string indent, bool last)
	{
		if (root != Nil)
		{
			cout << indent;
			if (last)
			{
				cout << "R---";
				indent += "   ";
			}
			else
			{
				cout << "L----";
				indent += "|  ";
			}
			string sColor = !root->color ? "black" : "red";
			cout << root->key << " " << root->value << " (" << sColor << ")" << endl;
			print_helper(root->left, indent, false);
			print_helper(root->right, indent, true);
		}
	}

	void list_key_or_value(int mode, List<keyTape>* list)
	{
		if (this->Root != Nil)
			this->key_or_value(Root, list, mode);
		else
			throw std::out_of_range("The tree is empty");
	}

	void key_or_value(Node* tree, List<keyTape>* list, int mode)
	{
		if (tree != Nil)
		{
			key_or_value(tree->left, list, mode);
			if (mode == 1)
				list->push_back(tree->key);
			else
				list->push_back(tree->value);
			key_or_value(tree->right, list, mode);
		}
	}

	

	void insert_fix(Node* node)
	{
		Node* uncle;
		while (node != this->Root && node->parent->color == COLOR_RED)
		{
			if (node->parent == this->grandparent(node)->left)
			{
				uncle = this->uncle(node);
				if (uncle->color == COLOR_RED)
				{
					node->parent->color = COLOR_BLACK;
					uncle->color = COLOR_BLACK;
					this->grandparent(node)->color = COLOR_RED;
					node = this->grandparent(node);
				}
				else {
					if (node == node->parent->right)
					{
						node = node->parent;
						this->left_rotate(node);
					}
					
					node->parent->color = COLOR_BLACK;
					this->grandparent(node)->color = COLOR_RED;
					this->right_rotate(this->grandparent(node));
				}
			}
			else {
				uncle = this->uncle(node);
				if (uncle->color == COLOR_RED)
				{
					node->parent->color = COLOR_BLACK;
					uncle->color = COLOR_BLACK;
					this->grandparent(node)->color = COLOR_RED;
					node = this->grandparent(node);
				}
				else {
					if (node == node->parent->left)
					{
						node = node->parent;
						this->right_rotate(node);
					}
					node->parent->color = COLOR_BLACK;
					this->grandparent(node)->color = COLOR_RED;
					this->left_rotate(this->grandparent(node));
				}
			}
		}
		this->Root->color = COLOR_BLACK;
	}

	void delete_fix(Node* node)
	{
		Node* sibling;
		while (node != this->Root && node->color == COLOR_BLACK)
		{
			sibling = this->sibling(node);
			if (sibling != Nil)
			{
				if (node == node->parent->left)
				{
					if (sibling->color == COLOR_BLACK)
					{
						node->parent->color = COLOR_BLACK;
						sibling->color = COLOR_RED;
						this->left_rotate(node->parent);
						sibling = this->sibling(node);
					}
					if (sibling->left->color == COLOR_RED && sibling->right->color == COLOR_RED)
					{
						sibling->color = COLOR_BLACK;
						node = node->parent;
					}
					else
					{
						if (sibling->right->color == COLOR_RED)
						{
							sibling->left->color = COLOR_RED;
							sibling->color = COLOR_BLACK;
							this->left_rotate(sibling);
							sibling = this->sibling(node);
						}
						sibling->color = node->parent->color;
						node->parent->color = COLOR_RED;
						sibling->right->color = COLOR_RED;
						this->left_rotate(node->parent);
						node = this->Root;
					}
				}
				else
				{
					if (sibling->color == COLOR_BLACK);
					{
						sibling->color = COLOR_RED;
						node->parent->color = COLOR_BLACK;
						this->right_rotate(node->parent);
						sibling = this->sibling(node);
					}
					if (sibling->left->color == COLOR_RED && sibling->right->color)
					{
						sibling->color = COLOR_BLACK;
						node = node->parent;
					}
					else
					{
						if (sibling->left->color == COLOR_RED)
						{
							sibling->right->color = COLOR_RED;
							sibling->color = COLOR_BLACK;
							this->left_rotate(sibling);
							sibling = this->sibling(node);
						}
						sibling->color = node->parent->color;
						node->parent->color = COLOR_RED;
						sibling->left->color = COLOR_RED;
						this->right_rotate(node->parent);
						node = Root;
					}
				}
			}

		}
		this->Root->color = COLOR_BLACK;
	}

	void left_rotate(Node* node)
	{
		Node* right = node->right;
		node->right = right->left;
		if (right->left != Nil)
			right->left->parent = node;
		if (right != Nil)
			right->parent = node->parent;
		if (node->parent != Nil)
		{
			if (node == node->parent->left)
				node->parent->left = right;
			else
				node->parent->right = right;
		}
		else {
			this->Root = right;
		}
		right->left = node;
		if (node != Nil)
			node->parent = right;
	}

	void right_rotate(Node* node)
	{
		Node* left = node->left;
		node->left = left->right;
		if (left->right != Nil)
			left->right->parent = node;
		if (left != Nil)
			left->parent = node->parent;
		if (node->parent != Nil)
		{
			if (node == node->parent->right)
				node->parent->right = left;
			else
				node->parent->left = left;
		}
		else
		{
			this->Root = left;
		}
		left->right = node;
		if (node != Nil)
			node->parent = left;
	}
public: 

	~Map()
	{
		if (this->Root != NULL)
			this->clear();
		Root = NULL;
		delete Nil;
		Nil = NULL;
	}

	Map(Node* Root = NULL, Node* Nil = new Node(0)) :Root(Root), Nil(Nil) {}

	void printTree()
	{
		if (Root)
		{
			print_helper(this->Root, "", true);
		}
		else {
			try {
				if (Root == NULL)
					throw "The tree is empty";
			}
			catch (const char* msg)
			{
				cout << msg << endl;
			}
		}
	}

	void  insert(keyTape key, valueTape value)
	{
		if (this->Root != NULL)
		{
			Node* node = NULL;
			Node* parent = NULL;
			for (node = this->Root; node != Nil; )
			{
				parent = node;
				if (key < node->key)
					node = node->left;
				else if (key > node->key)
					node = node->right;
				else if (key == node->key)
					cout << "key is repeated";
			}

			node = new Node(COLOR_RED, key, Nil, Nil, Nil, value);
			node->parent = parent;

			if (parent != Nil)
			{
				if (key < parent->key)
					parent->left = node;
				else
					parent->right = node;
			}
			insert_fix(node);
		}
		else
		{
			this->Root = new Node(COLOR_BLACK, key, Nil, Nil, Nil, value);
		}
	}

	List<keyTape>* get_keys()
	{
		List<keyTape>* list = new List<keyTape>();
		this->list_key_or_value(1, list);
		return list;
	}

	List<valueTape>* get_values()
	{
		List<valueTape>* list = new List<valueTape>();
		this->list_key_or_value(2, list);
		return list;
	}

	valueTape find(keyTape key)
	{
		Node* node = Root;
		while (node != Nil && node->key != key)
		{
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != Nil)
			return node->value;
		else
			throw std::out_of_range("No key");
	}

	void remove(keyTape key)
	{
		this->delete_node(this->find_key(key));
	}

	void clear()
	{
		this->clear_tree(this->Root);
		this->Root = NULL;
	}

};
