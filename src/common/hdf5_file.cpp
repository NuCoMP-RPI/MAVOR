#include <iostream>
#include <vector>

#include "H5Cpp.h"

void readHDF5Int(H5::H5File& file, const std::string& datasetName, int& value){
    H5::DataSet dataset = file.openDataSet(datasetName);
    H5::DataSpace dataspace = dataset.getSpace();
    dataset.read(&value, H5::PredType::NATIVE_INT);
    dataset.close();
    dataspace.close();
}

void writeHDF5Int(H5::H5File file, int const & value, std::string const & value_name){
    hsize_t dims[1] = {1};
    H5::DataSpace dataspace(1, dims);
    H5::IntType datatype(H5::PredType::NATIVE_INT);
    H5::DataSet dataset = file.createDataSet(value_name, datatype, dataspace);
    dataset.write(&value, H5::PredType::NATIVE_INT);
}

void readHDF5Double(H5::H5File& file, const std::string& datasetName, double& value){
    H5::DataSet dataset = file.openDataSet(datasetName);
    H5::DataSpace dataspace = dataset.getSpace();
    dataset.read(&value, H5::PredType::NATIVE_DOUBLE);
    dataset.close();
    dataspace.close();
}

void writeHDF5Double(H5::H5File file, double const & value, std::string const & value_name){
    hsize_t dims[1] = {1};
    H5::DataSpace dataspace(1, dims);
    H5::FloatType datatype(H5::PredType::NATIVE_DOUBLE);
    H5::DataSet dataset = file.createDataSet(value_name, datatype, dataspace);
    dataset.write(&value, H5::PredType::NATIVE_DOUBLE);
}

void readHDF5DoubleVector(H5::H5File& file, const std::string& datasetName, std::vector<double>& array) {
    H5::DataSet dataset = file.openDataSet(datasetName);
    H5::DataSpace dataspace = dataset.getSpace();
    // Fancy stuff is here to allow reading matrices into a vector
    // HDF5 does not support reading directly into nested vectors
    int rank = dataspace.getSimpleExtentNdims();
    hsize_t dims[rank];
    dataspace.getSimpleExtentDims(dims);
    hsize_t totalSize = 1;
    for(int i = 0; i<rank; ++i){
        totalSize *= dims[i];
    }
    array.resize(totalSize);
    dataset.read(array.data(), H5::PredType::NATIVE_DOUBLE);
    dataset.close();
    dataspace.close();
}

void writeHDF5DoubleVector(H5::H5File file, std::vector<double> const & vector, std::string const & vector_name){
    hsize_t dims[1] = {vector.size()};
    H5::DataSpace dataspace(1, dims);
    H5::FloatType datatype(H5::PredType::NATIVE_DOUBLE);
    H5::DataSet dataset = file.createDataSet(vector_name, datatype, dataspace);
    dataset.write(vector.data(), H5::PredType::NATIVE_DOUBLE);
}

void writeHDF5DoubleMatrix(H5::H5File file, std::vector<std::vector<double>> const & matrix, std::string const & matrix_name){
    hsize_t dims[2] = {matrix.size(), matrix[0].size()};
    H5::DataSpace dataspace(2, dims);
    H5::FloatType datatype(H5::PredType::NATIVE_DOUBLE);
    H5::DataSet dataset = file.createDataSet(matrix_name, datatype, dataspace);
    // Flatten matrix to be able to write
    // Don't think HDF5 supports vec<vec>> writing 
    std::vector<double> flattenedMatrix;
    for (const auto& row : matrix) {
        flattenedMatrix.insert(flattenedMatrix.end(), row.begin(), row.end());
    }
    dataset.write(flattenedMatrix.data(), H5::PredType::NATIVE_DOUBLE);
}