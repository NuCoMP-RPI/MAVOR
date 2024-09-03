#include <vector>
#include <functional>

double clenshaw(double const & x, 
                std::vector<double> const & coeffs, 
                const std::function<double(double, int)>& alpha_rec, 
                const std::function<double(double, int)>& beta_rec, 
                const std::function<double(double, int)>& phi){
    double bk2 = 0;
    double bk1 = 0;
    double bk = 0;
    for (double k = coeffs.size(); k > 0; --k){
        bk = coeffs[k] + alpha_rec(x, k)*bk1 + beta_rec(x,k)*bk2;
        bk2 = bk1;
        bk1 = bk;
    }
    return phi(x,0)*coeffs[0] + phi(x,1)*bk1 + beta_rec(x,1)*phi(x,0)*bk2;
}