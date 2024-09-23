#ifndef MAVOR_CLENSHAW_H
#define MAVOR_CLENSHAW_H

#include <vector>
#include <functional>
#include <iterator> 

double clenshaw(double const & x, 
                std::vector<double> const & coeffs, 
                const std::function<double(double, int)>& alpha_rec, 
                const std::function<double(double, int)>& beta_rec, 
                const std::function<double(double, int)>& phi);

typedef std::vector<double>::const_iterator Iter;

double clenshaw(double const & x, 
                Iter begin, 
                Iter end, 
                const std::function<double(double, int)>& alpha_rec, 
                const std::function<double(double, int)>& beta_rec, 
                const std::function<double(double, int)>& phi);

#endif
