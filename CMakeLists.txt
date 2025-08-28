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

message(STATUS "Retrieving ENDFtk version 1.2.0")
FetchContent_Declare(
    ENDFtk
    QUIET
    GIT_REPOSITORY https://github.com/njoy/ENDFtk.git
    GIT_TAG v1.2.0
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
    GIT_PROGRESS TRUE
    )
FetchContent_MakeAvailable(CLI11)

message(STATUS "Retrieving Eigen")
FetchContent_Declare(
    EIGEN 
    QUIET
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG master
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    )
FetchContent_MakeAvailable(EIGEN)

# set(HDF5_USE_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)
# find_package(HDF5 REQUIRED COMPONENTS C)
# if(HDF5_FOUND)
#     message(STATUS "Found HDF5: ${HDF5_VERSION}")
#     include_directories(${HDF5_INCLUDE_DIRS})
#     link_libraries(${HDF5_LIBRARIES})
#     set(HDF5_IS_PARALLEL FALSE)
# else()
#     message(WARNING "No system HDF5 found, falling back to FetchContent")
    message(STATUS "Retrieving HDF5 version 1.14.6")
    set(HDF5_ENABLE_THREADSAFE     ON)
    set(HDF5_ENABLE_Z_LIB_SUPPORT OFF)
    set(HDF5_EXTERNALLY_CONFIGURED  1)
    set(HDF5_ENABLE_SZIP_SUPPORT  OFF)
    set(HDF5_BUILD_EXAMPLES       OFF)
    set(HDF5_BUILD_TOOLS          OFF)
    set(HDF5_BUILD_UTILS          OFF)
    set(HDF5_BUILD_HL_LIB         OFF)
    set(BUILD_SHARED_LIBS         OFF)
    FetchContent_Declare(HDF5
        GIT_REPOSITORY https://github.com/HDFGroup/hdf5.git
        GIT_TAG        hdf5-1.14.6
        EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(HDF5)
# endif()

message(STATUS "Retrieving HighFive version 2.10.1")
set(HIGHFIVE_UNIT_TESTS OFF)
set(HIGHFIVE_TEST_SPAN OFF)
set(HIGHFIVE_EXAMPLES OFF)
set(HIGHFIVE_BUILD_DOCS OFF)
set(HIGHFIVE_FIND_HDF5 OFF)
set(HIGHFIVE_USE_MPI OFF)
set(HIGHFIVE_USE_BOOST Off)
FetchContent_Declare(HighFive
    GIT_REPOSITORY https://github.com/BlueBrain/HighFive.git
    GIT_TAG        v2.10.1
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(HighFive)

# GTEST is added if compile test are set to true

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test_files)
file(GLOB TEST_FILES "test_files/*")
file(COPY ${TEST_FILES} DESTINATION ${CMAKE_BINARY_DIR}/test_files)

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