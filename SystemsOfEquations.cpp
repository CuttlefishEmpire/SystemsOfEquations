#include "SystemsOfEquations.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

SystemsOfEquations::SystemsOfEquations(){
    cout << "For help, please enter the word 'large.' Otherwise, enter something else." << endl;
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
    this->singEqUnparsed = {};
    this->varsUsed = {};
    for(int i = 0; i < inp; i++){
        equations.push_back({""});
    }
    this->debug = fstream("debug.txt", fstream::out);
    string inpFixer = "";
    getline(cin, inpFixer);
    debug << "Empty parsed equations vector created with size " << equations.size() << "." << endl;
    for(int i = 0; i < inp; i++){
        string input = "";
        cout << "Please enter equation number " << i+1 << "." << endl;
        getline(cin, input);
        eqsUnparsed.push_back(input);
    }
    cout << "What variables did you use? Please enter them with the syntax of x, y, z." << endl;
    string vars = "";
    getline(cin, vars);
    for(int i = 0; i < vars.size(); i++){
    	if(vars.at(i)!=',' && vars.at(i)!=' '){
    		varsUsed.push_back(vars.at(i));
    		singEqUnparsed.push_back({});
    	}
    }
    debug << "Empty unparsed equations vector created with size " << eqsUnparsed.size() << "." << endl;
    debug << "Iterating through and displaying unparsed equations." << endl;
    for(unsigned int i = 0; i < eqsUnparsed.size(); i++){
        debug << "Equation at index " << i << ": " << eqsUnparsed.at(i) << endl;
    }
    this->parseEquations();
}

void SystemsOfEquations::parseEquations(){
    debug << "Parsing equations." << endl;
    for(string str:eqsUnparsed){
        string toAdd = "";
        for(int i = 0; i < str.size(); i++){
        	if(str.at(i)!=' '){
        		if(str.at(i)=='-'&&i!=0){
        			toAdd+="+-";
        		}else{
        			toAdd+=str.at(i);
        		}
        	}
        }
        for(int i = 0; i < toAdd.size(); i++){
        	for(int j = 0; j < varsUsed.size(); j++){
        		if(toAdd.at(i)==varsUsed.at(j)){
        			if((i!=0)&&((toAdd.at(i-1)=='+'&&toAdd.at(i)!='-')||toAdd.at(i-1)=='-')){
        				toAdd.insert(i,"1");
        			}
        		}
        	}
        }
        int eqInd = 0;
        for(int i = 0; i < toAdd.size(); i++){
        	if(toAdd.at(i)=='='){
        		eqInd = i;
        	}
        }
        for(int i = eqInd; i < toAdd.size(); i++){

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
        cout << "Supported functions: +\n-\n*\n/\nsin\ncos\ntan\narcsin\narccos\narctan\n" << endl;
    }
}
