#include <iostream>
#include <vector>
#include <math.h>

double ENDF_interp_scheme_1(double const & x1, double const & x2, double const & y1, double const & y2, double const& x){
    return y1;
}

double ENDF_interp_scheme_2(double const & x1, double const & x2, double const & y1, double const & y2, double const& x){
    return y1 + (y2 - y1) * ((x - x1) / (x2 - x1));
}

double ENDF_interp_scheme_3(double const & x1, double const & x2, double const & y1, double const & y2, double const& x){
    return y1 + (y2 - y1)*(log(x/x1)/log(x2/x1));
}

double ENDF_interp_scheme_4(double const & x1, double const & x2, double const & y1, double const & y2, double const& x){
    return y1*exp(log(y2/y1)*((x - x1)/(x2 - x1)));
}

double ENDF_interp_scheme_5(double const & x1, double const & x2, double const & y1, double const & y2, double const& x){
    return y1*exp(log(x/x1)*(log(y2/y1)/log(x2/x1)));
}

double ENDF_interp(double const & x1, double const & x2, double const & y1, double const & y2, double const & x, int const scheme){
    switch (scheme)
    {
    case 1:
        return ENDF_interp_scheme_1(x1, x2, y1, y2, x);
    case 2:
        return ENDF_interp_scheme_2(x1, x2, y1, y2, x);        
    case 3:
        return ENDF_interp_scheme_3(x1, x2, y1, y2, x);
    case 4:
        return ENDF_interp_scheme_4(x1, x2, y1, y2, x);
    case 5:
        return ENDF_interp_scheme_5(x1, x2, y1, y2, x);
    default:
        throw std::invalid_argument("Scheme type was not recognized.");
    }
}

std::vector<double> ENDF_interp_vector(double const & x1, double const & x2, std::vector<double> const & y1_vec, std::vector<double> const & y2_vec, double const & x, int const scheme){
    std::vector<double> results(y1_vec);
    for (int i = 0; i < y1_vec.size(); ++i){
        results[i] = ENDF_interp(x1, x2, y1_vec[i], y2_vec[i], x, scheme);
    }
    return results;
}

double bi_interp(double const & x1, double const & x2, double const & y1, double const & y2, 
                 double const & f11, double const & f12, double const & f21, double const & f22, 
                 double const & x, double const & y, 
                 int const x_scheme, int const y_scheme){
    //     | y1  |  y  | y2
    //  --------------------
    //  x1 | f11 |  -  | f12
    //  --------------------
    //  x  |  -  | fxy |  -
    //  --------------------
    //  x2 | f21 |  -  | f22
    double fxy1 = ENDF_interp(x1, x2, f11, f21, x, x_scheme);
    double fxy2 = ENDF_interp(x1, x2, f12, f22, x, x_scheme);
    return ENDF_interp(y1, y2, fxy1, fxy2, y, y_scheme);
}

std::pair<size_t, size_t> findInterpolationIndexes(const std::vector<double>& array, double val) {
    auto it = std::lower_bound(array.begin() + 1, array.end(), val); // +1 handles if below grid
    size_t hi_index = std::distance(array.begin(), it);
    hi_index = (hi_index == array.size()) ? hi_index - 1 : hi_index; // -1 handles if above grid
    size_t lo_index = hi_index - 1;
    return std::make_pair(lo_index, hi_index);
}

std::pair<size_t, size_t> findInterpolationIndexes(std::vector<double>::const_iterator begin, std::vector<double>::const_iterator end, double val) {
    auto it = std::lower_bound(begin + 1, end, val); // +1 handles if below grid
    size_t hi_index = std::distance(begin, it);
    hi_index = (hi_index == std::distance(begin, end)) ? hi_index - 1 : hi_index; // -1 handles if above grid
    size_t lo_index = hi_index - 1;
    return std::make_pair(lo_index, hi_index);
}