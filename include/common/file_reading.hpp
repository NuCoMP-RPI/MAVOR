#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

bool debug_getline(std::ifstream& file, std::string& line);

std::vector<std::string> split(const std::string &s, char delimiter = ' ');

double ENDF_float(const std::string &s);
