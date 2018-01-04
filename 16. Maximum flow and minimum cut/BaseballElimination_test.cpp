#include "BaseballElimination.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	BaseballElimination be("teams12.txt");
	
	for (const string teamName : be.teams()) {
		cout << "Team " << teamName << ": " << endl;
		cout << "\t is eliminated? " << be.isEliminated(teamName) << endl;
		if (be.isEliminated(teamName)) {
			cout << "\t teams that eliminate it: ";
			for (const string s : be.certificateOfElimination(teamName))
				cout << s << " ";
		}
		cout << endl << endl;
	}
	
}