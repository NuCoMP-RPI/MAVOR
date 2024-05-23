#include "fitting_function.hpp"

#include "chebychev.hpp"
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

std::map<int, std::pair<std::string, FuncPointer>> fitting_functions = {
    {0, {"Chebychev", eval_chebychev_order}},
    {1, {"cosine", eval_cosine_order}},
    {2, {"exponential", eval_exponential_order}},
    {3, {"inverse_exponential", eval_inverse_exponential_order}},
    {4, {"inverse_log_power", eval_inverse_log_power_order}},
    {5, {"inverse_power", eval_inverse_power_order}},
    {6, {"inverse_sqrt_log_power", eval_inverse_sqrt_log_power_order}},
    {7, {"inverse_sqrt_power", eval_inverse_sqrt_power_order}},
    {8, {"legendre", eval_legendre_order}},
    {9, {"log_power", eval_log_power_order}},
    {10, {"power", eval_power_order}},
    {11, {"sine_cosine", eval_sine_cosine_order}},
    {12, {"sine", eval_sine_order}},
    {13, {"sqrt_log_power", eval_sqrt_log_power_order}},
    {14, {"sqrt_power", eval_sqrt_power_order}},
};