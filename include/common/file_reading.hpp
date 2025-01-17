#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

/// @brief Reads a line from the given file and optionally outputs it for debugging.
/// @param file The input file stream to read from.
/// @param line The string to store the line that was read.
/// @return True if a line was successfully read, false otherwise.
bool debug_getline(std::ifstream& file, std::string& line);

/// @brief Splits a string into tokens based on the specified delimiter.
/// @param s The input string to be split.
/// @param delimiter The character used to delimit the tokens. Defaults to space (' ').
/// @return A vector of tokens extracted from the input string.
std::vector<std::string> split(const std::string &s, char delimiter = ' ');

/// @brief Parses a string in ENDF floating-point format and converts it to a double.
/// @param s The input string to parse.
/// @return The floating-point value represented by the input string.
/// @throws std::invalid_argument If the input string is empty or cannot be converted to a double.
double ENDF_float(const std::string &s);
