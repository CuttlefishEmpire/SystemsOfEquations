#include "Expressions/ExpressionModule.hpp"
#include "Parsing/TokenParser.hpp"
#include "Parsing/ExpressionBuilder.hpp"
#include <iostream>

using namespace std;

class CalcRunner{
public:
    CalcRunner(string);
private:
    double runnerOutput;
};