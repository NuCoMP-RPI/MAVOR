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

include(FetchContent)

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

# Find HDF5 package
find_package(HDF5 COMPONENTS CXX REQUIRED)
add_compile_options(-lhdf5_cpp -lhdf5)

add_subdirectory(src)

configure_file(test_files/HinYH2_293K.h5 test_files/HinYH2_293K.h5 COPYONLY)
configure_file(test_files/HinYH2_energies.txt test_files/HinYH2_energies.txt COPYONLY)