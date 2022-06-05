#pragma once
#include<iostream>
using namespace std;
template<typename T>
class List
{
private:
	class Node {
	public:
		Node(T data = T(), Node* Next = NULL)
		{
			this->data = data;
			this->Next = Next;
		}
		Node* Next;
		T data;
	};
	Node* head;
	Node* tail;
	int Size;

public:
	List(Node* head = NULL, Node* tail = NULL, int Size = 0) :head(head), tail(tail), Size(Size) {}
	~List()
	{
		if (head != NULL)
		{
			this->clear();
		}
	}
	void push_back(T obj) 
	{
		if (head != NULL)
		{
			this->tail->Next = new Node(obj);
			tail = tail->Next;
		}
		else {
			this->head = new Node(obj);
			this->tail = this->head;
		}
		Size++;
	}

	void insert(T obj, size_t k) 
	{
		if (k >= 0 && this->Size > k)
		{
			if (this->head != NULL)
			{
				if (k == 0)
					this->push_front(obj);
				else
					if (k == this->Size - 1)
						this->push_back(obj);
					else
					{
						Node* current = new Node;
						Node* current1 = head;
						for (int i = 0; i < k - 1; i++)
						{
							current1 = current1->Next;
						}
						current->data = obj;
						current->Next = current1->Next;
						current1->Next = current;
						Size++;
					}
			}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}

	T at(size_t k) { 
		if (this->head != NULL && k >= 0 && k <= this->Size - 1)
		{
			if (k == 0)
				return this->head->data;
			else
				if (k == this->Size - 1)
					return this->tail->data;
				else
				{
					Node* current = head;
					for (int i = 0; i < k; i++)
					{
						current = current->Next;
					}
					return current->data;
				}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}

	void remove(int k) {  
		if (head != NULL && k >= 0 && k <= Size - 1)
		{
			if (k == 0) this->pop_front();
			else
				if (k == this->Size - 1) this->pop_back();
				else
					if (k != 0)
					{
						Node* current = head;
						for (int i = 0; i < k - 1; i++) //go to the pre element
						{
							current = current->Next;
						}

						Node* current1 = current->Next;
						current->Next = current->Next->Next;
						delete current1;
						Size--;
					}
		}
		else
		{
			throw std::out_of_range("out_of_range");
		}
	}

	size_t get_size() {  
		return Size;
	}

	void clear() 
	{
		if (head != NULL)
		{
			Node* current = head;
			while (head != NULL)
			{
				current = current->Next;
				delete head;
				head = current;
			}
			Size = 0;
		}
	}

};