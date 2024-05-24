#include "predefined_fit_settings.hpp"
#include "fitting_function.hpp"

FitSettings chebyshev_settings = {true, -1, 1, chebyshev};
FitSettings cosine_settings = {true, 0, 1, cosine};
FitSettings exponential_settings = {false, -1, 1, exponential};
FitSettings scaled_exponential_settings = {true, -1, 1, exponential};
FitSettings inverse_exponential_settings = {false, -1, 1, inverse_exponential};
FitSettings scaled_inverse_exponential_settings = {true, -1, 1, inverse_exponential};
FitSettings inverse_log_power_settings = {false, 0, 1, inverse_log_power};
FitSettings scaled_inverse_log_power_settings = {true, 0, 1, inverse_log_power};
FitSettings inverse_power_settings = {false, -1, 1, inverse_power};
FitSettings scaled_inverse_power_settings = {true, -1, 1, inverse_power};
FitSettings inverse_sqrt_log_power_settings = {false, 0, 1, inverse_sqrt_log_power};
FitSettings scaled_inverse_sqrt_log_power_settings = {true, 0, 1, inverse_sqrt_log_power};
FitSettings legendre_settings = {true, -1, 1, legendre};
FitSettings log_power_settings = {false, 0, 1, log_power};
FitSettings scaled_log_power_settings = {true, 0, 1, log_power};
FitSettings power_settings = {false, -1, 1, power};
FitSettings scaled_power_settings = {true, -1, 1, power};
FitSettings sine_cosine_settings = {true, 0, 1, sine_cosine};
FitSettings sine_settings = {true, 0, 1, sine};
FitSettings sqrt_log_power_settings = {false, 0, 1, sqrt_log_power};
FitSettings scaled_sqrt_log_power_settings = {true, 0, 1, sqrt_log_power};
FitSettings sqrt_power_settings = {false, 0, 1, sqrt_power};
FitSettings scaled_sqrt_power_settings = {true, 0, 1, sqrt_power};

PredefinedFitSettings chebyshev_fit_settings = {"Chebyshev", chebyshev_settings};
PredefinedFitSettings cosine_fit_settings = {"Cosine", cosine_settings};
PredefinedFitSettings exponential_fit_settings = {"Exponential", exponential_settings};
PredefinedFitSettings scaled_exponential_fit_settings = {"Scaled Exponential", scaled_exponential_settings};
PredefinedFitSettings inverse_exponential_fit_settings = {"Inverse Exponential", inverse_exponential_settings};
PredefinedFitSettings scaled_inverse_exponential_fit_settings = {"Scaled Inverse Exponential", scaled_inverse_exponential_settings};
PredefinedFitSettings inverse_log_power_fit_settings = {"Inverse Log Power", inverse_log_power_settings};
PredefinedFitSettings scaled_inverse_log_power_fit_settings = {"Scaled Inverse Log Power", scaled_inverse_log_power_settings};
PredefinedFitSettings inverse_power_fit_settings = {"Inverse Power", inverse_power_settings};
PredefinedFitSettings scaled_inverse_power_fit_settings = {"Scaled Inverse Power", scaled_inverse_power_settings};
PredefinedFitSettings inverse_sqrt_log_power_fit_settings = {"Inverse Square Root Power", inverse_sqrt_log_power_settings};
PredefinedFitSettings scaled_inverse_sqrt_log_power_fit_settings = {"Scaled Inverse Square Root Power", scaled_inverse_sqrt_log_power_settings};
PredefinedFitSettings legendre_fit_settings = {"Legendre", legendre_settings};
PredefinedFitSettings log_power_fit_settings = {"Log Power", log_power_settings};
PredefinedFitSettings scaled_log_power_fit_settings = {"Scaled Log Power", scaled_log_power_settings};
PredefinedFitSettings power_fit_settings = {"Power", power_settings};
PredefinedFitSettings scaled_power_fit_settings = {"Scaled Power", scaled_power_settings};
PredefinedFitSettings sine_cosine_fit_settings = {"Sine Cosine", sine_cosine_settings};
PredefinedFitSettings sine_fit_settings = {"Sine", sine_settings};
PredefinedFitSettings sqrt_log_power_fit_settings = {"Square Root Power", sqrt_log_power_settings};
PredefinedFitSettings scaled_sqrt_log_power_fit_settings = {"Scaled Square Root Power", scaled_sqrt_log_power_settings};
PredefinedFitSettings sqrt_power_fit_settings = {"Square Root Power", sqrt_power_settings};
PredefinedFitSettings scaled_sqrt_power_fit_settings = {"Scaled Square Root Power", scaled_sqrt_power_settings};

PredefinedFitSettingsMap predefined_fit_settings = {
    {0, chebyshev_fit_settings},
    {1, cosine_fit_settings},
    {2, exponential_fit_settings},
    {3, scaled_exponential_fit_settings},
    {4, inverse_exponential_fit_settings},
    {5, scaled_inverse_exponential_fit_settings},
    {6, inverse_log_power_fit_settings},
    {7, scaled_inverse_log_power_fit_settings},
    {8, inverse_power_fit_settings},
    {9, scaled_inverse_power_fit_settings},
    {10, inverse_sqrt_log_power_fit_settings},
    {11, scaled_inverse_sqrt_log_power_fit_settings},
    {12, legendre_fit_settings},
    {13, log_power_fit_settings},
    {14, scaled_log_power_fit_settings},
    {15, power_fit_settings},
    {16, scaled_power_fit_settings},
    {17, sine_cosine_fit_settings},
    {18, sine_fit_settings},
    {19, sqrt_log_power_fit_settings},
    {20, scaled_sqrt_log_power_fit_settings},
    {21, sqrt_power_fit_settings},
    {22, scaled_sqrt_power_fit_settings}
};

MatPredefinedFitMap material_predefined_fits = {
    {27, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {44, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {30, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {11, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {37, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {1,  {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {10, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {5,  {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {7,  {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {71, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {46, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {51, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {50, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {75, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {31, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {32, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {43, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {72, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {48, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {55, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
    {58, {{scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5},
          {scaled_inverse_exponential_fit_settings, 5}}},
};
