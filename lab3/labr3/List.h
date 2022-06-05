#pragma once
#include <string>
#include <iostream>
#include "Read.h"

const int notAvailablePrice = INT_MAX;

using namespace std;

class List
{
private:
    struct Node
    {
        string name;
        Node* next;
    };
    Node* head;
    Node* tail;
public:
    List()
    {
        head = tail = NULL;
    }

    void add(string name)
    {
        if (head == NULL)
        {
            Node* buffer = new Node;
            buffer->name = name;
            buffer->next = NULL;
            head = tail = buffer;
        }
        else
        {
            Node* buffer = head;
            Node* prev = head;
            while (buffer != NULL)
            {
                prev = buffer;
                buffer = buffer->next;
            }
            buffer = new Node;
            buffer->name = name;
            buffer->next = NULL;
            prev->next = buffer;
            tail = buffer;
        }
    }
    bool check(string text)
    {
        Node* buffer = head;
        bool i = false;
        while (buffer != NULL)
        {
            if (buffer->name == text)
            {
                i = true;
                break;
            }
            buffer = buffer->next;
        }
        return i;
    }
    void print()
    {
        Node* buffer = head;
        while (buffer != NULL)
        {
            cout << buffer->name << endl;
            buffer = buffer->next;
        }
    }
    Node* stringToList(string text)
    {
        int i = 0;
        string line = "";
        while (i != text.length())
        {
            while (text[i] != ';')
            {

                if (text[i] <= 90 && text[i] >= 60 || text[i] <= 122 && text[i] >= 97 || text[i] == '-')
                {

                    line += text[i];
                }
                if (text[i] == '\n')
                {
                    line = "";
                }
                i++;
                if (i == text.length())
                {
                    break;
                }
            }
            if (i == text.length())
            {
                break;
            }
            i++;
            if (line != "NA" && line != "")
            {
                if (!check(line))
                    add(line);
            }
            line = "";
        }
        Node* buffer = head;
        return buffer;
    }
    int** Matrix(string text)
    {
        int i = 0;
        int** array = new int* [0];
        array = new int* [maxIndex() + 1];
        for (int count = 0; count <= maxIndex(); count++)
            array[count] = new int[maxIndex()]; 
        for (int count_row = 0; count_row <= maxIndex(); count_row++)
            for (int count_column = 0; count_column <= maxIndex(); count_column++)
            {
                if (count_row == count_column)
                {
                    array[count_row][count_column] = 0;
                }
                else array[count_row][count_column] = notAvailablePrice;

            }
        i = 0;
        string line = "";
        string city_one = "";
        int index1 = 0;
        string city_two = "";
        int index2 = 0;
        int length1 = 0;
        int length2 = 0;
        while (1)
        {
            while (text[i] != ';')
            {
                if (text[i] <= 90 && text[i] >= 60 || text[i] <= 122 && text[i] >= 97 || text[i] == '-')
                {
                    line += text[i];
                }
                if (text[i] >= 48 && text[i] <= 57)
                {
                    line += text[i];
                }
                if (text[i] == '\n')
                {
                    break;
                }
                i++;
                if (i == text.length())
                {
                    break;
                }
            }
            if (city_one == "")
            {
                city_one = line;
                index1 = index(city_one);
                line = "";
            }
            else if (city_two == "")
            {
                city_two = line;
                index2 = index(city_two);
                line = "";
            }
            if (line != city_one && line != city_two && line != "NA" && line != "")
            {
                if (length1 == 0)
                {
                    length1 = stoi(line);
                }
                else
                {
                    length2 = stoi(line);
                }
                line = "";
            }
            if (line == "NA")
            {
                if (length1 == 0)
                    length1 = notAvailablePrice;
                else
                    length2 = notAvailablePrice;
                line = "";
            }
            if (length1 != 0 && length2 != 0 && index1 != -1 && index2 != -1)
            {
                array[index1][index2] = length1;
                array[index2][index1] = length2;
                length1 = length2 = 0;
                index1 = index2 = -1;
                city_one = city_two = "";


            }
            i++;
            if (i >= text.length())
                break;

        }
        return array;
    }
    string find(int index)
    {
        Node* buffer = head;
        int i = 0;
        while (buffer != NULL)
        {
            if (i == index)
            {
                break;
            }
            else {
                buffer = buffer->next;
                i++;
            }
        }
        if (buffer != NULL)
            return buffer->name;
    }
    void printMatrix(int** arrayNew)
    {
        for (int i = 0; i <= maxIndex(); i++)
        {
            for (int j = 0; j <= maxIndex(); j++)
            {
                if (arrayNew[i][j] != notAvailablePrice)
                    cout << arrayNew[i][j] << " ";
                else cout << "N/A ";
            }
            cout << endl;
        }
        cout << endl;
    }
    int index(string text)
    {
        Node* buffer = head;
        int i = 0;
        while (buffer != NULL)
        {
            if (buffer->name == text)
            {
                break;
            }
            buffer = buffer->next;
            i++;
        }
        return i;
    }
    int maxIndex()
    {
        Node* buffer = head;
        int i = 0;
        while (buffer != NULL)
        {
            buffer = buffer->next;
            i++;
        }
        return i - 1;
    }

};