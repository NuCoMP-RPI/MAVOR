add_executable(test_scale_basis test_scale_basis.cpp)
target_link_libraries(test_scale_basis gtest_main common_lib)

target_include_directories(test_scale_basis PRIVATE "${CMAKE_SOURCE_DIR}/include/common")

# Add a test target
add_test(NAME test_scale_basis COMMAND test_scale_basis)