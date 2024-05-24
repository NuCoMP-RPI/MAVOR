#ifndef MAVOR_FITTING_FUNCTION_H
#define MAVOR_FITTING_FUNCTION_H

#include <map>
#include <iostream>

typedef double(*FuncPointer)(const double &, const int);
typedef std::pair<std::string, FuncPointer> FitFunction;

extern std::map<int, FitFunction> fitting_functions;

#endif