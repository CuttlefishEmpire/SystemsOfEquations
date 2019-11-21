#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CalcFiles/CalcRunner.hpp"

using namespace std;

class SystemsOfEquations{
public:
	SystemsOfEquations();
	void parseEquations();
	void help();
private:
	vector<vector<string>> equations;
	vector<string> eqsUnparsed;
	vector<string> varsUsed;
	int numOfEqs;
	fstream debug;
};
