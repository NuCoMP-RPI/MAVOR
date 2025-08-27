#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#include <highfive/highfive.hpp>

#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/tree/fromFile.hpp"
#include "ENDFtk/section/7/4.hpp"

#include "file_read.hpp"
#include "runtime_variables.hpp"
#include "interpolation.hpp"

// Class Constructor
TslFileData::TslFileData(const std::string& file_path, const std::string & file_type){
    if (file_type == "hdf5"){read_from_hdf5__(file_path);}
    else if (file_type == "endf"){read_from_endf__(file_path);}
    else{throw std::runtime_error("File type was not recognized.");}
}

void TslFileData::read_from_hdf5__(const std::string & file_path){
    HighFive::File file(file_path, HighFive::File::ReadOnly);

    lat = file.getDataSet("lat").read<int>();
    lasym = file.getDataSet("lasym").read<int>();
    lln = file.getDataSet("lln").read<int>();
    za = file.getDataSet("za").read<int>();
    mat = file.getDataSet("mat").read<int>();
    predefined_energy_grid_key = mat;

    temp = file.getDataSet("temp").read<double>();
    t_eff = file.getDataSet("t_eff").read<double>();
    temp_ratio = file.getDataSet("temp_ratio").read<double>();
    a0 = file.getDataSet("a0").read<double>();
    e_max = file.getDataSet("e_max").read<double>();
    m0 = file.getDataSet("m0").read<double>();
    free_xs = file.getDataSet("free_xs").read<double>();
    bound_xs = file.getDataSet("bound_xs").read<double>();

    alpha_interpolants = file.getDataSet("alpha_interpolants").read<std::vector<int>>();
    alpha_interpolants_boundaries = file.getDataSet("alpha_interpolants_boundaries").read<std::vector<int>>();
    beta_interpolants = file.getDataSet("beta_interpolants").read<std::vector<int>>();
    beta_interpolants_boundaries = file.getDataSet("beta_interpolants_boundaries").read<std::vector<int>>();

    alphas = file.getDataSet("alphas").read<std::vector<double>>();
    betas = file.getDataSet("betas").read<std::vector<double>>();

    tsl_vals = file.getDataSet("tsl_vals").read<std::vector<std::vector<double>>>();
}

void TslFileData::write_to_hdf5(const std::string & file_path){
    HighFive::File file(file_path, HighFive::File::Overwrite);

    file.createDataSet("lat", lat);
    file.createDataSet("lasym", lasym);
    file.createDataSet("lln", lln);
    file.createDataSet("za", za);
    file.createDataSet("mat", mat);

    file.createDataSet("temp", temp);
    file.createDataSet("t_eff", t_eff);
    file.createDataSet("temp_ratio", temp_ratio);
    file.createDataSet("a0", a0);
    file.createDataSet("e_max", e_max);
    file.createDataSet("m0", m0);
    file.createDataSet("free_xs", free_xs);
    file.createDataSet("bound_xs", bound_xs);

    file.createDataSet("alpha_interpolants", alpha_interpolants);
    file.createDataSet("alpha_interpolants_boundaries", alpha_interpolants_boundaries);
    file.createDataSet("beta_interpolants", beta_interpolants);
    file.createDataSet("beta_interpolants_boundaries", beta_interpolants_boundaries);

    file.createDataSet("alphas", alphas);
    file.createDataSet("betas", betas);

    file.createDataSet("tsl_vals", tsl_vals);
}

// type aliases
using Tape = njoy::ENDFtk::tree::Tape;
using MF7MT4 = njoy::ENDFtk::section::Type<7,4>;
using Constants = njoy::ENDFtk::section::Type<7,4>::ScatteringLawConstants;
using TEFF = njoy::ENDFtk::section::Type<7, 4>::EffectiveTemperature;
using TabulatedScatteringFunction = njoy::ENDFtk::section::Type<7,4>::TabulatedFunctions;

void TslFileData::read_from_endf__(const std::string & file_path){
    Tape tape = njoy::ENDFtk::tree::fromFile(file_path);
    mat = tape.materialNumbers()[0];

    MF7MT4 mt4 = tape.materials().front().section(7,4).parse<7,4>();

    lat = mt4.LAT();
    lasym = mt4.LASYM();
    za = mt4.ZA();
    a0 = mt4.AWR();

    Constants constants = mt4.constants();
    lln = constants.LLN();
    e_max = constants.upperEnergyLimit();
    m0 = constants.numberAtoms()[0];
    free_xs = constants.totalFreeCrossSections()[0] / m0;
    bound_xs = free_xs * std::pow((a0 + 1) / a0, 2);

    TEFF pet = mt4.principalEffectiveTemperature();
    TabulatedScatteringFunction scattering_law = std::get<1>(mt4.scatteringLaw());

    if (pet.NT() > 1) {throw std::runtime_error("More than one temperature found in ENDF file.");}

    t_eff = pet.TEFF()[0];
    temp = scattering_law.scatteringFunctions()[0].temperatures()[0];
    temp_ratio = t_eff / temp;

    auto beta_interpolants_range = scattering_law.interpolants();
    beta_interpolants.reserve(beta_interpolants_range.size());
    for (auto item:beta_interpolants_range) {beta_interpolants.push_back(item);}
    auto beta_interpolants_boundaries_range = scattering_law.boundaries();
    beta_interpolants_boundaries.reserve(beta_interpolants_boundaries_range.size());
    for (auto item:beta_interpolants_boundaries_range) {beta_interpolants_boundaries.push_back(item);}
    
    int nb = scattering_law.betas().size();
    int na = scattering_law.scatteringFunctions()[0].alphas().size();

    betas.resize(nb);
    alphas.resize(na);
    tsl_vals.resize(nb, std::vector<double>(na));


    for (int i = 0; i < nb; ++i){
        betas[i] = scattering_law.betas()[i];
        auto scat_func = scattering_law.scatteringFunctions()[i];

        /// NOTE: This assumes all alpha ranges are the as the first beta.
        if (i == 0) {
            auto alpha_interpolants_range = scat_func.interpolants();
            alpha_interpolants.reserve(alpha_interpolants_range.size());
            for (auto item:alpha_interpolants_range) {alpha_interpolants.push_back(item);}
            auto alpha_interpolants_boundaries_range = scat_func.boundaries();
            alpha_interpolants_boundaries.reserve(alpha_interpolants_boundaries_range.size());
            for (auto item:alpha_interpolants_boundaries_range) {alpha_interpolants_boundaries.push_back(item);}
        }

        for (int j = 0; j < na; ++j){
            if (i == 0){alphas[j] = scat_func.alphas()[j];}
            tsl_vals[i][j] = scat_func.thermalScatteringValues()[0][j];
        }
    }
}

// Private Methods //
// Supporting data methods

void TslFileData::vec_element_mult__(std::vector<double>&vec, double const val){
    for(int i = 0; i<vec.size(); i++){
        vec[i] *= val;
    }
}

void TslFileData::matrix_element_exp__(std::vector<std::vector<double>>&matrix){
    for(auto& vec: matrix){
        for(int i = 0; i<vec.size(); i++){
            vec[i] = std::exp(vec[i]);
        }
    }
}

std::vector<std::vector<double>> TslFileData::vector_to_matrix__(std::vector<double> const & flat_vector, int const n_rows, int const n_cols){
    if(n_rows*n_cols != flat_vector.size()){
        throw std::domain_error("Length of the vector does not match the n_rows*n_cols");
    }
    std::vector<std::vector<double>> matrix;
    const auto begin = std::begin(flat_vector);
    for(std::size_t row = 0 ; row<n_rows; ++row){ 
        matrix.push_back({begin + row*n_cols, begin + (row+1)*n_cols});
    }
    return matrix;
}

std::vector<double> TslFileData::vector_mirror__(std::vector<double> const & vec, bool const del_duplicate){
    std::vector<double> new_vec(vec);
    if(del_duplicate){
        new_vec.erase(new_vec.begin());
    }
    std::reverse(new_vec.begin(), new_vec.end());
    for(auto val: vec){
        new_vec.push_back(val);
    }
    return new_vec;
}

std::vector<double> TslFileData::negative_vector_mirror__(std::vector<double> const & vec, bool const del_duplicate){
    std::vector<double> new_vec(vec);
    if(del_duplicate){
        new_vec.erase(new_vec.begin());
    }
    std::reverse(new_vec.begin(), new_vec.end());
    vec_element_mult__(new_vec, -1);
    for(auto val: vec){
        new_vec.push_back(val);
    }
    return new_vec;
}

std::vector<std::vector<double>> TslFileData::matrix_2d_mirror__(std::vector<std::vector<double>> const & matrix2d, bool const del_duplicate){
    std::vector<std::vector<double>> result(matrix2d);
    if(del_duplicate){
        result.erase(result.begin());
    }
    std::reverse(result.begin(), result.end());
    for(auto vec: matrix2d){
        result.push_back(vec);
    }
    return result;
}


std::vector<double> TslFileData::lat_scale__(std::vector<double> const & vec, double const ref_temp){
    std::vector<double> new_vec(vec);
    if (lat == 1){
        vec_element_mult__(new_vec, ref_temp/temp);
    } 
    return new_vec;
}

// Public Methods //
// Alpha and Betas

int TslFileData::return_alpha_schemes(){
    // This is a gross oversimplification of the interpolation rules
    int interp = alpha_interpolants[0];
    // check for lln setting
    if (lln == 1){
        // Only interp rules 2 and 3 can be changed
        if (interp == 2){interp = 4;}
        else if (interp == 3){interp = 5;}
        else{
            // If you are here cause of the warning, I recommend using the "return_arbitrary_TSL_val" in this source file.
            // That function will treat the data properly (if you add functionality for the alpha interpolants to change with beta but that shouldn't be hard to add).
            // You then would have to abandon the analytic integration schemes and just ensure that you linearize before integrating.
            if (!silence){
                std::cout << "Warning: LLN flag is set but alpha interpolation and integration scheme is not valid for conversion." << std::endl;
                std::cout << "No conversion will be applied." << std::endl;
            }
        }
    }
    return interp;
}

int TslFileData::return_beta_schemes(){
    // This is a gross oversimplification of the interpolation rules.
    // This assumes that only one interpolation rule is present.
    // It also does not account for the symmetric to asymmetric conversion as I do not know how to handle it. 
    return beta_interpolants[0];
}

std::vector<double> TslFileData::return_alphas(){
    return alphas;
}

std::vector<double> TslFileData::return_scaled_alphas(double const & ref_temp){
    return lat_scale__(alphas);
}

std::vector<double> TslFileData::return_betas(){
    return betas;
}

std::vector<double> TslFileData::return_scaled_betas(double const & ref_temp){
    return lat_scale__(betas);
}

std::vector<double> TslFileData::return_full_betas(){
   return negative_vector_mirror__(betas, betas[0] == 0); 
}

std::vector<double> TslFileData::return_full_scaled_betas(double const & ref_temp){
    return negative_vector_mirror__(lat_scale__(betas), betas[0] == 0);
}


// TSL Values

std::vector<std::vector<double>> TslFileData::return_tsl_vals(){
    std::vector<std::vector<double>> new_mat(tsl_vals);
    if (lln != 0){
        matrix_element_exp__(new_mat);
    }
    return new_mat;
}

std::vector<std::vector<double>> TslFileData::return_half_sym_tsl_vals(){
    std::vector<std::vector<double>> new_mat(return_tsl_vals());
    std::vector<double> temp_betas = return_scaled_betas();
    vec_element_mult__(temp_betas, 0.5);
    if (lasym != 0){
        for(int i = 0; i<new_mat.size(); i++){
            vec_element_mult__(new_mat[i], std::exp(temp_betas[i]/2));
        }
    }
    return new_mat;
}

std::vector<std::vector<double>> TslFileData::return_half_asym_tsl_vals(){
    std::vector<std::vector<double>> new_mat(return_tsl_vals());
    std::vector<double> temp_betas = return_scaled_betas();
    vec_element_mult__(temp_betas, 0.5);
    if (lasym == 0){
        for(int i = 0; i<new_mat.size(); i++){
            vec_element_mult__(new_mat[i], std::exp(-temp_betas[i]));
        }
    }
    return new_mat;
}

std::vector<std::vector<double>> TslFileData::return_full_sym_tsl_vals(){
    return matrix_2d_mirror__(return_half_sym_tsl_vals(), betas[0] == 0); 
}

std::vector<std::vector<double>> TslFileData::return_full_asym_tsl_vals(){
    std::vector<std::vector<double>> new_mat = return_full_sym_tsl_vals();
    std::vector<double> temp_betas = return_full_scaled_betas();
    vec_element_mult__(temp_betas, 0.5);
    for(int i = 0; i<new_mat.size(); i++){
        vec_element_mult__(new_mat[i], std::exp(-temp_betas[i]));
    }
    return new_mat;
}

double TslFileData::asym_SCT_alpha_integral_bounds__(double const& alpha, double const& beta){
    double abs_b = std::abs(beta);
    double two_sqrt_ar = 2.0*std::sqrt(alpha*temp_ratio);
    double erfc_1 = std::erfc((abs_b-alpha)/two_sqrt_ar);
    double erfc_2 = std::erfc((abs_b+alpha)/two_sqrt_ar);
    double inner_exp = std::exp(beta/(std::copysign(temp_ratio, beta)));
    double outer_exp = std::exp(-(abs_b/2.0)-(beta/2.0));
    return 0.5*(outer_exp*(erfc_1 - inner_exp*erfc_2));
}

double TslFileData::calculate_beta_min(double const& inc_energy){
    return -(inc_energy)/(boltz*temp);
}

double TslFileData::calculate_beta_max(double const& inc_energy){
    return beta_max;
}

std::pair<double, double> TslFileData::calculate_alpha_extrema(double const& inc_energy, double const& beta){
    double t1 = std::sqrt(inc_energy);
    double t2 = std::sqrt(std::abs(inc_energy + beta*boltz*temp));
    double t3 = a0*boltz*temp;
    return std::make_pair(std::max(alpha_min, std::pow((t1 - t2), 2)/t3), std::pow((t1 + t2), 2)/t3);
}

double TslFileData::return_sym_SCT(double const& alpha, double const& beta){
    double numer_numer = std::pow((alpha-std::abs(beta)), 2);
    double numer_denom = 4.0*alpha*temp_ratio;
    double numer = std::exp(-(numer_numer/numer_denom) + (std::abs(beta)/2.0));
    double denom = std::sqrt(4.0*PI*alpha*temp_ratio);
    return numer/denom;
}

double TslFileData::return_asym_SCT(double const& alpha, double const& beta){
    return std::exp(-beta/2.0) * return_sym_SCT(alpha, beta);
}

double TslFileData::return_asym_SCT_alpha_integral(double const& alpha_l, double const& alpha_u, double const& beta){
    double l = asym_SCT_alpha_integral_bounds__(alpha_l, beta);
    double u = asym_SCT_alpha_integral_bounds__(alpha_u, beta);
    return u-l;
}


struct CubicSpline {
    std::array<double, 4> x;
    std::array<double, 4> y;
    std::array<double, 4> M;  // Second derivatives

    // Constructor — builds the spline coefficients
    CubicSpline(const std::array<double, 4>& x_vals, const std::array<double, 4>& y_vals)
        : x(x_vals), y(y_vals), M{} {

        // h[i] = x[i+1] - x[i]
        double h0 = x[1] - x[0];
        double h1 = x[2] - x[1];
        double h2 = x[3] - x[2];

        assert(h0 > 0 && h1 > 0 && h2 > 0);

        // alpha[i] = 3 * ( (y[i+1] - y[i]) / h[i] - (y[i] - y[i-1]) / h[i-1] )
        double alpha1 = (3.0 / h1) * (y[2] - y[1]) - (3.0 / h0) * (y[1] - y[0]);
        double alpha2 = (3.0 / h2) * (y[3] - y[2]) - (3.0 / h1) * (y[2] - y[1]);

        // Solve tridiagonal system for M[1], M[2]
        // Natural spline: M[0] = M[3] = 0
        double l1 = 2 * (x[2] - x[0]);
        double mu1 = h1 / l1;
        double z1 = (alpha1 - 0) / l1;

        double l2 = 2 * (x[3] - x[1]) - h1 * mu1;
        double z2 = (alpha2 - h1 * z1) / l2;

        M[0] = 0.0;
        M[3] = 0.0;
        M[2] = z2;
        M[1] = z1 - mu1 * M[2];
    }

    // Evaluate the spline at x_eval
    double evaluate(double x_eval) const {
        // Find the interval
        int i = -1;
        if (x_eval < x[1]) i = 0;
        else if (x_eval < x[2]) i = 1;
        else i = 2;

        double h = x[i + 1] - x[i];
        double A = (x[i + 1] - x_eval) / h;
        double B = (x_eval - x[i]) / h;

        return A * y[i] + B * y[i + 1]
             + ((A*A*A - A) * M[i] + (B*B*B - B) * M[i + 1]) * (h * h) / 6.0;
    }
};


std::pair<double, bool> TslFileData::return_arbitrary_TSL_val(double const& alpha, double const& beta){
    // Convert alpha and beta into search values that are in the same domain as the stored values
    double search_alpha = alpha;
    double search_beta = beta;
    if (lat == 1){
        search_alpha *= temp/ref_temp_k;
        search_beta *= temp/ref_temp_k;
    }
    if (lasym == 0){
        search_beta = std::abs(search_beta);
    }
    // If the desired alpha/beta is not contained within the stored data, use SCT
    /// NOTE: Getting S values below the alpha grid is handled by extrapolation
    bool off_data = (
                    //  search_alpha < alphas.front() ||
                     search_alpha > alphas.back() || 
                     search_beta < betas.front() || 
                     search_beta > betas.back()
                     );
    if(off_data){return std::make_pair(return_asym_SCT(alpha, beta), true);}

    else{
        // Extract the S values that bracket the desired point
        int alpha_lo_insert = std::lower_bound(alphas.begin()+1, alphas.end(), search_alpha) - alphas.begin();
        int beta_lo_insert = std::lower_bound(betas.begin()+1, betas.end(), search_beta) - betas.begin();
        double f11 = tsl_vals[beta_lo_insert-1][alpha_lo_insert-1];
        double f12 = tsl_vals[beta_lo_insert-1][alpha_lo_insert];
        double f21 = tsl_vals[beta_lo_insert][alpha_lo_insert-1];
        double f22 = tsl_vals[beta_lo_insert][alpha_lo_insert];

        // If the any of the bracketing S values fall below the SCT cutoff, use SCT
        // Ensure to compare the true S value and not ln(S)
        // Ternary operator looks to see if lln is set, if so take exp, if not use value directly
        // Cant update the values themselves cause interpolation is only valid on stored values
        bool below_cutoff = ((lln ? std::exp(f11) : f11) < sct_cutoff ||
                             (lln ? std::exp(f12) : f12) < sct_cutoff ||
                             (lln ? std::exp(f21) : f21) < sct_cutoff ||
                             (lln ? std::exp(f22) : f22) < sct_cutoff);
        if (below_cutoff){return std::make_pair(return_asym_SCT(alpha, beta), true);}

        else{
            double s;
            double& b_l = betas[beta_lo_insert-1];
            double& b_u = betas[beta_lo_insert];
            double& a_l = alphas[alpha_lo_insert-1];
            double& a_u = alphas[alpha_lo_insert];

            int beta_range_insert = std::lower_bound(beta_interpolants_boundaries.begin(), 
                                                     beta_interpolants_boundaries.end(), 
                                                     beta_lo_insert) - beta_interpolants_boundaries.begin();
            int beta_interp_scheme = beta_interpolants[beta_range_insert];

            if (search_alpha < alphas.front()){
                // Opposite with what is stated in "(2016) Computational Methods used to Process Thermal Neutron Scattering Data for use in Continuous energy Monte Carlo Codes - Trumbull"
                // Maybe just a mistake in the writing of the paper cause this fixed scattering cosine calculations at low E
                // Also needed the ternary to change behavior so that energy transfer pdfs for HinH2O aligned
                // if s values are increasing with alpha, log-log interpolation, otherwise log-linear interpolation
                int b_l_alpha_interp_scheme = (f11 - f12 < 0 ? 5 : 4);
                int b_u_alpha_interp_scheme = (f21 - f22 < 0 ? 5 : 4);
                // int b_l_alpha_interp_scheme = (f11 - f12 > 0 ? 5 : 4);
                // int b_u_alpha_interp_scheme = (f21 - f22 > 0 ? 5 : 4);

                // interpolate wrt alphas
                double s_l = ENDF_interp(a_l, a_u, f11, f12, search_alpha, b_l_alpha_interp_scheme);
                double s_u = ENDF_interp(a_l, a_u, f21, f22, search_alpha, b_u_alpha_interp_scheme);
                // interpolate wrt beta
                s = ENDF_interp(b_l, b_u, s_l, s_u, search_beta, beta_interp_scheme);

                // Spline implementation with S(alpha=0)=0
                // std::array<double, 4> x_array = {0, alphas[0], alphas[1], alphas[2]};
                // std::array<double, 4> s_l_array = {0, tsl_vals[beta_lo_insert-1][0], tsl_vals[beta_lo_insert-1][1], tsl_vals[beta_lo_insert-1][2]};
                // std::array<double, 4> s_u_array = {0, tsl_vals[beta_lo_insert][0], tsl_vals[beta_lo_insert][1], tsl_vals[beta_lo_insert][2]};

                // CubicSpline spline_l(x_array, s_l_array);
                // CubicSpline spline_u(x_array, s_u_array);

                // double s_l = spline_l.evaluate(search_alpha);
                // double s_u = spline_u.evaluate(search_alpha);
                // s = ENDF_interp(b_l, b_u, s_l, s_u, search_beta, beta_interp_scheme);
            }
            else{
                // Determine the interpolation schemes
                int alpha_range_insert = std::lower_bound(alpha_interpolants_boundaries.begin(), 
                                                          alpha_interpolants_boundaries.end(), 
                                                          alpha_lo_insert) - alpha_interpolants_boundaries.begin();
                int alpha_interp_scheme = alpha_interpolants[alpha_range_insert];

                s = bi_interp(b_l, b_u, a_l, a_u,
                              f11, f12, f21, f22,
                              search_beta, search_alpha,
                              beta_interp_scheme, alpha_interp_scheme);
            }

            // Take exp(s) if lln is set
            if (lln == 1){s = std::exp(s);}
            // Multiply by exp(-beta/2) if lasym is set
            if (lasym == 0){s = std::exp(-beta/2.0) * s;}
            return std::make_pair(s, false);
        }
    }
}