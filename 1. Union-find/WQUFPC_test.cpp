#include "WQUFPC.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	WQUFPC connected_comp(5);
	connected_comp.link(1, 2);
	cout << connected_comp.connected(0, 2) << endl;
	//print(cout, connected_comp);
	connected_comp.link(2, 3);
	//print(cout, connected_comp);
	connected_comp.link(4, 0);
	cout << connected_comp.connected(3, 4) << endl;
	//print(cout, connected_comp);
	connected_comp.link(4, 3);
	cout << connected_comp.connected(0, 3) << endl;
	//print(cout, connected_comp);
	connected_comp.link(0, 2);
	//print(cout, connected_comp);

}