#include <iostream>
#include <vector>
#include <filesystem>

#include "process_otf.hpp"
#include "sab_file.hpp"

OTFData::OTFData(const std::string & directory){
    std::vector<std::string> files;
    for (const auto & entry : std::filesystem::directory_iterator(directory)){
        if (entry.is_regular_file()){
            files.push_back(entry.path());
        }
    }
    std::cout << files[30] << std::endl;
}