#ifndef MAVOR_CONSTANTS_H
#define MAVOR_CONSTANTS_H

constexpr double PI{3.14159265358979323846264338327950288};
constexpr double boltz = 0.00008617385;
constexpr double ref_temp_ev = 0.0253;
constexpr double ref_temp_k = ref_temp_ev/boltz;

constexpr double beta_max = 50;
constexpr double sct_cutoff = 1.9219477278e-98;  // Based off the sabmin value in thermr | sabmin = exp(-225) | Found line 1609 and 1628 of thermr.f90
constexpr double alpha_min = 1e-10;
constexpr double e_min = 1e-5;

constexpr int beta_integration_scheme = 2;
constexpr int beta_interpolation_scheme = 2;
constexpr int alpha_integration_scheme = 2;
constexpr int alpha_interpolation_scheme = 2;

#endif