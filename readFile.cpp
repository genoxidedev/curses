#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

extern int main(int argc, char *argv[]) {

    fstream saveFile(argv[1], ios_base::in);

    int a;
    int i = 0;
	vector<int> savedVars;

    for(i != a; saveFile >> a; i++)									// Tbh I didnt expect this to work on first try at all but it works :)!
        savedVars.insert(savedVars.begin() + i, i+1, a);			// Add values to vector

    return savedVars[atoi(argv[2])];								// Ability to return only wanted integer

}