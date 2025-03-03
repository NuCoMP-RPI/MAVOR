add_executable(test_file_read test_file_read.cpp)

target_include_directories(test_file_read PRIVATE "${CMAKE_SOURCE_DIR}/include/sab")
target_include_directories(test_file_read PRIVATE "${CMAKE_SOURCE_DIR}/include/common")
target_include_directories(test_file_read PRIVATE ${highfive_SOURCE_DIR}/include)

target_link_libraries(test_file_read PRIVATE hdf5-static gtest_main gmock_main sab_lib)

add_test(NAME test_file_read COMMAND test_file_read)