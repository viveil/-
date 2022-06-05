#pragma once
#include <iostream>
#include <stdexcept> 
#include "RBTree.h"
using namespace std;

template <typename Tkey, typename Tvalue>

class ListHuffman {

private:

	class Node {
	public:
		Tkey key; 
		Tvalue value;
		Node* next; 
	};
	Node* head; 
	Node* tail; 

public:
	
	ListHuffman(Tkey key, Tvalue value) {

		Node* temp = new Node; 
		temp->key = key;
		temp->value = value;
		temp->next = tail;
		head = temp;
		tail = temp;
	}

	
	ListHuffman() {
		head = tail = NULL;
		Node* temp = new Node; 
		temp->next = NULL;
		temp->key = NULL;
		temp->value = NULL;
	}

	 


	
	int get_size() {
		int list_size = 0;
		Node* temp = head;
		while (temp != NULL) {
			list_size++;
			temp = temp->next;
		}
		return list_size;
	}

	
	Node* at(size_t index) {
		if (index < get_size()) 
		{
			Node* temp = head; 
			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}
			return temp;
		}
		else {
			throw out_of_range("The position of the element is out of range List index\n"); 
		}
	}


	bool isEmpty() {
		return head == NULL;
	}

	
	void clearList() {
		Node* temp = head; 
		while (head != NULL) {
			temp = head->next;
			delete head;
			head = temp;
		}
		tail = NULL;
	}

	
	void push_back(Tkey key, Tvalue value) {
		Node* temp = new Node;
		if (isEmpty() == 1) { 
			temp->key = key;
			temp->value = value;
			temp->next = NULL;
			head = temp;
			tail = temp;
		}
		else { 
			temp->key = key;
			temp->value = value;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
		}

	}


	void pop_front() {

		if (isEmpty() == 0) 
		{
			Node* temp = head; 
			head = head->next;
			delete temp;
			if (head == NULL) tail = head;
		}
		else {
			throw invalid_argument("List is empty. First element cannot be deleted"); // Error message 
		}
	}

	void printList() {
		Node* temp = head;
		while (temp != NULL)
		{
			cout << temp->key << " - " << temp->value << "; ";
			temp = temp->next;
		}
	}

	void sort() {
		Node* index = NULL;
		Node* current = head;
		Tkey tempKey;
		Tvalue tempValue;
		if (head == NULL) {
			return;
		}
		else {
			while (current != NULL) {
				index = current->next;
				while (index != NULL) {
					if (current->value > index->value) {
						tempKey = current->key;
						tempValue = current->value;
						current->key = index->key;
						current->value = index->value;
						index->key = tempKey;
						index->value = tempValue;
					}
					index = index->next;
				}
				current = current->next;
			}
		}
	}

};

class AlgoHuffman {
private:
	class Elem {

	public:

		char symbol;
		size_t freq;
		string code;
		Elem* parents;
		Elem* left;
		Elem* right;
		Elem* next;
	};
	size_t sizeTree;
	Elem* root;
	Elem* tail;
	Elem* head;



	bool isEmpty() {
		return head == NULL;
	}


	void printHelp(Elem* node) {
		if (node->freq != NULL) {
			cout << node->freq << " : " << node->code << endl;
			if (node->left != NULL)
				printHelp(node->left);
			if (node->right != NULL)
				printHelp(node->right);
		}
	};
	float memory(string inputString) {
		int memory = inputString.length() * 8;
		return memory;
	};
	void sorting() {
		Elem* index = NULL;
		Elem* current = head;
		Elem* tempLeft = NULL;
		Elem* tempRight = NULL;
		char tempSymb;
		size_t tempFreq;
		if (head == NULL) {
			return;
		}
		else {
			while (current != NULL) {
				index = current->next;
				while (index != NULL) {
					if (current->freq > index->freq) {
						tempSymb = current->symbol;
						tempFreq = current->freq;
						tempLeft = current->left;
						tempRight = current->right;
						current->symbol = index->symbol;
						current->freq = index->freq;
						current->left = index->left;
						current->right = index->right;
						index->symbol = tempSymb;
						index->freq = tempFreq;
						index->left = tempLeft;
						index->right = tempRight;
					}
					index = index->next;
				}
				current = current->next;
			}
		}
	}
	void code(Elem* help) {
		if (help->freq != NULL)  {
			if (help->left != NULL) {
				help->left->code = help->code + '0';
				code(help->left);
			}
			if (help->right != NULL) {
				help->right->code = help->code + '1';
				code(help->right);
			}
		}

	}

	Elem* at(size_t index) {
		if (index < get_size()) 
		{
			Elem* temp = head; 
			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}
			return temp;
		}
		else {
			throw out_of_range("The position of the element is out of range List index\n"); // Error message
		}
	}
	
	void push_front(Elem* value) {
		Elem* current = new Elem;
		if (head == NULL) {
			current = value;
			head = current;
			tail = head;
		}
		else {
			current = value;
			current->next = head;
			tail = head;
			head = current;
		}
	}
public:
	RBtree<char, int> map;
	string oridginalString;
	string codingString;
	string decodingString;
	AlgoHuffman(string str) {
		sizeTree = 0;
		root = NULL;
		tail = NULL;
		head = NULL;
		oridginalString = str;
		createEncodingTable(oridginalString, map);
	};
	float compressionRatio(string inputString, string outputString) {
		float compression = memory(inputString) / outputString.length();
		return compression;
	};
	size_t get_size() {
		return sizeTree;
	}
	void Table(Elem* node, RBtree<char, string>& tab) {
		if (node->freq != NULL)  {
			if (map.at(node->symbol)) {
				tab.insert(node->symbol, node->code);
			}
			if (node->right != NULL)
				Table(node->right, tab);
			if (node->left != NULL)
				Table(node->left, tab);
		}
	};
	void createEncodingTable(string inputString, RBtree<char, int>& map) {
		if (inputString.length() == 0) {
			throw invalid_argument("Input string is empty\n");
		}
		else {
			for (int i = 0; inputString[i] != '\0'; i++) {
				if (map.isEmpty()) {
					map.insert(inputString[i], 1);
				}
				else {
					if (map.at(inputString[i])) {
						map.find(inputString[i])->value++;
					}
					else {
						map.insert(inputString[i], 1);
					}
				}
			}
		}

	};
	void HuffmanTree(RBtree<char, int>& map) {
		ListHuffman <char, int> leaf;
		Elem* current_head = new Elem;
		Elem* help1 = new Elem;
		Elem* help2 = new Elem;
		List <char> key = map.get_keys();
		List <int> value = map.get_values();
		for (int i = 0; i < map.get_size(); i++) {
			leaf.push_back(key.get_head()->data, value.get_head()->data);
			key.pop_front();
			value.pop_front();
		}
		leaf.sort();
		int index = 0; 
		while (leaf.get_size() != index) {
			Elem* current = new Elem;
			if (head == NULL) {
				current->freq = leaf.at(index)->value;
				current->symbol = leaf.at(index)->key;
				current->left = NULL;
				current->right = NULL;
				head = current;
				tail = head;
				sizeTree++;
				index++;
			}
			else {
				current->freq = leaf.at(index)->value;
				current->symbol = leaf.at(index)->key;
				current->left = NULL;
				current->right = NULL;
				tail->next = current;
				tail = current;
				sizeTree++;
				index++;
			}
		}
		while (leaf.get_size() != 1) {
			Elem* current = new Elem;
			current->freq = leaf.at(0)->value + leaf.at(1)->value;
			current->symbol = '\0';
			current->left = at(0);
			current->left->parents = current;
			current->right = at(1);
			current->right->parents = current;
			sizeTree++;
			if (leaf.get_size() >= 3) {
				push_front(current);
				current->next = at(3);
				current->left->next = NULL;
				current->right->next = NULL;
				sorting();
			}
			leaf.pop_front();
			leaf.pop_front();
			leaf.push_back(current->symbol, current->freq);
			leaf.sort();
			root = current;
		}
	}

	void coding() {
		RBtree<char, string> tab;
		code(root);
		Table(root, tab);
		cout << "Code table:" << endl;
		tab.print();
		for (int i = 0; i < oridginalString.length(); i++) {
			codingString = codingString + tab.find(oridginalString[i])->value;
		}
		cout << "Ecoded string:\n" << codingString << endl;
	}
	void decoding() {
		int index = 0;
		Elem* current = root;
		while (index != codingString.length()) {
			if (current->left != NULL) {
				if (codingString[index] == '0') {
					current = current->left;
					index++;
				}
				else {
					current = current->right;
					index++;
				}
			}
			if (current->left == NULL) {
				decodingString = decodingString + current->symbol;
				current = root;
			}

		}
		cout << "Decoded string:\n" << decodingString << endl;
	}
	void printTree() {
		if (root == NULL)
			cout << "Map is empty\n" << endl;
		else
			printHelp(root);
	}
	void printaAll() {
		cout << "\nFrequency table:" << endl;
		map.print();
		HuffmanTree(map);
		coding();
		decoding();
		cout << "Compression ratio:\n" << compressionRatio(decodingString, codingString) << endl;
	}

};
