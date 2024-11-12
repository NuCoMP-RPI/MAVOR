add_library(common_lib)

target_sources(common_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/runtime_variables.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/integration.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/interpolation.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/linearize.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/clenshaw.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/horner.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/hdf5_file.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/file_reading.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/scale_basis.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/utilities.cpp")

# Link HDF5 library
target_link_libraries(common_lib PRIVATE ${HDF5_LIBRARIES})
target_include_directories(common_lib PRIVATE ${HDF5_INCLUDE_DIRS})
                              
target_include_directories(common_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/common")

# Set compile definitions so that mavor can always work in the build directory by defualt
add_compile_definitions(TSL_NJOY_EXE_LOC="${TSL_NJOY_EXE_LOC}")
add_compile_definitions(BUILD_DIR="${CMAKE_BINARY_DIR}")

if(COMPILE_TESTS)
    add_subdirectory(unit_tests)
endif(COMPILE_TESTS) 