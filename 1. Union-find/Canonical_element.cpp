/*
Statement of the problem:
Union-find with specific canonical element. Add a method find() to the union-find data type so that find(i) returns the largest element
in the connected component containing i. The operations union(), connected(), and find() should all take logarithmic time or better.

For example, if one of the connected components is {1, 2, 6, 9}, then the find() method should return 9 for each of the four elements in
the connected components because 9 is larger 1, 2, and 6.

Solution: 
Implement the class WQUFPC_largest, which is similar to class WQUFPC with the following modifications.
Add an additional vector data member to class WQUFPC called largest[] such that largest[i] = the largest element in the tree rooted at i.
The member function find(i) will return largest[i].
          
We read the edges from Canonical_element.txt.
*/

#include "WQUFPC_largest.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("Canonical_element.txt");
    int n;
    fin >> n;
	
	WQUFPC_largest comp_connected(n);

    int a, b, M { 0 };
    while (fin >> a >> b)
		comp_connected.link(--a, --b);

    for (size_t i = 0; i != n; i++)
        cout << "Largest element for " << i + 1 << ": " 
			 << comp_connected.find(i) + 1 << endl;
}
