add_library(tsl_lib)

target_sources(tsl_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/tsl.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/leapr_file.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/njoy_runner.cpp")

target_include_directories(tsl_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/tsl")
target_include_directories(tsl_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/sab")
target_include_directories(tsl_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/common")

target_include_directories(tsl_lib PRIVATE ${HDF5_INCLUDE_DIRS})