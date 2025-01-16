#ifndef MAVOR_FILE_WRITE
#define MAVOR_FILE_WRITE

#include "process_file.hpp"

/// @brief Writes the SAB sampling distributions
/// @param sampling_data SAB sampling data to write
/// @param file_name File path and name to write
void write_sampling_data(DistData const & sampling_data, std::string const & file_name);

#endif