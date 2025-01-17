#ifndef MAVOR_PREDEFINED_COEFF_EVALUATIONS_H
#define MAVOR_PREDEFINED_COEFF_EVALUATIONS_H

#include <map>
#include <vector>
#include <string>
#include <iostream>

/// @brief Pointer to a function that evaluates basis functions at a given x value up to a specified order.
/// The function takes a double value and an integer order as inputs and returns a vector of doubles.
/// Order indexing starts at 0, so a n value of 4 will yield a vector of length 5.
/// @param x The value at which the basis functions are evaluated.
/// @param n The maximum order up to which the basis functions are evaluated.
/// @return std::vector<double>(n+1) containing the evaluated basis functions up to order n, in ascending order.
typedef std::vector<double>(*EvalBasisFuncPointer)(double const &, int const &);

/// @brief Enum class representing the different types of basis functions available for evaluation.
enum class BasisFunction {
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

/// @struct EvaluationFunction
/// @brief Associates a basis function with its evaluation function pointer.
///
/// This structure contains information about the type of basis function 
/// and a function pointer to the corresponding evaluation method.
///
/// @var EvaluationFunction::basis_function
/// The type of basis function being evaluated, specified as a `BasisFunction` enum.
///
/// @var EvaluationFunction::eval_basis_func_pointer
/// A pointer to the function that evaluates the basis function for given inputs.
struct EvaluationFunction {
    BasisFunction basis_function;
    EvalBasisFuncPointer eval_basis_func_pointer;
};

/// @brief Typedef for a map associating a string key with an EvaluationFunction.
///
/// The key is a string representing the name of the basis function, and the value
/// is an EvaluationFunction structure containing details about the function and its evaluation.
typedef std::map<std::string, EvaluationFunction> EvaluationFunctionMap;

/// @brief Global map of available evaluation functions.
///
/// This map associates basis function names (as strings) with their corresponding
/// EvaluationFunction structures, allowing dynamic lookup and usage of evaluation routines.
extern const EvaluationFunctionMap evaluation_functions;

#endif 
