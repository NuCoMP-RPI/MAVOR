add_executable(test_scale_basis test_scale_basis.cpp)
add_executable(test_file_reading test_file_reading.cpp)
add_executable(test_linspace test_linspace.cpp)
add_executable(test_arange test_arange.cpp)

target_link_libraries(test_scale_basis gtest_main common_lib)
target_link_libraries(test_file_reading gtest_main common_lib)
target_link_libraries(test_linspace gtest_main common_lib)
target_link_libraries(test_arange gtest_main common_lib)

target_include_directories(test_scale_basis PRIVATE "${CMAKE_SOURCE_DIR}/include/common")
target_include_directories(test_file_reading PRIVATE "${CMAKE_SOURCE_DIR}/include/common")
target_include_directories(test_linspace PRIVATE "${CMAKE_SOURCE_DIR}/include/common")
target_include_directories(test_arange PRIVATE "${CMAKE_SOURCE_DIR}/include/common")

add_test(NAME test_scale_basis COMMAND test_scale_basis)
add_test(NAME test_file_reading COMMAND test_file_reading)
add_test(NAME test_linspace COMMAND test_linspace)
add_test(NAME test_arange COMMAND test_arange)