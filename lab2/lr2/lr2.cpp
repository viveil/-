#include <iostream>
#include"HuffmanAlgo.h"
using namespace std;

int main()
{
    string one = "it is test string";
    cout << one;
    AlgoHuffman firstrCod = AlgoHuffman(one);
    firstrCod.printaAll();
    cout << endl;
    string two = "Hana wa sakuragi, hito wa bushi. (Japanese proverb)";
    cout << two;
    AlgoHuffman secondCod = AlgoHuffman(two);
    secondCod.printaAll();
    cout << endl;
    string three = "HelLOO* heeelloo oOo";
    cout << three;
    AlgoHuffman thirdCod = AlgoHuffman(three);
    thirdCod.printaAll();
}
