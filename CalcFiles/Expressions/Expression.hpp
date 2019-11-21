#pragma once

#include "../Functions/Function.hpp"
#include <vector>

class Expression
{
    public:
        Function function;
        double value;
        std::vector<Expression *> arguments;

        Expression();
        Expression(Function function);
        Expression(double value);
};