add_subdirectory(fitting_functions)

add_library(otf_lib)

target_sources(otf_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/otf.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/sab_file.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/process_otf.cpp")

target_link_libraries(otf_lib PRIVATE common_lib
                                      fitting_functions_lib
                                      predefined_lib)  

target_include_directories(otf_lib PUBLIC ${highfive_SOURCE_DIR}/include)
target_link_libraries(otf_lib PUBLIC hdf5-static)

target_link_libraries(otf_lib PRIVATE Eigen3::Eigen)

target_include_directories(otf_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/otf")
target_include_directories(otf_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/otf/fitting_functions")
target_include_directories(otf_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/common")
target_include_directories(otf_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/predefined")