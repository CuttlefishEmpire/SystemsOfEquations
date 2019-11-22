#include "Expressions/ExpressionModule.hpp"
#include "Parsing/TokenParser.hpp"
#include "Parsing/ExpressionBuilder.hpp"
#include <iostream>

using namespace std;

double getAnswer(string & input, CalculatorContext & context)
{
    Expression expression = buildExpressionFromPostfix(infixToPostfix(parse(input)));
    double answer = evaluate(expression, context);
    context.setValue("ans", answer);
    return answer;
}

int main(int, char**)
{
    CalculatorContext context = CalculatorContext();
    while (true)
    {
        string input;
        cout << "Enter an expression to evaluate:" << endl;
        getline(cin, input);
        if (input == "clear")
        {
            std::cout << "\x1B[2J\x1B[H";
            continue;
        }
        else if (input == "quit")
        {
            break;
        }
        std::cout << getAnswer(input, context) << endl;
    }
}
