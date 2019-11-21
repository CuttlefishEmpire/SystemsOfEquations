#include "SystemsOfEquations.hpp"
#include "CalcFiles/CalcRunner.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

SystemsOfEquations::SystemsOfEquations(){
    cout << "For help, please enter the word 'large.'" << endl;
    string plshelp = "";
    cin >> plshelp;
    if(plshelp=="large"||plshelp=="verybig"||plshelp=="aaahhhhhhhh"){
        this->help();
    }
    cout << "How many equations would you like?" << endl;
    int inp = 0;
    cin >> inp;
    this->numOfEqs = inp;
    this->equations = {};
    this->eqsUnparsed = {};
    this->varsUsed = {};
    for(int i = 0; i < inp; i++){
        equations.push_back({""});
        varsUsed.push_back("");
    }
    this->debug = fstream("debug.txt", fstream::out);
    debug << "Empty parsed equations vector created with size " << equations.size() << "." << endl;
    for(int i = 0; i < inp; i++){
        string input = "";
        cout << "Please enter equation number " << i+1 << "." << endl;
        getline(cin, input);
        eqsUnparsed.push_back(input);
    }
    debug << "Empty unparsed equations vector created with size " << eqsUnparsed.size() << "." << endl;
    debug << "Iterating through and displaying unparsed equations." << endl;
    for(int i = 0; i < eqsUnparsed.size(); i++){
        debug << "Equation at index " << i << ": " << eqsUnparsed.at(i) << endl;
    }
}

void SystemsOfEquations::parseEquations(){
    debug << "Parsing equations." << endl;
    for(string str:eqsUnparsed){
        string toAdd = "";
        for(int i = 0; i < str.size(); i++){
        }
    }
}

void SystemsOfEquations::help(){
    cout << "This program does not support exponents on its variables; namely, no tying \"x^2,\" though \"2^2\" is fine." << endl;
    cout << "It does, however, support functions (sin, cos, etc)., but not derivatives." << endl;
    cout << "For a full list of supported operations, please enter 's.'" << endl;
    string s = "";
    cin >> s;
    if(s=="s"){
        cout << "Supported functions: +\n-\n*\n/\n^\nlog\nln\nsin\ncos\ntan\narcsin\narccos\narctan\n" << endl;
        cout << "csc\nsec\ncot\narccsc\narcsec\narccot\nsinh\ncosh\ntanh\ncsch\nsech\ncoth\n" << endl;
    }
}