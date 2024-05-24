add_library(predefined_lib)

target_sources(predefined_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/predefined_energy_grids.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/predefined_fit_settings.cpp")

target_link_libraries(predefined_lib PRIVATE fitting_functions_lib)
                              
target_include_directories(predefined_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/predefined"
                                                  "${CMAKE_SOURCE_DIR}/include/otf/fitting_functions")