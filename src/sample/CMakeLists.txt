add_library(sample_lib)

target_sources(sample_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/sample.cpp")

target_link_libraries(sample_lib PRIVATE 
                              common_lib
                              predefined_lib
                              otf_lib)

# Link HDF5 library
target_link_libraries(sample_lib PRIVATE ${HDF5_LIBRARIES})
target_include_directories(sample_lib PRIVATE ${HDF5_INCLUDE_DIRS})
                              
target_include_directories(sample_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/sample")
target_include_directories(sample_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/common")
target_include_directories(sample_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/predefined")
target_include_directories(sample_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/otf")