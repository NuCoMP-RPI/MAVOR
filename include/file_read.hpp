#ifndef MAVOR_FILE_READ_H
#define MAVOR_FILE_READ_H

#include <iostream>
#include <vector>

// Data Structures
typedef struct {
    int lat;
    int lasym;
    int lln;
    int za;
    int mat;
    float temp;
    float t_eff;
    float temp_ratio;
    float a0;
    float e_max;
    float m0;
    float free_xs;
    float bound_xs;
    std::vector<float> alphas;
    std::vector<float> betas;
    std::vector<float> tsl_vals;
} TslData;

// Function calls
void read_file(const std::string& file_path, TslData& data);

#endif