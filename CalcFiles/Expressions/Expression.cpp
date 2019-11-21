#include "Expression.hpp"

Expression::Expression()
{

}

Expression::Expression(Function function)
{
    this->function = function;
}

Expression::Expression(double value)
{
    this->function = Function::Identity;
    this->value = value;
}