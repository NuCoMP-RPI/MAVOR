#ifndef MAVOR_CLENSHAW_H
#define MAVOR_CLENSHAW_H

#include <vector>
#include <functional>

double clenshaw(double const & x, 
                std::vector<double> const & coeffs, 
                const std::function<double(double, int)>& alpha_rec, 
                const std::function<double(double, int)>& beta_rec, 
                const std::function<double(double, int)>& phi);

#endif