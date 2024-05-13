#ifndef MAVOR_HDF5_FILE_H
#define MAVOR_HDF5_FILE_H

#include <iostream>
#include <vector>

#include "H5Cpp.h"

void readHDF5Int(H5::H5File& file, const std::string& datasetName, int& value);

void writeHDF5Int(H5::H5File file, int const & value, std::string const & value_name);

void readHDF5Double(H5::H5File& file, const std::string& datasetName, double& value);

void writeHDF5Double(H5::H5File file, double const & value, std::string const & value_name);

void readHDF5DoubleVector(H5::H5File& file, const std::string& datasetName, std::vector<double>& array) ;

void writeHDF5DoubleVector(H5::H5File file, std::vector<double> const & vector, std::string const & vector_name);

void writeHDF5DoubleMatrix(H5::H5File file, std::vector<std::vector<double>> const & matrix, std::string const & matrix_name);

#endif
