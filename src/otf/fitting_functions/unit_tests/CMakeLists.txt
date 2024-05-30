add_executable(test_power test_power.cpp)
target_link_libraries(test_power gtest_main fitting_functions_lib)

target_include_directories(test_power PRIVATE "${CMAKE_SOURCE_DIR}/include/otf/fitting_functions")

# Add a test target
add_test(NAME test_power COMMAND test_power)