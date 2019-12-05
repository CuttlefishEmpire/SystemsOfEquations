#include "SystemsOfEquations.hpp"
#include "CalcFiles/mainCalc.hpp"
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
    this->mat = {};
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
    for(int i = 0; i < varsUsed.size(); i++){
    	mat.push_back({});
    }
    for(int i = 0; i < varsUsed.size(); i++){
    	mat.at(i).push_back({});
    }
    debug << "Empty unparsed equations vector created with size " << eqsUnparsed.size() << "." << endl;
    debug << "Iterating through and displaying unparsed equations." << endl;
    for(unsigned int i = 0; i < eqsUnparsed.size(); i++){
        debug << "Equation at index " << i << ": " << eqsUnparsed.at(i) << endl;
    }
    this->parseEquations();
}

void SystemsOfEquations::parseEquations(){
	mainCalc* parse = new mainCalc();
    debug << "\nParsing equations.\n" << endl;
    debug << "Iterating through unparsed equations vector." << endl;
    int eqOn = 0;
    for(string str:eqsUnparsed){
        debug << "\nUnparsed equation being processed: " << str <<"\n"<< endl;
        string toAdd = "";
        debug << "Searching for negative signs." << endl;
        for(int i = 0; i < str.size(); i++){
        	if(str.at(i)!=' '){
        		if(str.at(i)=='-'&&i!=0&&str.at(i-2)!='='){
        			toAdd+="+-";
                    debug << "Found negative sign at index " << i << ", replacing with +-." << endl;
        		}else{
        			toAdd+=str.at(i);
        		}
        	}
        }
        debug << "Equation without spaces and isolated subtraction signs: " << toAdd << endl;
        debug << "\nSearching for coefficient-less variables." << endl;
        for(int i = 0; i < toAdd.size(); i++){
        	for(int j = 0; j < varsUsed.size(); j++){
        		if(toAdd.at(i)==varsUsed.at(j)){
                    debug << "Variable " << toAdd.at(i) << " found at index " << i << "." << endl;
        			if((i!=0)&&((toAdd.at(i-1)=='+'&&toAdd.at(i)!='-')||toAdd.at(i-1)=='-')||toAdd.at(i-1)=='='){
        				toAdd.insert(i,"1");
                        i++;
                        debug << "Variable was found to be coefficient-less, so 1 has been supplied." << endl;
        			}
        		}
        	}
        }
        debug << "Equation without coefficient-less variables: " << toAdd << endl;
        int eqInd = 0;
        debug << "\nSearching for equals sign." << endl;
        for(int i = 0; i < toAdd.size(); i++){
           	if(toAdd.at(i)=='='){
          		eqInd = i;
                debug << "Equals sign found at index " << i << "." << endl;
           	}
        }
        string preEq = "";
        string postEq = "";
        for(int i = 0; i < eqInd; i++){
        	preEq+=toAdd.at(i);
        }
        debug << "Pre-equals sign equation: " << preEq << endl;
        for(int i = eqInd+1; i < toAdd.size(); i++){
        	postEq+=toAdd.at(i);
        }
        debug << "Post-equals sign equation: " << postEq << endl;
    	vector<string> stuffToAdd = {};
    	int sinceLastVar = 1;
    	int stored = 0;
        double ans = parse->returnAns(postEq);
        debug << "Making vector for coefficients." << endl;
        for(int i = 0; i < preEq.size(); i++){
        	for(int j = 0; j < varsUsed.size(); j++){
        		if(preEq.at(i)==varsUsed.at(j)){
        			debug << "Variable " << varsUsed.at(j) << " found at index " << i << "." << endl;
        			for(int k = stored; k < sinceLastVar; k++){
        				if(preEq.at(k)!='+'){
        					singEqUnparsed.at(j).push_back(preEq.at(k));
        					debug << "Character " << preEq.at(k) << " pushed to back of equation for variable " << varsUsed.at(j) << "." << endl;
        				}
        			}
        			stored = sinceLastVar;
        		}
        	}
        	sinceLastVar++;
        }
        debug << "Exited variable splitter." << endl;
        for(int i = 0; i < numOfEqs; i++){
        	debug << "Statement for variable " << varsUsed.at(i) << ": ";
        	for(int j = 0; j < singEqUnparsed.at(i).size(); j++){
        		debug << singEqUnparsed.at(i).at(j);
        		//mat.at(i).at(j).push_back(singEqUnparsed.at(i).at(j));
        	}
        	debug << endl;
        }
        vector<string> eqs = {};
        for(int i = 0; i < numOfEqs; i++){
        	eqs.push_back("");
        }
        debug << "Pre singEqUnparsed for loop" << endl;
        for(int i = 0; i < singEqUnparsed.size(); i++){
        	for(int j = 0; j < singEqUnparsed.at(i).size(); j++){
        		eqs.at(i)+=singEqUnparsed.at(i).at(j);
        	}
        }
        debug << "Pre eqs for loop" << endl;
        debug << "eqs size: " << eqs.size() << endl;
        for(int i = 0; i < eqs.size(); i++){
        	mat.at(i).at(eqOn) = eqs.at(i);
        }
        debug << "Current matrix: " << endl;
        for(int i = 0; i < mat.size(); i++){
        	for(int j = 0; j < mat.at(i).size(); j++){
        		debug << mat.at(i).at(j) << " ";
        	}
        	debug << endl;
        }
        singEqUnparsed = {};
        for(int i = 0; i < numOfEqs; i++){
        	singEqUnparsed.push_back({});
        }
        eqOn++;
    }
}

void SystemsOfEquations::help(){
    cout << "This program does not support exponents on its variables; namely, no tying \"x^2,\" though \"2^2\" is fine." << endl;
    cout << "It does, however, support functions (sin, cos, etc)., but not derivatives." << endl;
    cout << "When entering equations, please ensure that there is only one instance of each variable, where all variable terms are on the left and all constant on the right." << endl;
    cout << "For a full list of supported operations, please enter 's.'" << endl;
    string s = "";
    cin >> s;
    if(s=="s"){
        cout << "Supported functions: \n+\n-\n*\n/\n^\nlog\nln\nsin\ncos\ntan\narcsin\narccos\narctan" << endl;
        cout << "csc\nsec\ncot\narccsc\narcsec\narccot\nsinh\ncosh\ntanh\ncsch\nsech\ncoth\n" << endl;
    }
}
