#include "fitting_function.hpp"

#include "chebyshev.hpp"
#include "cosine.hpp"
#include "exponential.hpp"
#include "inverse_exponential.hpp"
#include "inverse_log_power.hpp"
#include "inverse_power.hpp"
#include "inverse_sqrt_log_power.hpp"
#include "inverse_sqrt_power.hpp"
#include "legendre.hpp"
#include "log_power.hpp"
#include "power.hpp"
#include "sine_cosine.hpp"
#include "sine.hpp"
#include "sqrt_log_power.hpp"
#include "sqrt_power.hpp"

FitFunction chebyshev = {"Chebyshev", eval_chebyshev_order};
FitFunction cosine = {"cosine", eval_cosine_order};
FitFunction exponential = {"exponential", eval_exponential_order};
FitFunction inverse_exponential = {"inverse_exponential", eval_inverse_exponential_order};
FitFunction inverse_log_power = {"inverse_log_power", eval_inverse_log_power_order};
FitFunction inverse_power = {"inverse_power", eval_inverse_power_order};
FitFunction inverse_sqrt_log_power = {"inverse_sqrt_log_power", eval_inverse_sqrt_log_power_order};
FitFunction inverse_sqrt_power = {"inverse_sqrt_power", eval_inverse_sqrt_power_order};
FitFunction legendre = {"legendre", eval_legendre_order};
FitFunction log_power = {"log_power", eval_log_power_order};
FitFunction power = {"power", eval_power_order};
FitFunction sine_cosine = {"sine_cosine", eval_sine_cosine_order};
FitFunction sine = {"sine", eval_sine_order};
FitFunction sqrt_log_power = {"sqrt_log_power", eval_sqrt_log_power_order};
FitFunction sqrt_power = {"sqrt_power", eval_sqrt_power_order};

std::map<int, FitFunction> fitting_functions = {
    {0, chebyshev},
    {1, cosine},
    {2, exponential},
    {3, inverse_exponential},
    {4, inverse_log_power},
    {5, inverse_power},
    {6, inverse_sqrt_log_power},
    {7, inverse_sqrt_power},
    {8, legendre},
    {9, log_power},
    {10, power},
    {11, sine_cosine},
    {12, sine},
    {13, sqrt_log_power},
    {14, sqrt_power},
};