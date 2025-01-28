#ifndef MAVOR_FILE_READ_H
#define MAVOR_FILE_READ_H

#include <iostream>
#include <vector>

#include "H5Cpp.h"

#include "constants.hpp"

/// @brief Class to read in TSL data and provide methods to transform it into desired domains
class TslFileData {
    public:
        int lat;
        int lasym;
        int lln;
        int za;
        int mat;
        double temp;
        double t_eff;
        double temp_ratio;
        double a0;
        double e_max;
        double m0;
        double free_xs;
        double bound_xs;

        /// Constructor
        /// @brief Reads in the TSL data
        /// @param file_path Path to TSL file
        /// @param file_type "endf" for output straight from NJOY or "hdf5" if already processed
        TslFileData(const std::string& file_path, const std::string & file_type = "hdf5");

        /// @brief Writes TSL data to a HDF5 file
        /// @param file_path File path to write
        void write_to_hdf5__(const std::string & file_path);

        // Public facing methods to return desired versions of the TSL data

        /// @brief Returns the interpolation and integration scheme for the alpha axis.
        /// This current implementation is not correct.  It assumes that only one scheme is applied to all values and no ranges exist.
        /// It also does not correct for the non-linear exp(-beta/2) term when converting to the asymmetric form of the TSL.  
        /// This term should should change the beta schemes to reflect this but I was unable to find a way to do that without moving everything into file_read.cpp.
        /// That implementation was also 10x slower and had no noticeable effects for the metal hydrides so it was abandoned in place.
        /// If you want a more accurate implementation, use the "return_arbitrary_TSL_val" in file_read.cpp instead of the one in this source file.
        /// @return Interpolation and Integration scheme
        int return_alpha_schemes();

        /// @brief Returns the interpolation and integration scheme for the beta axis.
        /// This current implementation is not correct.  It assumes that only one scheme is applied to all values and no ranges exist.
        /// It also does not correct for the non-linear exp(-beta/2) term when converting to the asymmetric form of the TSL.  
        /// This term should should change the beta schemes to reflect this but I was unable to find a way to do that without moving everything into file_read.cpp.
        /// That implementation was also 10x slower and had no noticeable effects for the metal hydrides so it was abandoned in place.
        /// If you want a more accurate implementation, use the "return_arbitrary_TSL_val" in file_read.cpp instead of the one in this source file.
        /// @return Interpolation and Integration scheme
        int return_beta_schemes();

        /// @brief Returns the alpha values that are stored in the file
        /// @return Storage alpha values
        std::vector<double> return_alphas();

        /// @brief Scales the storage alphas to the correct temperature
        /// @param ref_temp Reference temperature that the alphas are stored
        /// @return Scaled alpha values at the TSL temperature
        std::vector<double> return_scaled_alphas(double const & ref_temp = ref_temp_k);

        /// @brief Returns the beta values that are stored in the file
        /// Used in process_file to get the storage beta grid for the alpha distributions
        /// @return Storage beta values
        std::vector<double> return_betas();

        /// @brief Scales the storage beta values to the correct temperature
        /// @param ref_temp Reference temperature that the betas are stored
        /// @return Scaled beta values at the TSL temperature
        std::vector<double> return_scaled_betas(double const & ref_temp = ref_temp_k);
        
        /// @brief Reflects the stored beta values about the beta=0 line
        /// @return Full beta values
        std::vector<double> return_full_betas();
        
        /// @brief Reflects and scales the stored beta values about the beta=0 line
        /// @param ref_temp Reference temperature that the betas are stored
        /// @return Full scaled beta values at the TSL temperature
        std::vector<double> return_full_scaled_betas(double const & ref_temp = ref_temp_k);
        
        /// @brief Returns the TSL values, taking the exponential if lln is set
        /// @return Stored TSL values
        std::vector<std::vector<double>> return_tsl_vals();
        
        /// @brief Returns the positive half of the symmetric TSL values
        /// @return Half Sym TSL values
        std::vector<std::vector<double>> return_half_sym_tsl_vals();
        
        /// @brief Returns the positive half of the assymetric TSL values
        /// @return Half asym TSL values
        std::vector<std::vector<double>> return_half_asym_tsl_vals();
        
        /// @brief Returns the full symmetric TSL values
        /// @return Full sym TSL values
        std::vector<std::vector<double>> return_full_sym_tsl_vals();
        
        /// @brief Returns the full asymmetric TSL values
        /// @return Full asym TSL values
        std::vector<std::vector<double>> return_full_asym_tsl_vals();
        
        /// @brief Calculates the minimum beta value given an incident energy
        /// @param inc_energy Desired incident energy in eV
        /// @return Minumum beta value
        double calculate_beta_min(double const& inc_energy);
        
        /// @brief Calculates teh maximum beta value given an incident energy.
        /// Currently only returns the value set in runtime variables
        /// @param inc_energy Desired incident energy in eV
        /// @return Maximum beta value
        double calculate_beta_max(double const& inc_energy);
        
        /// @brief Calculates the minimum and maximum alpha values given an incident energy and beta value.
        /// @param inc_energy Desired incident energy in eV
        /// @param beta Desired beta value
        /// @return Minimum and maximum alpha values, respectively
        std::pair<double, double> calculate_alpha_extrema(double const& inc_energy, double const& beta);

        /// @brief Calculates the symmetric short collision time approximation
        /// @param alpha Alpha value to calculate SCT
        /// @param beta Beta value to calculate SCT
        /// @return Symmetric SCT approximation at alpha and beta
        double return_sym_SCT(double const& alpha, double const& beta);
        
        /// @brief Calculates the asymmetric short collision time approximation
        /// @param alpha Alpha value to calculate SCT
        /// @param beta Beta value to calculate SCT
        /// @return Asymmetric SCT approximation at alpha and beta
        double return_asym_SCT(double const& alpha, double const& beta);
        
        /// @brief Calculated the definite integral of the asymmetric short collision time approximation at a given beta between two alpha points
        /// @param alpha_l Lower alpha bound
        /// @param alpha_u Upper alpha bound
        /// @param beta Beta value to calculate integral
        /// @return Integral of the asymmetric SCT approximation
        double return_asym_SCT_alpha_integral(double const& alpha_l, double const& alpha_u, double const& beta);
        
        /// @brief Calculates an arbitrary asymmetric TSL value given the TSL data.
        /// This method assumes that the desired alpha and beta points given are the true points.
        /// Meaning that they have already been scaled to the temperature of this data file.
        /// @param alpha Desired alpha value at temperature
        /// @param beta Desired beta value at temperature
        /// @return TSL value
        std::pair<double, bool> return_arbitrary_TSL_val(double const& alpha, double const& beta);

    private:
        std::vector<int> alpha_interpolants;
        std::vector<int> alpha_interpolants_boundaries;

        std::vector<int> beta_interpolants;
        std::vector<int> beta_interpolants_boundaries;

        std::vector<double> alphas;
        std::vector<double> betas;
        std::vector<double> tsl_vals_array;
        std::vector<std::vector<double>> tsl_vals;

        /// @brief Calculates the asymmetric short collision time integral bound given an alpha and beta value
        /// Integrates d alpha from [-infty, alpha]
        /// @param alpha Desired alpha value
        /// @param beta Desired beta value
        /// @return Integral bound
        double asym_SCT_alpha_integral_bounds__(double const& alpha, double const& beta);

        /// @brief Reads a HDF5 TSL file from this class
        /// @param file_path Path to file
        void read_from_hdf5__(const std::string & file_path);

        /// @brief Reads he ENDF formatted TSL file from NJOY
        /// @param file_path Path to file
        void read_from_endf__(const std::string & file_path);
        
        /// @brief In-place element-wise matrix exponentiation
        /// @param matrix Matrix to exponentiate
        void matrix_element_exp__(std::vector<std::vector<double>>&matrix);
        
        /// @brief In-place element-wise vector multiplication
        /// @param vec Vector to multiply
        /// @param val value to multiply by
        void vec_element_mult__(std::vector<double>&vec, double const val);
        
        /// @brief Turns a vector into a 2D matrix with a certain number of rows and columns (Row major)
        /// @param flat_vector Vector to shape
        /// @param n_rows Number of rows
        /// @param n_cols Number of columns
        /// @return Row major 2D matrix
        std::vector<std::vector<double>> vector_to_matrix__(std::vector<double> const & flat_vector, int const n_rows, int const n_cols);
        
        /// @brief Mirrors a vector about the first element, deleting the duplicate if desired
        /// @param arr Vector to mirror
        /// @param del_duplicate Delete the duplicate first element
        /// @return Mirrored vector
        std::vector<double> vector_mirror__(std::vector<double> const & arr, bool const del_duplicate);
        
        /// @brief Mirrors a vector and multiplies the mirrored by -1
        /// @param arr Vector to mirror
        /// @param del_duplicate Delete the duplicate first element
        /// @return Mirrored vector
        std::vector<double> negative_vector_mirror__(std::vector<double> const & arr, bool const del_duplicate);
        
        /// @brief Mirrors a 2D matrix along the first axis
        /// @param matrix2d Matrix to mirror
        /// @param del_duplicate Delete teh duplicate first vector
        /// @return Mirrored matrix
        std::vector<std::vector<double>> matrix_2d_mirror__(std::vector<std::vector<double>> const & matrix2d, bool const del_duplicate);
        
        /// @brief Scales values based on the 'lat' value set by NJOY
        /// @param arr Vector to scale
        /// @param ref_temp Reference temperature
        /// @return Scaled vector
        std::vector<double> lat_scale__(std::vector<double> const & arr, double const ref_temp = ref_temp_k);
};
#endif