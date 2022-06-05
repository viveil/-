#include "FloydWarshallAlgorithm.h"

int main()
{
    string text = readFile();
    cout << text << endl << endl;
    cout << "We will find the best price flight from Vladivostok to Saint-Petersburg \n";
    algorithmFloyd(text, "Vladivostok", "Saint-Petersburg");
}
