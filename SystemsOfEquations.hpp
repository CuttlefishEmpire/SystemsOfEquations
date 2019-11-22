#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CalcFiles/mainCalc.hpp"

using namespace std;

class SystemsOfEquations{
public:
	SystemsOfEquations();
	void parseEquations();
	void help();
private:
	vector<vector<string>> equations;
	vector<string> eqsUnparsed;
	vector<vector<string>> singEqUnparsed;
	vector<char> varsUsed;
	int numOfEqs;
	fstream debug;
};
