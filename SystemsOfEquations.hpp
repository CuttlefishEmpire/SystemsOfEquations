#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class SystemsOfEquations{
public:
	SystemsOfEquations(int);
private:
	vector<vector<string>> equations;
	int numOfEqs;
};
