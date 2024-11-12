cmake_minimum_required(VERSION 3.11)
project(mavor CXX)

# Set default build behavior
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_compile_options(-fopenmp)

include(ExternalProject)
set(NJOY_BINARY_DIR ${CMAKE_BINARY_DIR}/NJOY/src/NJOY)
ExternalProject_Add(
    NJOY
    PREFIX ${CMAKE_BINARY_DIR}/NJOY
    GIT_REPOSITORY https://github.com/njoy/NJOY2016
    GIT_TAG 2016.76
    GIT_SHALLOW TRUE
    UPDATE_COMMAND ""
    BUILD_IN_SOURCE TRUE
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DCMAKE_Fortran_FLAGS="-w"
    INSTALL_COMMAND ""
    )

# Define TSL_NJOY_EXE_LOC as the path to the NJOY executable
set(TSL_NJOY_EXE_LOC ${NJOY_BINARY_DIR}/njoy CACHE STRING "Path to NJOY executable")

include(FetchContent)

# message(STATUS "Retrieving ENDFtk version 1.1.0")
# FetchContent_Declare(
#     ENDFtk
#     QUIET
#     GIT_REPOSITORY https://github.com/njoy/ENDFtk.git
#     GIT_TAG v1.1.0
#     GIT_SHALLOW TRUE
#     GIT_PROGRESS TRUE)

# FetchContent_MakeAvailable(ENDFtk)

message(STATUS "Retrieving ENDFtk develop")
FetchContent_Declare(
    ENDFtk
    QUIET
    GIT_REPOSITORY https://github.com/njoy/ENDFtk.git
    GIT_TAG develop
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(ENDFtk)

message(STATUS "Retrieving CLI11 version 2.4.1.")
FetchContent_Declare(
    CLI11 
    QUIET
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.4.1
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(CLI11)

message(STATUS "Retrieving Eigen")
FetchContent_Declare(
    EIGEN 
    QUIET
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG master
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(EIGEN)

# GTEST is added if compile test are set to true

# Find HDF5 package
find_package(HDF5 COMPONENTS CXX REQUIRED)
add_compile_options(-lhdf5_cpp -lhdf5)

configure_file(test_files/HinYH2_energies.txt test_files/HinYH2_energies.txt COPYONLY)
configure_file(test_files/HinYH2_293K_tsl.h5 test_files/HinYH2_293K_tsl.h5 COPYONLY)
configure_file(test_files/HinYH2_293K_CDFs.h5 test_files/HinYH2_293K_CDFs.h5 COPYONLY)
configure_file(test_files/HinYH2_coeffs.h5 test_files/HinYH2_coeffs.h5 COPYONLY)
configure_file(test_files/tsl-HinYH2.leapr test_files/tsl-HinYH2.leapr COPYONLY)

set(COMPILE_TESTS on)

option(generate_tests "Option to generate compile tests." ${COMPILE_TESTS})

if(COMPILE_TESTS)

    message(STATUS "Retrieving GTest")
    FetchContent_Declare(
        GTEST
        QUIET
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

    FetchContent_MakeAvailable(GTEST)

    enable_testing()
endif(COMPILE_TESTS)


add_subdirectory(src)