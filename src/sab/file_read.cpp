#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#include "H5Cpp.h"
#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/tree/fromFile.hpp"
#include "ENDFtk/section/7/4.hpp"

#include "file_read.hpp"
#include "runtime_variables.hpp"
#include "hdf5_file.hpp"

// Class Constructor
TslFileData::TslFileData(const std::string& file_path, const std::string & file_type){
    if (file_type == "hdf5"){read_from_hdf5__(file_path);}
    else if (file_type == "endf"){read_from_endf__(file_path);}
    else{throw std::runtime_error("File type was not recognized.");}
}

void TslFileData::read_from_hdf5__(const std::string & file_path){
    H5::H5File file(file_path, H5F_ACC_RDONLY);

    readHDF5Int(file, "lat", lat);
    readHDF5Int(file, "lasym", lasym);
    readHDF5Int(file, "lln", lln);
    readHDF5Int(file, "za", za);
    readHDF5Int(file, "mat", mat);
    predefined_energy_grid_key = mat;
    readHDF5Double(file, "temp", temp);
    readHDF5Double(file, "t_eff", t_eff);
    readHDF5Double(file, "temp_ratio", temp_ratio);
    readHDF5Double(file, "a0", a0);
    readHDF5Double(file, "e_max", e_max);
    readHDF5Double(file, "m0", m0);
    readHDF5Double(file, "free_xs", free_xs);
    readHDF5Double(file, "bound_xs", bound_xs);
    readHDF5DoubleVector(file, "alphas", alphas);
    readHDF5DoubleVector(file, "betas", betas);
    readHDF5DoubleVector(file, "tsl_vals", tsl_vals_array);
    tsl_vals = __vector_to_matrix__(tsl_vals_array, betas.size(), alphas.size());
    
    file.close();
}

void TslFileData::write_to_hdf5__(const std::string & file_path){
    H5::FileCreatPropList fcpl;
    H5::FileAccPropList fapl;
    H5::H5File file(file_path, H5F_ACC_TRUNC, fcpl, fapl);

    writeHDF5Int(file, lat, "lat");
    writeHDF5Int(file, lasym, "lasym");
    writeHDF5Int(file, lln, "lln");
    writeHDF5Int(file, za, "za");
    writeHDF5Int(file, mat, "mat");
    writeHDF5Double(file, temp, "temp");
    writeHDF5Double(file, t_eff, "t_eff");
    writeHDF5Double(file, temp_ratio, "temp_ratio");
    writeHDF5Double(file, a0, "a0");
    writeHDF5Double(file, e_max, "e_max");
    writeHDF5Double(file, m0, "m0");
    writeHDF5Double(file, free_xs, "free_xs");
    writeHDF5Double(file, bound_xs, "bound_xs");
    writeHDF5DoubleVector(file, alphas, "alphas");
    writeHDF5DoubleVector(file, betas, "betas");
    writeHDF5DoubleMatrix(file, tsl_vals, "tsl_vals");

    file.close();
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
    
    int nb = scattering_law.betas().size();
    int na = scattering_law.scatteringFunctions()[0].alphas().size();

    betas.resize(nb);
    alphas.resize(na);
    tsl_vals.resize(nb, std::vector<double>(na));

    for (int i = 0; i < nb; ++i){
        betas[i] = scattering_law.betas()[i];
        for (int j = 0; j < na; ++j){
            if (i == 0){alphas[j] = scattering_law.scatteringFunctions()[i].alphas()[j];}
            tsl_vals[i][j] = scattering_law.scatteringFunctions()[i].thermalScatteringValues()[0][j];
        }
    }
}

// Private Methods //
// Supporting data methods

void TslFileData::__vec_element_mult__(std::vector<double>&vec, double const val){
    for(int i = 0; i<vec.size(); i++){
        vec[i] *= val;
    }
}

void TslFileData::__matrix_element_exp__(std::vector<std::vector<double>>&matrix){
    for(auto& vec: matrix){
        for(int i = 0; i<vec.size(); i++){
            vec[i] = std::exp(vec[i]);
        }
    }
}

std::vector<std::vector<double>> TslFileData::__vector_to_matrix__(std::vector<double> const & flat_vector, int const n_rows, int const n_cols){
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

std::vector<double> TslFileData::__vector_mirror__(std::vector<double> const & vec, bool const del_duplicate){
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

std::vector<double> TslFileData::__negative_vector_mirror__(std::vector<double> const & vec, bool const del_duplicate){
    std::vector<double> new_vec(vec);
    if(del_duplicate){
        new_vec.erase(new_vec.begin());
    }
    std::reverse(new_vec.begin(), new_vec.end());
    __vec_element_mult__(new_vec, -1);
    for(auto val: vec){
        new_vec.push_back(val);
    }
    return new_vec;
}

std::vector<std::vector<double>> TslFileData::__matrix_2d_mirror__(std::vector<std::vector<double>> const & matrix2d, bool const del_duplicate){
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


std::vector<double> TslFileData::__lat_scale__(std::vector<double> const & vec, double const ref_temp){
    std::vector<double> new_vec(vec);
    if (lat == 1){
        __vec_element_mult__(new_vec, ref_temp/temp);
    } 
    return new_vec;
}

// Public Methods //
// Alpha and Betas

std::vector<double> TslFileData::return_scaled_alphas(double const & ref_temp){
    return __lat_scale__(alphas);
}

std::vector<double> TslFileData::return_betas(){
    return betas;
}

std::vector<double> TslFileData::return_scaled_betas(double const & ref_temp){
    return __lat_scale__(betas);
}

std::vector<double> TslFileData::return_full_betas(){
   return __negative_vector_mirror__(betas, betas[0] == 0); 
}

std::vector<double> TslFileData::return_full_scaled_betas(double const & ref_temp){
    return __negative_vector_mirror__(__lat_scale__(betas), betas[0] == 0);
}


// TSL Values

std::vector<std::vector<double>> TslFileData::return_tsl_vals(){
    std::vector<std::vector<double>> new_mat(tsl_vals);
    if (lln != 0){
        __matrix_element_exp__(new_mat);
    }
    return new_mat;
}

std::vector<std::vector<double>> TslFileData::return_half_sym_tsl_vals(){
    std::vector<std::vector<double>> new_mat(return_tsl_vals());
    std::vector<double> temp_betas = return_scaled_betas();
    __vec_element_mult__(temp_betas, 0.5);
    if (lasym != 0){
        for(int i = 0; i<new_mat.size(); i++){
            __vec_element_mult__(new_mat[i], std::exp(temp_betas[i]/2));
        }
    }
    return new_mat;
}

std::vector<std::vector<double>> TslFileData::return_half_asym_tsl_vals(){
    std::vector<std::vector<double>> new_mat(return_tsl_vals());
    std::vector<double> temp_betas = return_scaled_betas();
    __vec_element_mult__(temp_betas, 0.5);
    if (lasym == 0){
        for(int i = 0; i<new_mat.size(); i++){
            __vec_element_mult__(new_mat[i], std::exp(-temp_betas[i]));
        }
    }
    return new_mat;
}

std::vector<std::vector<double>> TslFileData::return_full_sym_tsl_vals(){
    return __matrix_2d_mirror__(return_half_sym_tsl_vals(), betas[0] == 0); 
}

std::vector<std::vector<double>> TslFileData::return_full_asym_tsl_vals(){
    std::vector<std::vector<double>> new_mat = return_full_sym_tsl_vals();
    std::vector<double> temp_betas = return_full_scaled_betas();
    __vec_element_mult__(temp_betas, 0.5);
    for(int i = 0; i<new_mat.size(); i++){
        __vec_element_mult__(new_mat[i], std::exp(-temp_betas[i]));
    }
    return new_mat;
}