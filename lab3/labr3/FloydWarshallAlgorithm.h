#pragma once
#include "List.h"
#include <string>
#include <iostream>
#include "Read.h"
using namespace std;

string printWay(List list, int** way, int** arrayNew, string cityDep, string cityArr)
{

    int index1 = list.index(cityDep);
    int index2 = list.index(cityArr);
    string Way = "";
    if (index1 == index2)
    {
        throw invalid_argument("Incorrect way");
    }
    if (way[index1][index2] != 0)
    {
        Way += list.find(index1);
        Way += "->";
        Way += list.find(way[index1][index2] - 1);
        Way += "->";
        Way += list.find(index2);
    }
    else
    {
        Way += list.find(index1);
        Way += "->";
        Way += list.find(index2);
    }
    cout << "The cost of the flight is " << arrayNew[index1][index2] << endl;
    return Way;
}
int** algorithmFloyd(string text, string cityDep, string cityArr)
{
    List list;
    list.stringToList(text);
    int** array = list.Matrix(text);
    cout << "Adjacency matrix:" << endl;
    list.printMatrix(array);
    int** arrayNew = array;
    int** way = new int* [0];
    way = new int* [list.maxIndex() + 1];
    for (int i = 0; i <= list.maxIndex(); i++)
        way[i] = new int[list.maxIndex()];
    for (int i = 0; i <= list.maxIndex(); i++)
        for (int j = 0; j <= list.maxIndex(); j++)
            way[i][j] = 0;

    for (int k = 0; k <= list.maxIndex(); k++) {	
        for (int i = 0; i <= list.maxIndex(); i++) {
            for (int j = 0; j <= list.maxIndex(); j++) {
                if (arrayNew[i][k] != notAvailablePrice && arrayNew[k][j] != notAvailablePrice)
                {
                    if (arrayNew[i][k] + arrayNew[k][j] < arrayNew[i][j])
                    {
                        arrayNew[i][j] = arrayNew[i][k] + arrayNew[k][j];
                        way[i][j] = way[i][j] * 10 + k + 1;
                    }
                }
            }
        }
    }
    cout << "Matrix processed by Floyd Warshall's algorithm" << endl;
    list.printMatrix(arrayNew);
    cout << "The way: " << printWay(list, way, arrayNew, cityDep, cityArr);
    return arrayNew;
}