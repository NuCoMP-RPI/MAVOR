add_executable(test_sample_search test_sample_search.cpp)

target_link_libraries(test_sample_search gtest_main sample_lib)

target_include_directories(test_sample_search PRIVATE "${CMAKE_SOURCE_DIR}/include/sample" "${CMAKE_SOURCE_DIR}/include/predefined")

# Add a test target
add_test(NAME test_sample_search COMMAND test_sample_search)