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
)

FetchContent_MakeAvailable(CLI11)

# Find HDF5 package
find_package(HDF5 COMPONENTS CXX REQUIRED)

add_compile_options(-lhdf5_cpp -lhdf5)

add_executable(mavor src/main.cpp
                     src/runtime_variables.cpp
                     src/process_file.cpp
                     src/energy_grid.cpp
                     src/predefined_energy_grids.cpp
                     src/file_read.cpp
                     src/file_write.cpp
                     src/interpolation.cpp
                     src/integration.cpp
                     src/utilities.cpp
                     src/linearize.cpp)

set_target_properties(mavor PROPERTIES OUTPUT_NAME "mavor")
target_include_directories(mavor PRIVATE include)
target_compile_features(mavor PRIVATE cxx_std_20)

# Link HDF5 library
target_link_libraries(mavor PRIVATE ${HDF5_LIBRARIES})
target_include_directories(mavor PRIVATE ${HDF5_INCLUDE_DIRS})
# Link CLI11
 target_link_libraries(mavor PRIVATE CLI11::CLI11)

configure_file(test_files/HinYH2_293K.h5 test_files/HinYH2_293K.h5 COPYONLY)
configure_file(test_files/HinYH2_energies.txt test_files/HinYH2_energies.txt COPYONLY)

# Allow for install of executable
install(TARGETS mavor 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)