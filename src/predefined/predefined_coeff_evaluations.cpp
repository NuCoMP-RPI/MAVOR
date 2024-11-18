#include "predefined_coeff_evaluations.hpp"

#include "coeff_chebyshev.hpp"
#include "coeff_cosine.hpp"
#include "coeff_exponential.hpp"
#include "coeff_inverse_exponential.hpp"
#include "coeff_inverse_log_power.hpp"
#include "coeff_inverse_power.hpp"
#include "coeff_inverse_sqrt_log_power.hpp"
#include "coeff_inverse_sqrt_power.hpp"
#include "coeff_legendre.hpp"
#include "coeff_log_power.hpp"
#include "coeff_power.hpp"
#include "coeff_sine_cosine.hpp"
#include "coeff_sine.hpp"
#include "coeff_sqrt_log_power.hpp"
#include "coeff_sqrt_power.hpp"

const EvaluationFunction chebyshevEvalFunc = {
    BasisFunction::Chebyshev,
    &eval_chebyshev_orders
};

const EvaluationFunction cosineEvalFunc = {
    BasisFunction::Cosine,
    &eval_cosine_orders
};

const EvaluationFunction exponentialEvalFunc = {
    BasisFunction::Exponential,
    &eval_exponential_orders
};

const EvaluationFunction inverseExponentialEvalFunc = {
    BasisFunction::InverseExponential,
    &eval_inverse_exponential_orders
};

const EvaluationFunction inverseLogPowerEvalFunc = {
    BasisFunction::InverseLogPower,
    &eval_inverse_log_power_orders
};

const EvaluationFunction inversePowerEvalFunc = {
    BasisFunction::InversePower,
    &eval_inverse_power_orders
};

const EvaluationFunction inverseSqrtLogPowerEvalFunc = {
    BasisFunction::InverseSqrtLogPower,
    &eval_inverse_sqrt_log_power_orders
};

const EvaluationFunction inverseSqrtPowerEvalFunc = {
    BasisFunction::InverseSqrtPower,
    &eval_inverse_sqrt_power_orders
};

const EvaluationFunction legendreEvalFunc = {
    BasisFunction::Legendre,
    &eval_legendre_orders
};

const EvaluationFunction logPowerEvalFunc = {
    BasisFunction::LogPower,
    &eval_log_power_orders
};

const EvaluationFunction powerEvalFunc = {
    BasisFunction::Power,
    &eval_power_orders
};

const EvaluationFunction sineCosineEvalFunc = {
    BasisFunction::SineCosine,
    &eval_sine_cosine_orders
};

const EvaluationFunction sineEvalFunc = {
    BasisFunction::Sine,
    &eval_sine_orders
};

const EvaluationFunction sqrtLogPowerEvalFunc = {
    BasisFunction::SqrtLogPower,
    &eval_sqrt_log_power_orders
};

const EvaluationFunction sqrtPowerEvalFunc = {
    BasisFunction::SqrtPower,
    &eval_sqrt_power_orders
};

const EvaluationFunctionMap evaluation_functions = {
    {"Chebyshev", chebyshevEvalFunc},
    {"Cosine", cosineEvalFunc},
    {"Exponential", exponentialEvalFunc},
    {"InverseExponential", inverseExponentialEvalFunc},
    {"InverseLogPower", inverseLogPowerEvalFunc},
    {"InversePower", inversePowerEvalFunc},
    {"InverseSqrtLogPower", inverseSqrtLogPowerEvalFunc},
    {"InverseSqrtPower", inverseSqrtPowerEvalFunc},
    {"Legendre", legendreEvalFunc},
    {"LogPower", logPowerEvalFunc},
    {"Power", powerEvalFunc},
    {"SineCosine", sineCosineEvalFunc},
    {"Sine", sineEvalFunc},
    {"SqrtLogPower", sqrtLogPowerEvalFunc},
    {"SqrtPower", sqrtPowerEvalFunc},
};