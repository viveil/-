#pragma once
#include <iostream>
#include <stdexcept> 
using namespace std;

template <typename T>

class List {

private:

	class Node {
	public:
		T data; 
		Node* next;
	};
	Node* head; 
	Node* tail; 

public:
	List(T data) {

		Node* temp = new Node; 
		temp->data = data;
		temp->next = tail;
		head = temp;
		tail = temp;
	}

	List() {
		head = tail = NULL;
		Node* temp = new Node; 
		temp->next = NULL;
		temp->data = NULL;
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
	Node* get_head() {
		return head;
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

	
	void push_back(T data) {
		Node* temp = new Node;
		if (isEmpty() == 1) {  
			temp->data = data;
			temp->next = NULL;
			head = temp;
			tail = temp;
		}
		else { 
			temp->data = data;
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
			cout << temp->data << " ";
			temp = temp->next;
		}
	}

};

