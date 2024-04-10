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

# Find HDF5 package
find_package(HDF5 COMPONENTS CXX REQUIRED)

add_compile_options(-lhdf5_cpp -lhdf5)

add_executable(mavor src/main.cpp
                     src/process_file.cpp
                     src/file_read.cpp
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

#===============================================================================
# Allow for install of executable
install(TARGETS mavor 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)