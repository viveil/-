#include <iostream>
#include "RBTree.h"

using namespace std;


int main() {
	Map <int, float> map;
	map.insert(55, 7.5);
	map.insert(40, 1.2);
	map.insert(65, 1);
	map.insert(60, 3);
	map.insert(75, 78);
	map.insert(57, 98.1);
	map.printTree();
	cout << "Clear the tree." << endl;
	cout << "Print result: " << endl;
	map.clear();
	map.printTree();
	return 0;
}
