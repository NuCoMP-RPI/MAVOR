cmake_minimum_required(VERSION 3.11)
project(mavor CXX)

add_executable(mavor src/main.cpp
                     src/process_file.cpp)

set_target_properties(mavor PROPERTIES OUTPUT_NAME "mavor")
target_include_directories(mavor PRIVATE include)
target_compile_features(mavor PRIVATE cxx_std_20)
#===============================================================================
# Allow for install of executable
install(TARGETS mavor 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)