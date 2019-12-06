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
	void printMatrix(vector<vector<string>>);
	void printMatrix(vector<vector<double>>);
private:
	vector<vector<string>> equations;
	vector<string> eqsUnparsed;
	vector<vector<char>> singEqUnparsed;
	vector<vector<string>> mat;
	vector<vector<double>> matNum;
	vector<char> varsUsed;
	int numOfEqs;
	fstream debug;
	mainCalc* parse;
};
