#ifndef MAVOR_FITTING_FUNCTION_H
#define MAVOR_FITTING_FUNCTION_H

#include <map>
#include <iostream>

typedef double(*FuncPointer)(const double &, const int);
typedef std::pair<std::string, FuncPointer> FitFunction;

extern FitFunction chebyshev;
extern FitFunction cosine;
extern FitFunction exponential;
extern FitFunction inverse_exponential;
extern FitFunction inverse_log_power;
extern FitFunction inverse_power;
extern FitFunction inverse_sqrt_log_power;
extern FitFunction inverse_sqrt_power;
extern FitFunction legendre;
extern FitFunction log_power;
extern FitFunction power;
extern FitFunction sine_cosine;
extern FitFunction sine;
extern FitFunction sqrt_log_power;
extern FitFunction sqrt_power;

extern std::map<int, FitFunction> fitting_functions;

#endif