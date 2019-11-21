#pragma once

#include "Expression.hpp"

typedef double (* Evaluator) (Expression & toEvaluate);

double evaluate(Expression & expression);

/* Returns an Evaluator built from a specific operator or function's properties */
Evaluator buildEvaluator(Function func);