add_library(otf_lib)

target_sources(otf_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/otf.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/sab_file.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/process_otf.cpp")

target_link_libraries(otf_lib PRIVATE common_lib)

# Link HDF5 library
target_link_libraries(otf_lib PRIVATE ${HDF5_LIBRARIES})
target_include_directories(otf_lib PRIVATE ${HDF5_INCLUDE_DIRS})

# Link Eigen library
target_link_libraries(otf_lib PRIVATE Eigen3::Eigen)

target_include_directories(otf_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/otf")
target_include_directories(otf_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/common")