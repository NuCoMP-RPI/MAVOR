add_library(predefined_lib)

target_sources(predefined_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/predefined_energy_grids.cpp")
                              
target_include_directories(predefined_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/predefined")