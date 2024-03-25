cmake_minimum_required(VERSION 3.11)
project(mavor CXX)

# Find HDF5 package
find_package(HDF5 COMPONENTS CXX REQUIRED)

add_compile_options(-lhdf5_cpp -lhdf5)

add_executable(mavor src/main.cpp
                     src/process_file.cpp
                     src/file_read.cpp)

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