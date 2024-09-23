add_subdirectory(fit_evaluation)

add_library(sample_lib)

target_sources(sample_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/sample.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/sample_cdf.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/sample_coeff.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/sample_search.cpp")

target_link_libraries(sample_lib PRIVATE 
                              common_lib
                              predefined_lib
                              otf_lib
                              fit_evaluation_lib)

# Link OpenMP library
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(sample_lib PRIVATE OpenMP::OpenMP_CXX)
endif()

# Link HDF5 library
target_link_libraries(sample_lib PRIVATE ${HDF5_LIBRARIES})
target_include_directories(sample_lib PRIVATE ${HDF5_INCLUDE_DIRS})
                              
target_include_directories(sample_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/sample")
target_include_directories(sample_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/sample/fit_evaluation")
target_include_directories(sample_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/common")
target_include_directories(sample_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/predefined")
target_include_directories(sample_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/otf")

if(COMPILE_TESTS)
    add_subdirectory(unit_tests)
endif(COMPILE_TESTS)