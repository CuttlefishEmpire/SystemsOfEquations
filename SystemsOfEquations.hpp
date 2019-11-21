#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class SystemsOfEquations{
public:
	SystemsOfEquations();
	void parseEquations();
private:
	vector<vector<string>> equations;
	vector<string> eqsUnparsed;
	int numOfEqs;
	fstream debug;
};
