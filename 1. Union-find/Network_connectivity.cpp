/*
Statement of the problem:
Network connectivity: Given a social network containing N members and a log file containing M timestamps at which times pairs of members formed friendships, design an algorithm to determine the earliest time at which all members are connected (i.e., every member is a friend
of a friend of a friend ... of a friend). Assume that the log file is sorted by timestamp and that friendship is an equivalence relation. The running time of your algorithm should be M log N or better and use extra space proportional to N.
*/

/*
Solution: 
Implement weighted quick union find with path compression. Add a new member function connected() that checks if the network is connected.  
*/

#include "WQUFPC.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("Network_connectivity_timestamps.txt");
    int n;
    fin >> n;
    
	WQUFPC comp_connected(n);
	
    int t, a, b, m = 0;
    while ( (!comp_connected.connected()) && (fin >> t >> a >> b) ) {
        ++m;
		comp_connected.link(a-1, b-1);		
    }
	
    if (comp_connected.connected())
        cout << "Network is connected after " << m << " time steps." << endl;
    else
        cout << "Network is not connected." << endl;

}