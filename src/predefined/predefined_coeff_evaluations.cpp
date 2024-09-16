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

// ==========================================
// Function Definitions
// ==========================================

// ==========================================
// Chebyshev

const EvaluationFunction chebyshevNaiveFunction = {
    FittingType::Chebyshev, 
    EvaluationMethod::Naive, 
    &naive_chebyshev, 
};

const EvaluationFunction chebyshevDirectRecurrenceCustomFunction = {
    FittingType::Chebyshev, 
    EvaluationMethod::DirectRecurrenceCustom, 
    &direct_recurrence_chebyshev_custom, 
};

const EvaluationFunction chebyshevDirectRecurrenceGeneralFunction = {
    FittingType::Chebyshev, 
    EvaluationMethod::DirectRecurrenceGeneral, 
    &direct_recurrence_chebyshev_general, 
};

const EvaluationFunction chebyshevClenshawCustomFunction = {
    FittingType::Chebyshev, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_chebyshev_custom, 
};

const EvaluationFunction chebyshevClenshawGeneralFunction = {
    FittingType::Chebyshev, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_chebyshev_general, 
};

// ==========================================
// Cosine

const EvaluationFunction cosineNaiveFunction = {
    FittingType::Cosine, 
    EvaluationMethod::Naive, 
    &naive_cosine, 
};

const EvaluationFunction cosineImprovedFunction = {
    FittingType::Cosine, 
    EvaluationMethod::Improved, 
    &improved_cosine, 
};

// ==========================================
// Exponential

const EvaluationFunction exponentialNaiveFunction = {
    FittingType::Exponential, 
    EvaluationMethod::Naive, 
    &naive_exponential, 
};

const EvaluationFunction exponentialHornerCustomFunction = {
    FittingType::Exponential, 
    EvaluationMethod::HornerCustom, 
    &horner_exponential_custom, 
};

const EvaluationFunction exponentialHornerGeneralFunction = {
    FittingType::Exponential, 
    EvaluationMethod::HornerGeneral, 
    &horner_exponential_general, 
};

const EvaluationFunction exponentialClenshawCustomFunction = {
    FittingType::Exponential, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_exponential_custom, 
};

const EvaluationFunction exponentialClenshawGeneralFunction = {
    FittingType::Exponential, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_exponential_general, 
};

// ==========================================
// Inverse Exponential

const EvaluationFunction inverseExponentialNaiveFunction = {
    FittingType::InverseExponential, 
    EvaluationMethod::Naive, 
    &naive_inverse_exponential, 
};

const EvaluationFunction inverseExponentialHornerCustomFunction = {
    FittingType::InverseExponential, 
    EvaluationMethod::HornerCustom, 
    &horner_inverse_exponential_custom, 
};

const EvaluationFunction inverseExponentialHornerGeneralFunction = {
    FittingType::InverseExponential, 
    EvaluationMethod::HornerGeneral, 
    &horner_inverse_exponential_general, 
};

const EvaluationFunction inverseExponentialClenshawCustomFunction = {
    FittingType::InverseExponential, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_inverse_exponential_custom, 
};

const EvaluationFunction inverseExponentialClenshawGeneralFunction = {
    FittingType::InverseExponential, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_inverse_exponential_general, 
};

// ==========================================
// Inverse Log Power

const EvaluationFunction inverseLogPowerNaiveFunction = {
    FittingType::InverseExponential, 
    EvaluationMethod::Naive, 
    &naive_inverse_log_power, 
};

const EvaluationFunction inverseLogPowerHornerCustomFunction = {
    FittingType::InverseExponential, 
    EvaluationMethod::HornerCustom, 
    &horner_inverse_exponential_custom, 
};

const EvaluationFunction inverseLogPowerHornerGeneralFunction = {
    FittingType::InverseExponential, 
    EvaluationMethod::HornerGeneral, 
    &horner_inverse_exponential_general, 
};

const EvaluationFunction inverseLogPowerClenshawCustomFunction = {
    FittingType::InverseExponential, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_inverse_exponential_custom, 
};

const EvaluationFunction inverseLogPowerClenshawGeneralFunction = {
    FittingType::InverseExponential, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_inverse_exponential_general, 
};

// ==========================================
// Inverse Power

const EvaluationFunction inversePowerNaiveFunction = {
    FittingType::InversePower, 
    EvaluationMethod::Naive, 
    &naive_inverse_power, 
};

const EvaluationFunction inversePowerHornerCustomFunction = {
    FittingType::InversePower, 
    EvaluationMethod::HornerCustom, 
    &horner_inverse_power_custom, 
};

const EvaluationFunction inversePowerHornerGeneralFunction = {
    FittingType::InversePower, 
    EvaluationMethod::HornerGeneral, 
    &horner_inverse_power_general, 
};

const EvaluationFunction inversePowerClenshawCustomFunction = {
    FittingType::InversePower, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_inverse_power_custom, 
};

const EvaluationFunction inversePowerClenshawGeneralFunction = {
    FittingType::InversePower, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_inverse_power_general, 
};

// ==========================================
// Inverse SQRT Log Power

const EvaluationFunction inverseSqrtLogPowerNaiveFunction = {
    FittingType::InverseSqrtLogPower, 
    EvaluationMethod::Naive, 
    &naive_inverse_sqrt_log_power, 
};

const EvaluationFunction inverseSqrtLogPowerHornerCustomFunction = {
    FittingType::InverseSqrtLogPower, 
    EvaluationMethod::HornerCustom, 
    &horner_inverse_sqrt_log_power_custom, 
};

const EvaluationFunction inverseSqrtLogPowerHornerGeneralFunction = {
    FittingType::InverseSqrtLogPower, 
    EvaluationMethod::HornerGeneral, 
    &horner_inverse_sqrt_log_power_general, 
};

const EvaluationFunction inverseSqrtLogPowerClenshawCustomFunction = {
    FittingType::InverseSqrtLogPower, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_inverse_sqrt_log_power_custom, 
};

const EvaluationFunction inverseSqrtLogPowerClenshawGeneralFunction = {
    FittingType::InverseSqrtLogPower, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_inverse_sqrt_log_power_general, 
};

// ==========================================
// Inverse SQRT Power

const EvaluationFunction inverseSqrtPowerNaiveFunction = {
    FittingType::InverseSqrtPower, 
    EvaluationMethod::Naive, 
    &naive_inverse_sqrt_power, 
};

const EvaluationFunction inverseSqrtPowerHornerCustomFunction = {
    FittingType::InverseSqrtPower, 
    EvaluationMethod::HornerCustom, 
    &horner_inverse_sqrt_power_custom, 
};

const EvaluationFunction inverseSqrtPowerHornerGeneralFunction = {
    FittingType::InverseSqrtPower, 
    EvaluationMethod::HornerGeneral, 
    &horner_inverse_sqrt_power_general, 
};

const EvaluationFunction inverseSqrtPowerClenshawCustomFunction = {
    FittingType::InverseSqrtPower, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_inverse_sqrt_power_custom, 
};

const EvaluationFunction inverseSqrtPowerClenshawGeneralFunction = {
    FittingType::InverseSqrtPower, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_inverse_sqrt_power_general, 
};

// ==========================================
// Legendre

const EvaluationFunction legendreNaiveFunction = {
    FittingType::Legendre, 
    EvaluationMethod::Naive, 
    &naive_legendre, 
};

const EvaluationFunction legendreDirectRecurrenceCustomFunction = {
    FittingType::Legendre, 
    EvaluationMethod::DirectRecurrenceCustom, 
    &direct_recurrence_legendre_custom, 
};

const EvaluationFunction legendreDirectRecurrenceGeneralFunction = {
    FittingType::Legendre, 
    EvaluationMethod::DirectRecurrenceGeneral, 
    &direct_recurrence_legendre_general, 
};

const EvaluationFunction legendreClenshawCustomFunction = {
    FittingType::Legendre, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_legendre_custom, 
};

const EvaluationFunction legendreClenshawGeneralFunction = {
    FittingType::Legendre, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_legendre_general, 
};

// ==========================================
// Log Power

const EvaluationFunction logPowerNaiveFunction = {
    FittingType::LogPower, 
    EvaluationMethod::Naive, 
    &naive_log_power, 
};

const EvaluationFunction logPowerHornerCustomFunction = {
    FittingType::LogPower, 
    EvaluationMethod::HornerCustom, 
    &horner_log_power_custom, 
};

const EvaluationFunction logPowerHornerGeneralFunction = {
    FittingType::LogPower, 
    EvaluationMethod::HornerGeneral, 
    &horner_log_power_general, 
};

const EvaluationFunction logPowerClenshawCustomFunction = {
    FittingType::LogPower, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_log_power_custom, 
};

const EvaluationFunction logPowerClenshawGeneralFunction = {
    FittingType::LogPower, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_log_power_general, 
};

// ==========================================
// Power

const EvaluationFunction powerNaiveFunction = {
    FittingType::Power, 
    EvaluationMethod::Naive, 
    &naive_power, 
};

const EvaluationFunction powerHornerCustomFunction = {
    FittingType::Power, 
    EvaluationMethod::HornerCustom, 
    &horner_power_custom, 
};

const EvaluationFunction powerHornerGeneralFunction = {
    FittingType::Power, 
    EvaluationMethod::HornerGeneral, 
    &horner_power_general, 
};

const EvaluationFunction powerClenshawCustomFunction = {
    FittingType::Power, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_power_custom, 
};

const EvaluationFunction powerClenshawGeneralFunction = {
    FittingType::Power, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_power_general, 
};

// ==========================================
// Sine Cosine

const EvaluationFunction sineCosineNaiveFunction = {
    FittingType::SineCosine, 
    EvaluationMethod::Naive, 
    &naive_sine_cosine, 
};

const EvaluationFunction sineCosineImprovedFunction = {
    FittingType::SineCosine, 
    EvaluationMethod::Improved, 
    &improved_sine_cosine, 
};

// ==========================================
// Sine

const EvaluationFunction sineNaiveFunction = {
    FittingType::Sine, 
    EvaluationMethod::Naive, 
    &naive_sine, 
};

const EvaluationFunction sineImprovedFunction = {
    FittingType::Sine, 
    EvaluationMethod::Improved, 
    &improved_sine, 
};

// ==========================================
// Sqrt Log Power

const EvaluationFunction sqrtLogPowerNaiveFunction = {
    FittingType::SqrtLogPower, 
    EvaluationMethod::Naive, 
    &naive_sqrt_log_power, 
};

const EvaluationFunction sqrtLogPowerHornerCustomFunction = {
    FittingType::SqrtLogPower, 
    EvaluationMethod::HornerCustom, 
    &horner_sqrt_log_power_custom, 
};

const EvaluationFunction sqrtLogPowerHornerGeneralFunction = {
    FittingType::SqrtLogPower, 
    EvaluationMethod::HornerGeneral, 
    &horner_sqrt_log_power_general, 
};

const EvaluationFunction sqrtLogPowerClenshawCustomFunction = {
    FittingType::SqrtLogPower, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_sqrt_log_power_custom, 
};

const EvaluationFunction sqrtLogPowerClenshawGeneralFunction = {
    FittingType::SqrtLogPower, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_sqrt_log_power_general, 
};

// ==========================================
// Sqrt Power

const EvaluationFunction sqrtPowerNaiveFunction = {
    FittingType::SqrtPower, 
    EvaluationMethod::Naive, 
    &naive_sqrt_power, 
};

const EvaluationFunction sqrtPowerHornerCustomFunction = {
    FittingType::SqrtPower, 
    EvaluationMethod::HornerCustom, 
    &horner_sqrt_power_custom, 
};

const EvaluationFunction sqrtPowerHornerGeneralFunction = {
    FittingType::SqrtPower, 
    EvaluationMethod::HornerGeneral, 
    &horner_sqrt_power_general, 
};

const EvaluationFunction sqrtPowerClenshawCustomFunction = {
    FittingType::SqrtPower, 
    EvaluationMethod::ClenshawCustom, 
    &clenshaw_sqrt_power_custom, 
};

const EvaluationFunction sqrtPowerClenshawGeneralFunction = {
    FittingType::SqrtPower, 
    EvaluationMethod::ClenshawGeneral, 
    &clenshaw_sqrt_power_general, 
};

// ==========================================
// Evaluation Function Map Definitions
// ==========================================

const EvaluationFunctionMap chebyshevFunctionMap = {
    {"Naive", chebyshevNaiveFunction},
    {"DirectRecurrenceCustom", chebyshevDirectRecurrenceCustomFunction},
    {"DirectRecurrenceGeneral", chebyshevDirectRecurrenceGeneralFunction},
    {"ClenshawCustom", chebyshevClenshawCustomFunction},
    {"ClenshawGeneral", chebyshevClenshawGeneralFunction},
};
const EvaluationFunctionMap cosineFunctionMap = {
    {"Naive", cosineNaiveFunction},
    {"Improved", cosineImprovedFunction},
};
const EvaluationFunctionMap exponentialFunctionMap = {
    {"Naive", exponentialNaiveFunction},
    {"HornerCustom", exponentialHornerCustomFunction},
    {"HornerGeneral", exponentialHornerGeneralFunction},
    {"ClenshawCustom", exponentialClenshawCustomFunction},
    {"ClenshawGeneral", exponentialClenshawGeneralFunction},
};
const EvaluationFunctionMap inverseExponentialFunctionMap = {
    {"Naive", inverseExponentialNaiveFunction},
    {"HornerCustom", inverseExponentialHornerCustomFunction},
    {"HornerGeneral", inverseExponentialHornerGeneralFunction},
    {"ClenshawCustom", inverseExponentialClenshawCustomFunction},
    {"ClenshawGeneral", inverseExponentialClenshawGeneralFunction},
};
const EvaluationFunctionMap inverseLogPowerFunctionMap = {
    {"Naive", inverseLogPowerNaiveFunction},
    {"HornerCustom", inverseLogPowerHornerCustomFunction},
    {"HornerGeneral", inverseLogPowerHornerGeneralFunction},
    {"ClenshawCustom", inverseLogPowerClenshawCustomFunction},
    {"ClenshawGeneral", inverseLogPowerClenshawGeneralFunction},
};
const EvaluationFunctionMap inversePowerFunctionMap = {
    {"Naive", inversePowerNaiveFunction},
    {"HornerCustom", inversePowerHornerCustomFunction},
    {"HornerGeneral", inversePowerHornerGeneralFunction},
    {"ClenshawCustom", inversePowerClenshawCustomFunction},
    {"ClenshawGeneral", inversePowerClenshawGeneralFunction},
};
const EvaluationFunctionMap inverseSqrtLogPowerFunctionMap = {
    {"Naive", inverseSqrtLogPowerNaiveFunction},
    {"HornerCustom", inverseSqrtLogPowerHornerCustomFunction},
    {"HornerGeneral", inverseSqrtLogPowerHornerGeneralFunction},
    {"ClenshawCustom", inverseSqrtLogPowerClenshawCustomFunction},
    {"ClenshawGeneral", inverseSqrtLogPowerClenshawGeneralFunction},
};
const EvaluationFunctionMap inverseSqrtPowerFunctionMap = {
    {"Naive", inverseSqrtPowerNaiveFunction},
    {"HornerCustom", inverseSqrtPowerHornerCustomFunction},
    {"HornerGeneral", inverseSqrtPowerHornerGeneralFunction},
    {"ClenshawCustom", inverseSqrtPowerClenshawCustomFunction},
    {"ClenshawGeneral", inverseSqrtPowerClenshawGeneralFunction},
};
const EvaluationFunctionMap legendreFunctionMap = {
    {"Naive", legendreNaiveFunction},
    {"DirectRecurrenceCustom", legendreDirectRecurrenceCustomFunction},
    {"DirectRecurrenceGeneral", legendreDirectRecurrenceGeneralFunction},
    {"ClenshawCustom", legendreClenshawCustomFunction},
    {"ClenshawGeneral", legendreClenshawGeneralFunction},
};
const EvaluationFunctionMap logPowerFunctionMap = {
    {"Naive", logPowerNaiveFunction},
    {"HornerCustom", logPowerHornerCustomFunction},
    {"HornerGeneral", logPowerHornerGeneralFunction},
    {"ClenshawCustom", logPowerClenshawCustomFunction},
    {"ClenshawGeneral", logPowerClenshawGeneralFunction},
};
const EvaluationFunctionMap powerFunctionMap = {
    {"Naive", powerNaiveFunction},
    {"HornerCustom", powerHornerCustomFunction},
    {"HornerGeneral", powerHornerGeneralFunction},
    {"ClenshawCustom", powerClenshawCustomFunction},
    {"ClenshawGeneral", powerClenshawGeneralFunction},
};
const EvaluationFunctionMap sineCosineFunctionMap = {
    {"Naive", sineCosineNaiveFunction},
    {"Improved", sineCosineImprovedFunction},
};
const EvaluationFunctionMap sineFunctionMap = {
    {"Naive", sineNaiveFunction},
    {"Improved", sineImprovedFunction},
};
const EvaluationFunctionMap sqrtLogPowerFunctionMap = {
    {"Naive", sqrtLogPowerNaiveFunction},
    {"HornerCustom", sqrtLogPowerHornerCustomFunction},
    {"HornerGeneral", sqrtLogPowerHornerGeneralFunction},
    {"ClenshawCustom", sqrtLogPowerClenshawCustomFunction},
    {"ClenshawGeneral", sqrtLogPowerClenshawGeneralFunction},
};
const EvaluationFunctionMap sqrtPowerFunctionMap = {
    {"Naive", sqrtPowerNaiveFunction},
    {"HornerCustom", sqrtPowerHornerCustomFunction},
    {"HornerGeneral", sqrtPowerHornerGeneralFunction},
    {"ClenshawCustom", sqrtPowerClenshawCustomFunction},
    {"ClenshawGeneral", sqrtPowerClenshawGeneralFunction},
};

// ==========================================
// Evaluation Type Map Definition
// ==========================================

const EvaluationTypeMap FitEvaluationMap = {
    {"Chebyshev", chebyshevFunctionMap},
    {"Cosine", cosineFunctionMap},
    {"Exponential", exponentialFunctionMap},
    {"InverseExponential", inverseExponentialFunctionMap},
    {"InverseLogPower", inverseLogPowerFunctionMap},
    {"InversePower", inversePowerFunctionMap},
    {"InverseSqrtLogPower", inverseSqrtLogPowerFunctionMap},
    {"InverseSqrtPower", inverseSqrtPowerFunctionMap},
    {"Legendre", legendreFunctionMap},
    {"LogPower", logPowerFunctionMap},
    {"Power", powerFunctionMap},
    {"SineCosine", sineCosineFunctionMap},
    {"Sine", sineFunctionMap},
    {"SqrtLogPower", sqrtLogPowerFunctionMap},
    {"SqrtPower", sqrtPowerFunctionMap},
};


// ==========================================
// Predefined Evaluation types 
// ==========================================

const PredefinedEvaluationsMap NaiveEvaluationsMap = {
    {"Chebyshev", chebyshevNaiveFunction},
    {"Cosine", cosineNaiveFunction},
    {"Exponential", exponentialNaiveFunction},
    {"InverseExponential", inverseExponentialNaiveFunction},
    {"InverseLogPower", inverseLogPowerNaiveFunction},
    {"InversePower", inversePowerNaiveFunction},
    {"InverseSqrtLogPower", inverseSqrtLogPowerNaiveFunction},
    {"InverseSqrtPower", inverseSqrtPowerNaiveFunction},
    {"Legendre", legendreNaiveFunction},
    {"LogPower", logPowerNaiveFunction},
    {"Power", powerNaiveFunction},
    {"SineCosine", sineCosineNaiveFunction},
    {"Sine", sineNaiveFunction},
    {"SqrtLogPower", sqrtLogPowerNaiveFunction},
    {"SqrtPower", sqrtPowerNaiveFunction},
};

// NOTE: This needs to be filled in later with the fastest evaluation methods
const PredefinedEvaluationsMap OptimalEvaluationsMap = {
    {"Chebyshev", chebyshevNaiveFunction},
    {"Cosine", cosineNaiveFunction},
    {"Exponential", exponentialNaiveFunction},
    {"InverseExponential", inverseExponentialNaiveFunction},
    {"InverseLogPower", inverseLogPowerNaiveFunction},
    {"InversePower", inversePowerNaiveFunction},
    {"InverseSqrtLogPower", inverseSqrtLogPowerNaiveFunction},
    {"InverseSqrtPower", inverseSqrtPowerNaiveFunction},
    {"Legendre", legendreNaiveFunction},
    {"LogPower", logPowerNaiveFunction},
    {"Power", powerNaiveFunction},
    {"SineCosine", sineCosineNaiveFunction},
    {"Sine", sineNaiveFunction},
    {"SqrtLogPower", sqrtLogPowerNaiveFunction},
    {"SqrtPower", sqrtPowerNaiveFunction},
};