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
    this->mat = {};
    this->matNum = {};
    this->parse = new mainCalc();
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
    for(int i = 0; i < numOfEqs; i++){
    	mat.push_back({});
        matNum.push_back({});
    }
    for(int i = 0; i < numOfEqs; i++){
        for(int j = 0; j < numOfEqs; j++){
    	    mat.at(i).push_back({});
            matNum.at(i).push_back({});
        }
    }
    debug << "Matrix dimensions: " << mat.size() << "x" << mat.at(0).size() << endl;
    debug << "Empty unparsed equations vector created with size " << eqsUnparsed.size() << "." << endl;
    debug << "Iterating through and displaying unparsed equations." << endl;
    for(unsigned int i = 0; i < eqsUnparsed.size(); i++){
        debug << "Equation at index " << i << ": " << eqsUnparsed.at(i) << endl;
    }
    this->parseEquations();
}

void SystemsOfEquations::parseEquations(){
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
                    if(i==0){
                        debug << "Entered i is zero if statement." << endl;
                        toAdd.insert(i,"1");
                        i++;
                        debug << "Variable was found to be coefficient-less, so 1 has been supplied." << endl;
                    }else if((i!=0)&&((toAdd.at(i-1)=='+'&&toAdd.at(i)!='-')||toAdd.at(i-1)=='-')||toAdd.at(i-1)=='='){
                        debug << "Entered i is not zero if statement." << endl;
        				toAdd.insert(i,"1");
                        i++;
                        debug << "Variable was found to be coefficient-less, so 1 has been supplied." << endl;
        			}else{
                        debug << "Has coefficient, and so nothing shall be done." << endl;
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
        debug << "Matrix dimensions: " << mat.size() << "x" << mat.at(0).size() << endl;
        for(int i = 0; i < eqs.size(); i++){
        	mat.at(eqOn).at(i) = eqs.at(i);
        }
        debug << "Current matrix: " << endl;
        printMatrix(mat);
        singEqUnparsed = {};
        for(int i = 0; i < numOfEqs; i++){
        	singEqUnparsed.push_back({});
        }
        eqOn++;
    }
    debug << "Removing variables from matrix." << endl;
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat.at(i).size(); j++){
            mat.at(i).at(j) = mat.at(i).at(j).substr(0, mat.at(i).at(j).size()-1);
        }
    }
    debug << "Matrix without variables: " << endl;
    printMatrix(mat);
    debug << "Converting string matrix into a double matrix." << endl;
    for(int i = 0; i < matNum.size(); i++){
        for(int j = 0; j < matNum.at(i).size(); j++){
            matNum.at(i).at(j) = parse->returnAns(mat.at(i).at(j));
        }
    }
    debug << "Matrix converted into doubles: " << endl;
    printMatrix(matNum);
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

void SystemsOfEquations::printMatrix(vector<vector<string>> m){
    for(int i = 0; i < m.size(); i++){
       	for(int j = 0; j < m.at(i).size(); j++){
       		debug << m.at(i).at(j) << " ";
       	}
       	debug << endl;
    }
}

void SystemsOfEquations::printMatrix(vector<vector<double>> m){
    for(int i = 0; i < m.size(); i++){
       	for(int j = 0; j < m.at(i).size(); j++){
       		debug << m.at(i).at(j) << " ";
       	}
       	debug << endl;
    }
}