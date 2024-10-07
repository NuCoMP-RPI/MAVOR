add_executable(test_scale_basis test_scale_basis.cpp)
add_executable(test_file_reading test_file_reading.cpp)

target_link_libraries(test_scale_basis gtest_main common_lib)
target_link_libraries(test_file_reading gtest_main common_lib)

target_include_directories(test_scale_basis PRIVATE "${CMAKE_SOURCE_DIR}/include/common")
target_include_directories(test_file_reading PRIVATE "${CMAKE_SOURCE_DIR}/include/common")

add_test(NAME test_scale_basis COMMAND test_scale_basis)
add_test(NAME test_file_reading COMMAND test_file_reading)