#include "file_reading.hpp"

bool debug_getline(std::ifstream& file, std::string& line) {
    bool result = static_cast<bool>(std::getline(file, line));
    if (result) {
        std::cout << "Read line: " << line << std::endl;
    }
    else {
        std::cout << "Get line returned false" << std::endl;
    }
    return result;
}

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

double ENDF_float(const std::string &str) {
    // std::cout << "Passed ENDF_float str: " << str << std::endl;
    std::string trimmed = str;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r") + 1);
    if (trimmed.empty()) {
        throw std::invalid_argument("Empty string passed to ENDF_float.");
    }
    size_t pos = trimmed.find_first_of("+-", 1);
    if (pos != std::string::npos && (pos + 1 < trimmed.size()) && isdigit(trimmed[pos + 1]) && std::tolower(trimmed[pos-1]) != 'e') {
        trimmed.insert(trimmed.begin()+pos, 'e');
    }
    return std::stod(trimmed);
}