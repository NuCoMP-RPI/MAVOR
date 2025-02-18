#include <iostream>
#include <chrono>

#include "elastic.hpp"
#include "runtime_variables.hpp"
#include "add_elastic.hpp"

void run_elastic(){
    if (!silence){
        std::cout << "Adding elastic scattering data | " << otf_input_directory << std::endl;
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    scattering_data();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    if (!silence){
        std::cout << "Time to add elastic scattering data | milliseconds " << duration.count() << std::endl;
    }
}