#pragma once
#include <iostream>
#include "List.h"
using namespace  std;

template <typename keyType, typename valueType>

class RBtree {
private:

	class Node
	{
	public:
		bool color; 
		keyType key;
		valueType value;
		Node* parents;
		Node* left;
		Node* right;
	};

	Node* root;  
	Node* nil;
	size_t size;
	
	void leftRotate(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left != NULL)
			y->left->parents = x;

		y->parents = x->parents;
		if (x->parents == NULL)
			root = y;
		else {
			if (x == x->parents->left)
				x->parents->left = y;
			else
				x->parents->right = y;
		}
		y->left = x;
		x->parents = y;
	};
	
	void rightRotate(Node* y) {
		Node* x = y->left;
		y->left = x->right;
		if (x->right != NULL)
			x->right->parents = y;

		x->parents = y->parents;
		if (y->parents == NULL)
			root = x;
		else {
			if (y == y->parents->right)
				y->parents->right = x;
			else
				y->parents->left = x;
		}
		x->right = y;
		y->parents = x;
	};

	
	void insertFix(Node* node)
	{
		Node* parent;
		parent = node->parents;
		while (node != root && parent->color == true)
		{
			Node* gparent = parent->parents;
			if (gparent->left == parent)
			{
				Node* uncle = gparent->right;
				if (uncle != NULL && uncle->color == true)
				{
					parent->color = false;
					uncle->color = false;
					gparent->color = true;
					node = gparent;
					parent = node->parents;
				}
				else
				{
					if (parent->right == node)
					{
						leftRotate(parent);
						swap(node, parent);
					}
					rightRotate(gparent);
					gparent->color = true;
					parent->color = false;
					break;
				}
			}
			else
			{
				Node* uncle = gparent->left;
				if (uncle != NULL && uncle->color == true)
				{
					gparent->color = true;
					parent->color = false;
					uncle->color = false;

					node = gparent;
					parent = node->parents;
				}
				else
				{
					if (parent->left == node)
					{
						rightRotate(parent);
						swap(parent, node);
					}
					leftRotate(gparent);
					parent->color = false;
					gparent->color = true;
					break;
				}
			}
		}
		root->color = false;
	};
	void removeFix(Node* node)
	{
		Node* otherNode;
		Node* parent;
		parent = node->parents;
		while ((!node) || node->color == false && node != root)
		{
			if (parent->left == node)
			{
				otherNode = parent->right;
				if (otherNode->color == true)
				{
					otherNode->color = false;
					parent->color = true;
					leftRotate(parent);
					otherNode = parent->right;
				}
				else
				{
					if (!(otherNode->right) || otherNode->right->color == false)
					{
						otherNode->left->color = false;
						otherNode->color = true;
						rightRotate(otherNode);
						otherNode = parent->right;
					}
					otherNode->color = parent->color;
					parent->color = false;
					otherNode->right->color = false;
					leftRotate(parent);
					node = root;
					break;
				}
			}
			else
			{
				otherNode = parent->left;
				if (otherNode->color == true)
				{
					otherNode->color = false;
					parent->color = true;
					rightRotate(parent);
					otherNode = parent->left;
				}
				if ((!otherNode->left || otherNode->left->color == false) && (!otherNode->right || otherNode->right->color == false))
				{
					otherNode->color = true;
					node = parent;
					parent = node->parents;
				}
				else
				{
					if (!(otherNode->left) || otherNode->left->color == false)
					{
						otherNode->right->color = false;
						otherNode->color = true;
						leftRotate(otherNode);
						otherNode = parent->left;
					}
					otherNode->color = parent->color;
					parent->color = false;
					otherNode->left->color = false;
					rightRotate(parent);
					node = root;
					break;
				}
			}
		}
		if (node)
			node->color = false;
	};

	void printHelper(Node* node) {
		if (node != nil) {
			cout << node->key << " : " << node->value << endl;
			if (node->left != NULL && node->left != nil)
				printHelper(node->left);
			if (node->right != NULL && node->right != nil)
				printHelper(node->right);
		}
	};
	
	void transplant(Node* current, Node* newNode)
	{
		if (current->parents == NULL) {
			current = newNode;
		}
		else if (current == current->parents->left) {
			current->parents->left = newNode;
		}
		else { current->parents->right = newNode; }
		newNode->parents = current->parents;

	};
	
	List<keyType> getHelpKey(List<keyType> list, Node* node) {
		if (node != nil) {
			list.push_back(node->key);
			if (node->left != NULL && node->left != nil)
				list = getHelpKey(list, node->left);
			if (node->right != NULL && node->right != nil)
				list = getHelpKey(list, node->right);
			return list;
		}
	};

	List<valueType> getHelpValue(List<valueType> list, Node* node) {
		if (node != nil) {
			list.push_back(node->value);
			if (node->left != NULL && node->left != nil)
				list = getHelpValue(list, node->left);
			if (node->right != NULL && node->right != nil)
				list = getHelpValue(list, node->right);
			return list;
		}
	};


public:

	RBtree() {
		nil = new Node;
		nil->color = 0;
		nil->left = nullptr;
		nil->right = nullptr;
		root = nil;
		size = 0;
	};
	~RBtree() {
		clear();
	};

	bool isEmpty() {
		if (root == nil) { return true; }
		else return false;
	}
	bool at(keyType key) {
		Node* newNode = root;
		bool flag = 0;
		if (newNode->key == key) {
			return true;
			flag = 1;
		}
		else {
			while (newNode != nil) {
				if (newNode->key == key) {
					return true;
					flag = 1;
				}
				else
					if (key > newNode->key) { newNode = newNode->right; }
					else
						if (key < newNode->key) { newNode = newNode->left; }
			}
		}
		if (flag == 0) return false;
	};
	size_t get_size() {
		return size;
	}
	
	void insert(keyType key, valueType value)
	{
		Node* newNode = new Node;
		newNode->color = true;
		newNode->key = key;
		newNode->value = value;
		newNode->right = nil;
		newNode->left = nil;
		newNode->parents = NULL;
		size++;
		
		if (root == nil) {
			newNode->color = false;
			root = newNode;
			return;
		}
		else {
			Node* currentRoot = root;
			Node* parNewNode = NULL;
			while (currentRoot != nil) {
				parNewNode = currentRoot;
				if (newNode->key < currentRoot->key) {
					currentRoot = currentRoot->left;
				}
				else {
					currentRoot = currentRoot->right;
				}
			}
			newNode->parents = parNewNode;

			if (newNode->key < parNewNode->key)
				parNewNode->left = newNode;
			else
				parNewNode->right = newNode;
		}
		insertFix(newNode);
	};
	
	void remove(keyType key)
	{
		Node* nodeToBeDeleted = find(key);
		bool colorDeleted = nodeToBeDeleted->color;
		Node* temp = nodeToBeDeleted;
		Node* y;
		if (nodeToBeDeleted->left == nil) {
			temp = nodeToBeDeleted->right;
			transplant(nodeToBeDeleted, temp);
			if (root == nodeToBeDeleted) root = temp;
			delete nodeToBeDeleted;
		}
		else if (nodeToBeDeleted->right == nil) {
			temp = nodeToBeDeleted->left;
			transplant(nodeToBeDeleted, temp);
			if (root == nodeToBeDeleted) root = temp;
			delete nodeToBeDeleted;
		}
		else {
			y = nodeToBeDeleted->right;
			while (y->left != nil) {
				y = y->left;
			}
			colorDeleted = y->color;
			temp = y->right;
			if (y->parents == nodeToBeDeleted) {
				temp->parents = y;
			}
			else {
				transplant(y, y->right);
				y->right = nodeToBeDeleted->right;
				y->right->parents = y;
			}
			transplant(nodeToBeDeleted, y);
			y->left = nodeToBeDeleted->left;
			y->left->parents = y;
			y->color = nodeToBeDeleted->color;

			if (root == nodeToBeDeleted) {
				y->parents = NULL;
				root = y;
			}
			delete nodeToBeDeleted;
			if (colorDeleted == 0) {
				removeFix(temp);
			}
		}
		size--;

	};
	
	Node* find(keyType key)
	{
		Node* newNode = root;
		bool flag = 0;
		if (newNode->key == key) {
			return newNode;
			flag = 1;
		}
		else {
			while (newNode != nil) {
				if (newNode->key == key) {
					return newNode;
					flag = 1;
				}
				else
					if (key > newNode->key) { newNode = newNode->right; }
					else
						if (key < newNode->key) { newNode = newNode->left; }
			}
		}
		if (flag == 0) throw out_of_range("There is no element with this key in the map\n");
	};
	void clear()
	{
		while ((root != nil) && (root != NULL))
			remove(root->key);
		root = nil;
		size = 0;
	};
	List <keyType> get_keys()
	{
		List <keyType> listKey;
		if (root == NULL || root == nil) {
			throw out_of_range("Map is empty\n");
		}
		else {
			listKey = getHelpKey(listKey, root);
			return listKey;
		}
	}

	List <valueType> get_values()
	{
		List <valueType> listValue;
		if (root == NULL || root == nil) {
			throw out_of_range("Map is empty\n");
		}
		else {
			listValue = getHelpValue(listValue, root);
			return listValue;
		}
	}
	
	void print() {
		if (root == nil)
			cout << "Map is empty\n" << endl;
		else
			printHelper(root);
	};

}; 
