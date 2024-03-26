#include <iostream>
#include <vector>

#include "H5Cpp.h"

#include "file_read.hpp"

void readHDF5FloatArray(H5::H5File& file, const std::string& datasetName, std::vector<float>& dataArray) {
    H5::DataSet dataset = file.openDataSet(datasetName);
    H5::DataSpace dataspace = dataset.getSpace();
    int rank = dataspace.getSimpleExtentNdims();
    hsize_t dims[rank];
    dataspace.getSimpleExtentDims(dims);
    hsize_t totalSize = 1;
    for (int i = 0; i < rank; ++i) {
        totalSize *= dims[i];
    }
    dataArray.resize(totalSize);
    dataset.read(dataArray.data(), H5::PredType::NATIVE_FLOAT);
    dataset.close();
    dataspace.close();
}

void readHDF5Float(H5::H5File& file, const std::string& datasetName, float& value){
    H5::DataSet dataset = file.openDataSet(datasetName);
    H5::DataSpace dataspace = dataset.getSpace();
    dataset.read(&value, H5::PredType::NATIVE_FLOAT);
    dataset.close();
    dataspace.close();
}

void readHDF5Int(H5::H5File& file, const std::string& datasetName, int& value){
    H5::DataSet dataset = file.openDataSet(datasetName);
    H5::DataSpace dataspace = dataset.getSpace();
    dataset.read(&value, H5::PredType::NATIVE_INT16);
    dataset.close();
    dataspace.close();
}

void read_file(const std::string& file_path, TslData& data){
    H5::H5Library::open();
    H5::H5File file(file_path, H5F_ACC_RDONLY);

    readHDF5Int(file, "lat", data.lat);
    readHDF5Int(file, "lasym", data.lasym);
    readHDF5Int(file, "lln", data.lln);
    readHDF5Int(file, "za", data.za);
    readHDF5Int(file, "mat", data.mat);
    readHDF5Float(file, "temp", data.temp);
    readHDF5Float(file, "t_eff", data.t_eff);
    readHDF5Float(file, "temp_ratio", data.temp_ratio);
    readHDF5Float(file, "a0", data.a0);
    readHDF5Float(file, "e_max", data.e_max);
    readHDF5Float(file, "m0", data.m0);
    readHDF5Float(file, "free_xs", data.free_xs);
    readHDF5Float(file, "bound_xs", data.bound_xs);
    readHDF5FloatArray(file, "alphas", data.alphas);
    readHDF5FloatArray(file, "alphas", data.alphas);
    readHDF5FloatArray(file, "alphas", data.alphas);
    readHDF5FloatArray(file, "alphas", data.alphas);
    readHDF5FloatArray(file, "alphas", data.alphas);
    readHDF5FloatArray(file, "alphas", data.alphas);
    readHDF5FloatArray(file, "betas", data.betas);
    readHDF5FloatArray(file, "tsl_vals", data.tsl_vals);
    
    file.close();
    H5::H5Library::close();
}