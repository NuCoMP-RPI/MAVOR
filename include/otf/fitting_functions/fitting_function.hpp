#ifndef MAVOR_FITTING_FUNCTION_H
#define MAVOR_FITTING_FUNCTION_H

#include <map>
#include <iostream>

typedef double(*FuncPointer)(const double &, const int);

extern std::map<int, std::pair<std::string, FuncPointer>> fitting_functions;

#endif