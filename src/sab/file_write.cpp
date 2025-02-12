#include "H5Cpp.h"

#include "file_write.hpp"
#include "process_file.hpp"
#include "hdf5_file.hpp"

void write_sampling_data(DistData const & sampling_data, std::string const & file_name){
    H5::FileCreatPropList fcpl;
    H5::FileAccPropList fapl;
    H5::H5File file(file_name, H5F_ACC_TRUNC, fcpl, fapl);

    writeHDF5Int(file, sampling_data.tsl_data.za, "ZA");
    writeHDF5Int(file, sampling_data.tsl_data.mat, "MAT");
    writeHDF5Double(file, sampling_data.tsl_data.temp, "Temp");
    writeHDF5Double(file, sampling_data.tsl_data.t_eff, "T_EFF");
    writeHDF5Double(file, sampling_data.tsl_data.temp_ratio, "TEMP_RATIO");
    writeHDF5Double(file, sampling_data.tsl_data.a0, "A0");
    writeHDF5Double(file, sampling_data.tsl_data.e_max, "E_MAX");
    writeHDF5Double(file, sampling_data.tsl_data.m0, "M0");
    writeHDF5Double(file, sampling_data.tsl_data.free_xs, "FREE_XS");
    writeHDF5Double(file, sampling_data.tsl_data.bound_xs, "BOUND_XS");

    writeHDF5DoubleVector(file, sampling_data.incident_energy_grid, "Incident Energy Grid");
    writeHDF5DoubleVector(file, sampling_data.cross_section, "Incoherent Inelastic XS");
    writeHDF5DoubleJaggedMatrix(file, sampling_data.beta_cdf_grid, "Beta CDF Grid");
    writeHDF5DoubleJaggedMatrix(file, sampling_data.beta_vals, "Betas");

    writeHDF5DoubleVector(file, sampling_data.beta_grid, "Beta Grid");
    writeHDF5DoubleJaggedMatrix(file, sampling_data.alpha_cdf_grid, "Alpha CDF Grid");
    writeHDF5DoubleJaggedMatrix(file, sampling_data.alpha_vals, "Alphas");

    file.close();
}
