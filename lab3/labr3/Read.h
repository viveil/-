#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string readFile()
{
    string text = "";
    string newText;
    ifstream creat;
    char ch;
    creat.open("data.txt");

    while (!creat.eof()) {
        creat.get(ch);

        text += ch;
    }
    creat.close();
    newText = text.substr(0, text.length() - 1);
    return newText;
}