#ifndef MAVOR_PREDEFINED_COEFF_EVALUATIONS_H
#define MAVOR_PREDEFINED_COEFF_EVALUATIONS_H

#include <map>
#include <vector>
#include <string>
#include <iostream>

typedef std::vector<double>::const_iterator Iter;
// typedef double(*EvaluationFunctionPointer)(double const &, std::vector<double> const &);
typedef double(*EvaluationFunctionPointer)(double const &, Iter, Iter);

enum class FittingType{
    Chebyshev,
    Cosine,
    Exponential,
    InverseExponential,
    InverseLogPower,
    InversePower,
    InverseSqrtLogPower,
    InverseSqrtPower,
    Legendre,
    LogPower,
    Power,
    SineCosine,
    Sine,
    SqrtLogPower,
    SqrtPower
};

enum class EvaluationMethod{
    Naive,
    Improved,
    DirectRecurrenceCustom,
    DirectRecurrenceGeneral,
    HornerCustom,
    HornerGeneral,
    ClenshawCustom,
    ClenshawGeneral
};

struct EvaluationFunction{
    FittingType type;
    EvaluationMethod method;
    EvaluationFunctionPointer function;
};

typedef std::map<std::string, EvaluationFunction> EvaluationFunctionMap;
typedef std::map<std::string, EvaluationFunctionMap> EvaluationTypeMap;
typedef std::map<std::string, EvaluationFunction> PredefinedEvaluationsMap;

extern const EvaluationTypeMap FitEvaluationMap;
extern const PredefinedEvaluationsMap NaiveEvaluationsMap;
extern const PredefinedEvaluationsMap OptimalEvaluationsMap;

#endif 
