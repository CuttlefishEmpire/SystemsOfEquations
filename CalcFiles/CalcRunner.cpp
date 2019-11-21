#include "Expressions/ExpressionModule.hpp"
#include "Parsing/TokenParser.hpp"
#include "Parsing/ExpressionBuilder.hpp"
#include "CalcRunner.hpp"
#include <iostream>

using namespace std;

CalcRunner::CalcRunner(string input){
    Expression expression = buildExpressionFromPostfix(infixToPostfix(parse(input)));
	runnerOutput = evaluate(expression);
}