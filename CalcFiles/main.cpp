#include "Expressions/ExpressionModule.hpp"
#include "Parsing/TokenParser.hpp"
#include "Parsing/ExpressionBuilder.hpp"
#include <iostream>

using namespace std;

double getAnswer(string input)
{
	Expression expression = buildExpressionFromPostfix(infixToPostfix(parse(input))));
	return evaluate(expression);
}

int main(int, char**)
{
	while(true)
	{
		string input;
		cout << "Enter an expression to evaluate:" << endl;
		getline(cin, input);
		if(input == "quit")
		{
			break;
		}
		std::cout << getAnswer(input) << endl;
	}
}
