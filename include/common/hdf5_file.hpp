#ifndef MAVOR_HDF5_FILE_H
#define MAVOR_HDF5_FILE_H

#include <iostream>
#include <vector>

#include "H5Cpp.h"

/// @brief Reads a boolean value from an HDF5 dataset.
/// @param file Reference to the HDF5 file object.
/// @param datasetName Name of the dataset to read.
/// @param value Output boolean value.
void readHDF5Bool(H5::H5File& file, const std::string& datasetName, bool& value);

/// @brief Writes a boolean value to an HDF5 dataset.
/// @param file HDF5 file object.
/// @param value The boolean value to write.
/// @param value_name Name of the dataset to create.
void writeHDF5Bool(H5::H5File file, bool const& value, std::string const& value_name);

/// @brief Reads an integer value from an HDF5 dataset.
/// @param file Reference to the HDF5 file object.
/// @param datasetName Name of the dataset to read.
/// @param value Output integer value.
void readHDF5Int(H5::H5File& file, const std::string& datasetName, int& value);

/// @brief Writes an integer value to an HDF5 dataset.
/// @param file HDF5 file object.
/// @param value The integer value to write.
/// @param value_name Name of the dataset to create.
void writeHDF5Int(H5::H5File file, int const& value, std::string const& value_name);

/// @brief Reads a double value from an HDF5 dataset.
/// @param file Reference to the HDF5 file object.
/// @param datasetName Name of the dataset to read.
/// @param value Output double value.
void readHDF5Double(H5::H5File& file, const std::string& datasetName, double& value);

/// @brief Writes a double value to an HDF5 dataset.
/// @param file HDF5 file object.
/// @param value The double value to write.
/// @param value_name Name of the dataset to create.
void writeHDF5Double(H5::H5File file, double const& value, std::string const& value_name);

/// @brief Reads a vector of integers from an HDF5 dataset.
/// @param file Reference to the HDF5 file object.
/// @param datasetName Name of the dataset to read.
/// @param array Output vector of integers.
void readHDF5IntVector(H5::H5File& file, const std::string& datasetName, std::vector<int>& array);

/// @brief Writes a vector of integers to an HDF5 dataset.
/// @param file HDF5 file object.
/// @param vector The vector of integers to write.
/// @param vector_name Name of the dataset to create.
void writeHDF5IntVector(H5::H5File file, const std::vector<int>& vector, const std::string& vector_name);

/// @brief Reads a vector of doubles from an HDF5 dataset.
/// @param file Reference to the HDF5 file object.
/// @param datasetName Name of the dataset to read.
/// @param array Output vector of doubles.
void readHDF5DoubleVector(H5::H5File& file, const std::string& datasetName, std::vector<double>& array);

/// @brief Writes a vector of doubles to an HDF5 dataset.
/// @param file HDF5 file object.
/// @param vector The vector of doubles to write.
/// @param vector_name Name of the dataset to create.
void writeHDF5DoubleVector(H5::H5File file, std::vector<double> const& vector, std::string const& vector_name);

/// @brief Writes a matrix of doubles to an HDF5 dataset.
/// @param file HDF5 file object.
/// @param matrix The 2D vector (matrix) of doubles to write.
/// @param matrix_name Name of the dataset to create.
void writeHDF5DoubleMatrix(H5::H5File file, std::vector<std::vector<double>> const& matrix, std::string const& matrix_name);

/// @brief Writes a jagged matrix of doubles to an HDF5 dataset.
/// @param file HDF5 file object.
/// @param matrix The 2D jagged vector (matrix) of doubles to write.
/// @param matrix_name Name of the dataset to create.
void writeHDF5DoubleJaggedMatrix(H5::H5File file, std::vector<std::vector<double>> const& matrix, std::string const& matrix_name);

/// @brief Reads a string from an HDF5 dataset.
/// @param file Reference to the HDF5 file object.
/// @param datasetName Name of the dataset to read.
/// @param value Output string value.
void readHDF5String(H5::H5File& file, const std::string& datasetName, std::string& value);

/// @brief Writes a string to an HDF5 dataset.
/// @param file HDF5 file object.
/// @param value The string to write.
/// @param value_name Name of the dataset to create.
void writeHDF5String(H5::H5File file, std::string const& value, std::string const& value_name);


#endif
