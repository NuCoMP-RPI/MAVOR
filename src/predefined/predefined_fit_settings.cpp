#include "predefined_fit_settings.hpp"

#include "basis_chebyshev.hpp"
#include "basis_cosine.hpp"
#include "basis_exponential.hpp"
#include "basis_inverse_exponential.hpp"
#include "basis_inverse_log_power.hpp"
#include "basis_inverse_power.hpp"
#include "basis_inverse_sqrt_log_power.hpp"
#include "basis_inverse_sqrt_power.hpp"
#include "basis_legendre.hpp"
#include "basis_log_power.hpp"
#include "basis_power.hpp"
#include "basis_sine_cosine.hpp"
#include "basis_sine.hpp"
#include "basis_sqrt_log_power.hpp"
#include "basis_sqrt_power.hpp"

BasisFunction chebyshev = {"Chebyshev", eval_chebyshev_order};
BasisFunction cosine = {"cosine", eval_cosine_order};
BasisFunction exponential = {"exponential", eval_exponential_order};
BasisFunction inverse_exponential = {"inverse_exponential", eval_inverse_exponential_order};
BasisFunction inverse_log_power = {"inverse_log_power", eval_inverse_log_power_order};
BasisFunction inverse_power = {"inverse_power", eval_inverse_power_order};
BasisFunction inverse_sqrt_log_power = {"inverse_sqrt_log_power", eval_inverse_sqrt_log_power_order};
BasisFunction inverse_sqrt_power = {"inverse_sqrt_power", eval_inverse_sqrt_power_order};
BasisFunction legendre = {"legendre", eval_legendre_order};
BasisFunction log_power = {"log_power", eval_log_power_order};
BasisFunction power = {"power", eval_power_order};
BasisFunction sine_cosine = {"sine_cosine", eval_sine_cosine_order};
BasisFunction sine = {"sine", eval_sine_order};
BasisFunction sqrt_log_power = {"sqrt_log_power", eval_sqrt_log_power_order};
BasisFunction sqrt_power = {"sqrt_power", eval_sqrt_power_order};

BasisFunctionSettings chebyshev_settings = {true, -1, 1, chebyshev};
BasisFunctionSettings cosine_settings = {true, 0, 1, cosine};
BasisFunctionSettings scaled_exponential_settings = {true, -1, 1, exponential};
BasisFunctionSettings scaled_inverse_exponential_settings = {true, -1, 1, inverse_exponential};
BasisFunctionSettings inverse_log_power_settings = {false, 1, 2, inverse_log_power};
BasisFunctionSettings scaled_inverse_log_power_settings = {true, 2, 3, inverse_log_power};
BasisFunctionSettings inverse_power_settings = {false, -1, 1, inverse_power};
BasisFunctionSettings scaled_inverse_power_settings = {true, -1, 1, inverse_power};
BasisFunctionSettings inverse_sqrt_log_power_settings = {false, 2, 3, inverse_sqrt_log_power};
BasisFunctionSettings scaled_inverse_sqrt_log_power_settings = {true, 2, 3, inverse_sqrt_log_power};
BasisFunctionSettings inverse_sqrt_power_settings = {false, 1, 2, inverse_sqrt_power};
BasisFunctionSettings scaled_inverse_sqrt_power_settings = {true, 1, 2, inverse_sqrt_power};
BasisFunctionSettings legendre_settings = {true, -1, 1, legendre};
BasisFunctionSettings log_power_settings = {false, 1, 2, log_power};
BasisFunctionSettings scaled_log_power_settings = {true, 1, 2, log_power};
BasisFunctionSettings power_settings = {false, -1, 1, power};
BasisFunctionSettings scaled_power_settings = {true, -1, 1, power};
BasisFunctionSettings sine_cosine_settings = {true, 0, 1, sine_cosine};
BasisFunctionSettings sine_settings = {true, 0, 1, sine};
BasisFunctionSettings sqrt_log_power_settings = {false, 1, 2, sqrt_log_power};
BasisFunctionSettings scaled_sqrt_log_power_settings = {true, 1, 2, sqrt_log_power};
BasisFunctionSettings sqrt_power_settings = {false, 0, 1, sqrt_power};
BasisFunctionSettings scaled_sqrt_power_settings = {true, 0, 1, sqrt_power};

FittingFunction chebyshev_fit_settings = {"Chebyshev", chebyshev_settings};
FittingFunction cosine_fit_settings = {"Cosine", cosine_settings};
FittingFunction scaled_exponential_fit_settings = {"Scaled Exponential", scaled_exponential_settings};
FittingFunction scaled_inverse_exponential_fit_settings = {"Scaled Inverse Exponential", scaled_inverse_exponential_settings};
FittingFunction inverse_log_power_fit_settings = {"Inverse Log Power", inverse_log_power_settings};
FittingFunction scaled_inverse_log_power_fit_settings = {"Scaled Inverse Log Power", scaled_inverse_log_power_settings};
FittingFunction inverse_power_fit_settings = {"Inverse Power", inverse_power_settings};
FittingFunction scaled_inverse_power_fit_settings = {"Scaled Inverse Power", scaled_inverse_power_settings};
FittingFunction inverse_sqrt_log_power_fit_settings = {"Inverse Square Root Log Power", inverse_sqrt_log_power_settings};
FittingFunction scaled_inverse_sqrt_log_power_fit_settings = {"Scaled Inverse Square Root Log Power", scaled_inverse_sqrt_log_power_settings};
FittingFunction inverse_sqrt_power_fit_settings = {"Scaled Inverse Square Root Power", inverse_sqrt_power_settings};
FittingFunction scaled_inverse_sqrt_power_fit_settings = {"Scaled Inverse Square Root Power", scaled_inverse_sqrt_power_settings};
FittingFunction legendre_fit_settings = {"Legendre", legendre_settings};
FittingFunction log_power_fit_settings = {"Log Power", log_power_settings};
FittingFunction scaled_log_power_fit_settings = {"Scaled Log Power", scaled_log_power_settings};
FittingFunction power_fit_settings = {"Power", power_settings};
FittingFunction scaled_power_fit_settings = {"Scaled Power", scaled_power_settings};
FittingFunction sine_cosine_fit_settings = {"Sine Cosine", sine_cosine_settings};
FittingFunction sine_fit_settings = {"Sine", sine_settings};
FittingFunction sqrt_log_power_fit_settings = {"Square Root Power", sqrt_log_power_settings};
FittingFunction scaled_sqrt_log_power_fit_settings = {"Scaled Square Root Power", scaled_sqrt_log_power_settings};
FittingFunction sqrt_power_fit_settings = {"Square Root Power", sqrt_power_settings};
FittingFunction scaled_sqrt_power_fit_settings = {"Scaled Square Root Power", scaled_sqrt_power_settings};

BasisFunctionMap basis_functions = {
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

FittingFunctionMap fitting_functions = {
    {0, chebyshev_fit_settings},
    {1, cosine_fit_settings},
    {2, scaled_exponential_fit_settings},
    {3, scaled_inverse_exponential_fit_settings},
    {4, inverse_log_power_fit_settings},
    {5, scaled_inverse_log_power_fit_settings},
    {6, inverse_power_fit_settings},
    {7, scaled_inverse_power_fit_settings},
    {8, inverse_sqrt_log_power_fit_settings},
    {9, scaled_inverse_sqrt_log_power_fit_settings},
    {10, inverse_sqrt_power_fit_settings},
    {11, scaled_inverse_sqrt_power_fit_settings},
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

Fit default_fit = {scaled_power_fit_settings, 5};

// Decided by maximum mean r-squared value
AlphaFit best_BeinBeO_alpha_fit = {scaled_inverse_sqrt_power_fit_settings, 4};
AlphaFit best_CinSiC_alpha_fit = {scaled_inverse_sqrt_log_power_fit_settings, 4};
AlphaFit best_crystalline_graphite_alpha_fit = {scaled_exponential_fit_settings, 12};
AlphaFit best_DinD2O_alpha_fit = {scaled_exponential_fit_settings, 6};
AlphaFit best_HinCH2_alpha_fit = {inverse_power_fit_settings, 2};
AlphaFit best_HinH2O_alpha_fit = {scaled_exponential_fit_settings, 8};
AlphaFit best_HinIcelh_alpha_fit = {inverse_power_fit_settings, 2};
AlphaFit best_HinYH2_alpha_fit = {inverse_log_power_fit_settings, 3};
AlphaFit best_HinZrH_alpha_fit = {inverse_log_power_fit_settings, 3};
AlphaFit best_NinUN_alpha_fit = {scaled_inverse_log_power_fit_settings, 4};
AlphaFit best_OinBeO_alpha_fit = {scaled_inverse_sqrt_power_fit_settings, 4};
AlphaFit best_OinD2O_alpha_fit = {scaled_exponential_fit_settings, 6};
AlphaFit best_OinIcelh_alpha_fit = {scaled_exponential_fit_settings, 5};
AlphaFit best_OinUO2_alpha_fit = {legendre_fit_settings, 5};
AlphaFit best_reactor_graphite_10P_alpha_fit = {power_fit_settings, 15};
AlphaFit best_reactor_graphite_30P_alpha_fit = {scaled_inverse_sqrt_power_fit_settings, 7};
AlphaFit best_SiinSiC_alpha_fit = {inverse_sqrt_log_power_fit_settings, 3};
AlphaFit best_UinUN_alpha_fit = {scaled_exponential_fit_settings, 14};
AlphaFit best_UinUO2_alpha_fit = {scaled_exponential_fit_settings, 14};
AlphaFit best_YinYH2_alpha_fit = {scaled_power_fit_settings, 15};
AlphaFit best_ZrinZrH_alpha_fit = {inverse_log_power_fit_settings, 3};

// Decided by eyeballing mean r-squared plots
AlphaFit optimal_BeinBeO_alpha_fit = {scaled_inverse_sqrt_power_fit_settings, 4};
AlphaFit optimal_CinSiC_alpha_fit = {scaled_inverse_sqrt_log_power_fit_settings, 4};
AlphaFit optimal_crystalline_graphite_alpha_fit = {scaled_exponential_fit_settings, 6};
AlphaFit optimal_DinD2O_alpha_fit = {scaled_exponential_fit_settings, 6};
AlphaFit optimal_HinCH2_alpha_fit = {inverse_power_fit_settings, 2};
AlphaFit optimal_HinH2O_alpha_fit = {scaled_exponential_fit_settings, 8};
AlphaFit optimal_HinIcelh_alpha_fit = {inverse_power_fit_settings, 2};
AlphaFit optimal_HinYH2_alpha_fit = {inverse_log_power_fit_settings, 3};
AlphaFit optimal_HinZrH_alpha_fit = {inverse_log_power_fit_settings, 3};
AlphaFit optimal_NinUN_alpha_fit = {scaled_inverse_log_power_fit_settings, 4};
AlphaFit optimal_OinBeO_alpha_fit = {scaled_inverse_sqrt_power_fit_settings, 4};
AlphaFit optimal_OinD2O_alpha_fit = {scaled_exponential_fit_settings, 6};
AlphaFit optimal_OinIcelh_alpha_fit = {scaled_exponential_fit_settings, 5};
AlphaFit optimal_OinUO2_alpha_fit = {legendre_fit_settings, 5};
AlphaFit optimal_reactor_graphite_10P_alpha_fit = {scaled_exponential_fit_settings, 6};
AlphaFit optimal_reactor_graphite_30P_alpha_fit = {scaled_inverse_sqrt_power_fit_settings, 7};
AlphaFit optimal_SiinSiC_alpha_fit = {inverse_sqrt_log_power_fit_settings, 3};
AlphaFit optimal_UinUN_alpha_fit = {scaled_log_power_fit_settings, 8};
AlphaFit optimal_UinUO2_alpha_fit = {scaled_log_power_fit_settings, 8};
AlphaFit optimal_YinYH2_alpha_fit = {scaled_inverse_exponential_fit_settings, 8};
AlphaFit optimal_ZrinZrH_alpha_fit = {inverse_log_power_fit_settings, 3};

// Decided by maximum mean r-squared value
BetaFit best_BeinBeO_beta_fit = {scaled_inverse_exponential_fit_settings, 15};
BetaFit best_CinSiC_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_crystalline_graphite_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_DinD2O_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_HinCH2_beta_fit = {scaled_exponential_fit_settings, 15};
BetaFit best_HinH2O_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_HinIcelh_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_HinYH2_beta_fit = {inverse_power_fit_settings, 14};
BetaFit best_HinZrH_beta_fit = {legendre_fit_settings, 15};
BetaFit best_NinUN_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_OinBeO_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_OinD2O_beta_fit = {legendre_fit_settings, 15};
BetaFit best_OinIcelh_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_OinUO2_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_reactor_graphite_10P_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_reactor_graphite_30P_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_SiinSiC_beta_fit = {chebyshev_fit_settings, 15};
BetaFit best_UinUN_beta_fit = {inverse_power_fit_settings, 15};
BetaFit best_UinUO2_beta_fit = {scaled_inverse_exponential_fit_settings, 15};
BetaFit best_YinYH2_beta_fit = {inverse_power_fit_settings, 14};
BetaFit best_ZrinZrH_beta_fit = {legendre_fit_settings, 15};

// Decided by eyeballing mean r-squared plots
BetaFit optimal_BeinBeO_beta_fit = {inverse_power_fit_settings, 5};
BetaFit optimal_CinSiC_beta_fit = {scaled_inverse_exponential_fit_settings, 5};
BetaFit optimal_crystalline_graphite_beta_fit = {scaled_inverse_exponential_fit_settings, 5};
BetaFit optimal_DinD2O_beta_fit = {scaled_power_fit_settings, 5};
BetaFit optimal_HinCH2_beta_fit = {scaled_inverse_exponential_fit_settings, 5};
BetaFit optimal_HinH2O_beta_fit = {scaled_inverse_exponential_fit_settings, 6};
BetaFit optimal_HinIcelh_beta_fit = {scaled_inverse_exponential_fit_settings, 6};
BetaFit optimal_HinYH2_beta_fit = {scaled_inverse_exponential_fit_settings, 5};
BetaFit optimal_HinZrH_beta_fit = {inverse_power_fit_settings, 5};
BetaFit optimal_NinUN_beta_fit = {scaled_inverse_exponential_fit_settings, 5};
BetaFit optimal_OinBeO_beta_fit = {scaled_inverse_log_power_fit_settings, 5};
BetaFit optimal_OinD2O_beta_fit = {scaled_log_power_fit_settings, 5};
BetaFit optimal_OinIcelh_beta_fit = {scaled_inverse_exponential_fit_settings, 4};
BetaFit optimal_OinUO2_beta_fit = {inverse_power_fit_settings, 4};
BetaFit optimal_reactor_graphite_10P_beta_fit = {inverse_log_power_fit_settings, 4};
BetaFit optimal_reactor_graphite_30P_beta_fit = {scaled_inverse_exponential_fit_settings, 4};
BetaFit optimal_SiinSiC_beta_fit = {inverse_power_fit_settings, 4};
BetaFit optimal_UinUN_beta_fit = {inverse_power_fit_settings, 3};
BetaFit optimal_UinUO2_beta_fit = {inverse_power_fit_settings, 4};
BetaFit optimal_YinYH2_beta_fit = {inverse_sqrt_log_power_fit_settings, 4};
BetaFit optimal_ZrinZrH_beta_fit = {inverse_power_fit_settings, 5};

// Decided by maximum mean r-squared value
XSFit best_BeinBeO_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_CinSiC_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_crystalline_graphite_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_DinD2O_xs_fit = {scaled_power_fit_settings, 15};
XSFit best_HinCH2_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_HinH2O_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_HinIcelh_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_HinYH2_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_HinZrH_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_NinUN_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_OinBeO_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_OinD2O_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_OinIcelh_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_OinUO2_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_reactor_graphite_10P_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_reactor_graphite_30P_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_SiinSiC_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_UinUN_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_UinUO2_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_YinYH2_xs_fit = {chebyshev_fit_settings, 15};
XSFit best_ZrinZrH_xs_fit = {chebyshev_fit_settings, 15};

// Decided by eyeballing mean r-squared plots
XSFit optimal_BeinBeO_xs_fit = {chebyshev_fit_settings, 5};
XSFit optimal_CinSiC_xs_fit = {scaled_inverse_sqrt_power_fit_settings, 6};
XSFit optimal_crystalline_graphite_xs_fit = {sqrt_power_fit_settings, 4};
XSFit optimal_DinD2O_xs_fit = {scaled_exponential_fit_settings, 5};
XSFit optimal_HinCH2_xs_fit = {chebyshev_fit_settings, 3};
XSFit optimal_HinH2O_xs_fit = {scaled_power_fit_settings, 3};
XSFit optimal_HinIcelh_xs_fit = {legendre_fit_settings, 3};
XSFit optimal_HinYH2_xs_fit = {scaled_inverse_log_power_fit_settings, 3};
XSFit optimal_HinZrH_xs_fit = {scaled_inverse_sqrt_power_fit_settings, 3};
XSFit optimal_NinUN_xs_fit = {sqrt_power_fit_settings, 3};
XSFit optimal_OinBeO_xs_fit = {scaled_log_power_fit_settings, 3};
XSFit optimal_OinD2O_xs_fit = {legendre_fit_settings, 4};
XSFit optimal_OinIcelh_xs_fit = {chebyshev_fit_settings, 3};
XSFit optimal_OinUO2_xs_fit = {sqrt_power_fit_settings, 4};
XSFit optimal_reactor_graphite_10P_xs_fit = {scaled_inverse_log_power_fit_settings, 4};
XSFit optimal_reactor_graphite_30P_xs_fit = {scaled_inverse_log_power_fit_settings, 4};
XSFit optimal_SiinSiC_xs_fit = {sqrt_power_fit_settings, 3};
XSFit optimal_UinUN_xs_fit = {chebyshev_fit_settings, 3};
XSFit optimal_UinUO2_xs_fit = {log_power_fit_settings, 3};
XSFit optimal_YinYH2_xs_fit = {log_power_fit_settings, 3};
XSFit optimal_ZrinZrH_xs_fit = {sqrt_power_fit_settings, 3};

MaterialFit best_BeinBeO_fits = {best_BeinBeO_xs_fit, best_BeinBeO_beta_fit, best_BeinBeO_alpha_fit};
MaterialFit best_CinSiC_fits = {best_CinSiC_xs_fit, best_CinSiC_beta_fit, best_CinSiC_alpha_fit};
MaterialFit best_crystalline_graphite_fits = {best_crystalline_graphite_xs_fit, best_crystalline_graphite_beta_fit, best_crystalline_graphite_alpha_fit};
MaterialFit best_DinD2O_fits = {best_DinD2O_xs_fit, best_DinD2O_beta_fit, best_DinD2O_alpha_fit};
MaterialFit best_HinCH2_fits = {best_HinCH2_xs_fit, best_HinCH2_beta_fit, best_HinCH2_alpha_fit};
MaterialFit best_HinH2O_fits = {best_HinH2O_xs_fit, best_HinH2O_beta_fit, best_HinH2O_alpha_fit};
MaterialFit best_HinIcelh_fits = {best_HinIcelh_xs_fit, best_HinIcelh_beta_fit, best_HinIcelh_alpha_fit};
MaterialFit best_HinYH2_fits = {best_HinYH2_xs_fit, best_HinYH2_beta_fit, best_HinYH2_alpha_fit};
MaterialFit best_HinZrH_fits = {best_HinZrH_xs_fit, best_HinZrH_beta_fit, best_HinZrH_alpha_fit};
MaterialFit best_NinUN_fits = {best_NinUN_xs_fit, best_NinUN_beta_fit, best_NinUN_alpha_fit};
MaterialFit best_OinBeO_fits = {best_OinBeO_xs_fit, best_OinBeO_beta_fit, best_OinBeO_alpha_fit};
MaterialFit best_OinD2O_fits = {best_OinD2O_xs_fit, best_OinD2O_beta_fit, best_OinD2O_alpha_fit};
MaterialFit best_OinIcelh_fits = {best_OinIcelh_xs_fit, best_OinIcelh_beta_fit, best_OinIcelh_alpha_fit};
MaterialFit best_OinUO2_fits = {best_OinUO2_xs_fit, best_OinUO2_beta_fit, best_OinUO2_alpha_fit};
MaterialFit best_reactor_graphite_10P_fits = {best_reactor_graphite_10P_xs_fit, best_reactor_graphite_10P_beta_fit, best_reactor_graphite_10P_alpha_fit};
MaterialFit best_reactor_graphite_30P_fits = {best_reactor_graphite_30P_xs_fit, best_reactor_graphite_30P_beta_fit, best_reactor_graphite_30P_alpha_fit};
MaterialFit best_SiinSiC_fits = {best_SiinSiC_xs_fit, best_SiinSiC_beta_fit, best_SiinSiC_alpha_fit};
MaterialFit best_UinUN_fits = {best_UinUN_xs_fit, best_UinUN_beta_fit, best_UinUN_alpha_fit};
MaterialFit best_UinUO2_fits = {best_UinUO2_xs_fit, best_UinUO2_beta_fit, best_UinUO2_alpha_fit};
MaterialFit best_YinYH2_fits = {best_YinYH2_xs_fit, best_YinYH2_beta_fit, best_YinYH2_alpha_fit};
MaterialFit best_ZrinZrH_fits = {best_ZrinZrH_xs_fit, best_ZrinZrH_beta_fit, best_ZrinZrH_alpha_fit};

MaterialFit optimal_BeinBeO_fits = {optimal_BeinBeO_xs_fit, optimal_BeinBeO_beta_fit, optimal_BeinBeO_alpha_fit};
MaterialFit optimal_CinSiC_fits = {optimal_CinSiC_xs_fit, optimal_CinSiC_beta_fit, optimal_CinSiC_alpha_fit};
MaterialFit optimal_crystalline_graphite_fits = {optimal_crystalline_graphite_xs_fit, optimal_crystalline_graphite_beta_fit, optimal_crystalline_graphite_alpha_fit};
MaterialFit optimal_DinD2O_fits = {optimal_DinD2O_xs_fit, optimal_DinD2O_beta_fit, optimal_DinD2O_alpha_fit};
MaterialFit optimal_HinCH2_fits = {optimal_HinCH2_xs_fit, optimal_HinCH2_beta_fit, optimal_HinCH2_alpha_fit};
MaterialFit optimal_HinH2O_fits = {optimal_HinH2O_xs_fit, optimal_HinH2O_beta_fit, optimal_HinH2O_alpha_fit};
MaterialFit optimal_HinIcelh_fits = {optimal_HinIcelh_xs_fit, optimal_HinIcelh_beta_fit, optimal_HinIcelh_alpha_fit};
MaterialFit optimal_HinYH2_fits = {optimal_HinYH2_xs_fit, optimal_HinYH2_beta_fit, optimal_HinYH2_alpha_fit};
MaterialFit optimal_HinZrH_fits = {optimal_HinZrH_xs_fit, optimal_HinZrH_beta_fit, optimal_HinZrH_alpha_fit};
MaterialFit optimal_NinUN_fits = {optimal_NinUN_xs_fit, optimal_NinUN_beta_fit, optimal_NinUN_alpha_fit};
MaterialFit optimal_OinBeO_fits = {optimal_OinBeO_xs_fit, optimal_OinBeO_beta_fit, optimal_OinBeO_alpha_fit};
MaterialFit optimal_OinD2O_fits = {optimal_OinD2O_xs_fit, optimal_OinD2O_beta_fit, optimal_OinD2O_alpha_fit};
MaterialFit optimal_OinIcelh_fits = {optimal_OinIcelh_xs_fit, optimal_OinIcelh_beta_fit, optimal_OinIcelh_alpha_fit};
MaterialFit optimal_OinUO2_fits = {optimal_OinUO2_xs_fit, optimal_OinUO2_beta_fit, optimal_OinUO2_alpha_fit};
MaterialFit optimal_reactor_graphite_10P_fits = {optimal_reactor_graphite_10P_xs_fit, optimal_reactor_graphite_10P_beta_fit, optimal_reactor_graphite_10P_alpha_fit};
MaterialFit optimal_reactor_graphite_30P_fits = {optimal_reactor_graphite_30P_xs_fit, optimal_reactor_graphite_30P_beta_fit, optimal_reactor_graphite_30P_alpha_fit};
MaterialFit optimal_SiinSiC_fits = {optimal_SiinSiC_xs_fit, optimal_SiinSiC_beta_fit, optimal_SiinSiC_alpha_fit};
MaterialFit optimal_UinUN_fits = {optimal_UinUN_xs_fit, optimal_UinUN_beta_fit, optimal_UinUN_alpha_fit};
MaterialFit optimal_UinUO2_fits = {optimal_UinUO2_xs_fit, optimal_UinUO2_beta_fit, optimal_UinUO2_alpha_fit};
MaterialFit optimal_YinYH2_fits = {optimal_YinYH2_xs_fit, optimal_YinYH2_beta_fit, optimal_YinYH2_alpha_fit};
MaterialFit optimal_ZrinZrH_fits = {optimal_ZrinZrH_xs_fit, optimal_ZrinZrH_beta_fit, optimal_ZrinZrH_alpha_fit};

PredefinedMaterialFitsMap best_material_fits = {
  {27, {"BeinBeO", best_BeinBeO_fits}},
  {44, {"CinSiC", best_CinSiC_fits}},
  {30, {"crystalline_graphite", best_crystalline_graphite_fits}},
  {11, {"DinD2O", best_DinD2O_fits}},
  {37, {"HinCH2", best_HinCH2_fits}},
  {1, {"HinH2O", best_HinH2O_fits}},
  {10, {"HinIcelh", best_HinIcelh_fits}},
  {5, {"HinYH2", best_HinYH2_fits}},
  {7, {"HinZrH", best_HinZrH_fits}},
  {71, {"NinUN", best_NinUN_fits}},
  {46, {"OinBeO", best_OinBeO_fits}},
  {51, {"OinD2O", best_OinD2O_fits}},
  {50, {"OinIcelh", best_OinIcelh_fits}},
  {75, {"OinUO2", best_OinUO2_fits}},
  {31, {"reactor_graphite_10P", best_reactor_graphite_10P_fits}},
  {32, {"reactor_graphite_30P", best_reactor_graphite_30P_fits}},
  {43, {"SiinSiC", best_SiinSiC_fits}},
  {72, {"UinUN", best_UinUN_fits}},
  {48, {"UinUO2", best_UinUO2_fits}},
  {55, {"YinYH2", best_YinYH2_fits}},
  {58, {"ZrinZrH", best_ZrinZrH_fits}},
};

PredefinedMaterialFitsMap optimal_material_fits = {
  {27, {"BeinBeO", optimal_BeinBeO_fits}},
  {44, {"CinSiC", optimal_CinSiC_fits}},
  {30, {"crystalline_graphite", optimal_crystalline_graphite_fits}},
  {11, {"DinD2O", optimal_DinD2O_fits}},
  {37, {"HinCH2", optimal_HinCH2_fits}},
  {1, {"HinH2O", optimal_HinH2O_fits}},
  {10, {"HinIcelh", optimal_HinIcelh_fits}},
  {5, {"HinYH2", optimal_HinYH2_fits}},
  {7, {"HinZrH", optimal_HinZrH_fits}},
  {71, {"NinUN", optimal_NinUN_fits}},
  {46, {"OinBeO", optimal_OinBeO_fits}},
  {51, {"OinD2O", optimal_OinD2O_fits}},
  {50, {"OinIcelh", optimal_OinIcelh_fits}},
  {75, {"OinUO2", optimal_OinUO2_fits}},
  {31, {"reactor_graphite_10P", optimal_reactor_graphite_10P_fits}},
  {32, {"reactor_graphite_30P", optimal_reactor_graphite_30P_fits}},
  {43, {"SiinSiC", optimal_SiinSiC_fits}},
  {72, {"UinUN", optimal_UinUN_fits}},
  {48, {"UinUO2", optimal_UinUO2_fits}},
  {55, {"YinYH2", optimal_YinYH2_fits}},
  {58, {"ZrinZrH", optimal_ZrinZrH_fits}},

};

PredefinedFitGroups predefined_material_fits_groups = {
  {0, best_material_fits},
  {1, optimal_material_fits}
};