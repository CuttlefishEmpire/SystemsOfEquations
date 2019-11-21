#include "ExpressionModule.hpp"
#include <cmath>

double evaluate(Expression & expression)
{
    Evaluator evaluator = buildEvaluator(expression.function);
    return evaluator(expression);
}

Evaluator buildEvaluator(Function func)
{
    switch (func)
    {
        case Function::Add:
            return [](Expression & toEvaluate)
            {
                return evaluate(*toEvaluate.arguments[0]) + evaluate(*toEvaluate.arguments[1]);
            };
        case Function::Cosecant:
            return [](Expression & toEvaluate)
            {
                return 1 / std::sin(evaluate(*toEvaluate.arguments[0]));
            };
        case Function::Cosine:
            return [](Expression & toEvaluate)
            {
                return std::cos(evaluate(*toEvaluate.arguments[0]));
            };
        case Function::Cotangent:
            return [](Expression & toEvaluate)
            {
                return 1 / std::tan(evaluate(*toEvaluate.arguments[0]));
            };
        case Function::Divide:
            return [](Expression & toEvaluate)
            {
                return evaluate(*toEvaluate.arguments[0]) / evaluate(*toEvaluate.arguments[1]);
            };
        case Function::Exponent:
            return [](Expression & toEvaluate)
            {
                return std::pow(evaluate(*toEvaluate.arguments[0]), evaluate(*toEvaluate.arguments[1]));
            };
        case Function::Identity:
            return [](Expression & toEvaluate)
            {
                return toEvaluate.value;
            };
        case Function::Log:
            return [](Expression & toEvaluate)
            {
                return std::log(evaluate(*toEvaluate.arguments[1])) / std::log(evaluate(*toEvaluate.arguments[0]));
            };
        case Function::Multiply:
            return [](Expression & toEvaluate)
            {
                return evaluate(*toEvaluate.arguments[0]) * evaluate(*toEvaluate.arguments[1]);
            };
        case Function::NaturalLogarithm:
            return [](Expression & toEvaluate)
            {
                return std::log(evaluate(*toEvaluate.arguments[0]));
            };
        case Function::Secant:
            return [](Expression & toEvaluate)
            {
                return 1 / std::cos(evaluate(*toEvaluate.arguments[0]));
            };
        case Function::Sine:
            return [](Expression & toEvaluate)
            {
                return std::sin(evaluate(*toEvaluate.arguments[0]));
            };
        case Function::Subtract:
            return [](Expression & toEvaluate)
            {
                return evaluate(*toEvaluate.arguments[0]) - evaluate(*toEvaluate.arguments[1]);
            };
        case Function::Tangent:
            return [](Expression & toEvaluate)
            {
                return std::tan(evaluate(*toEvaluate.arguments[0]));
            };
        case Function::HyperSine:
        	return [](Expression & toEvaluate)
        			{
        		return std::sinh(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::HyperCosine:
        	return [](Expression & toEvaluate)
        			{
        		return std::cosh(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::HyperTangent:
        	return [](Expression & toEvaluate)
        			{
        		return std::tanh(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::HyperCosecant:
        	return [](Expression & toEvaluate)
        			{
        		return 1/sinh(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::HyperSecant:
        	return [](Expression & toEvaluate)
        			{
        		return 1/cosh(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::HyperCotangent:
        	return [](Expression & toEvaluate)
        			{
        		return 1/tanh(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::Arcsine:
        	return [](Expression & toEvaluate)
        			{
        		return asin(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::Arccosine:
        	return [](Expression & toEvaluate)
        			{
        		return acos(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::Arctangent:
        	return [](Expression & toEvaluate)
        			{
        		return atan(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::Arccosecant:
        	return [](Expression & toEvaluate)
        			{
        		return 1/asin(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::Arcsecant:
        	return [](Expression & toEvaluate)
        			{
        		return 1/acos(evaluate(*toEvaluate.arguments[0]));
        			};
        case Function::Arccotangent:
        	return [](Expression & toEvaluate)
        			{
        		return 1/atan(evaluate(*toEvaluate.arguments[0]));
        			};
        default:
            break;
    }
    return [](Expression & toEvaluate)
    {
        return 69.69;
    };
}
