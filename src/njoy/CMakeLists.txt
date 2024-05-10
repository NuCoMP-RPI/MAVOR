add_library(njoy_lib)

target_sources(njoy_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/njoy.cpp")

target_include_directories(njoy_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/njoy")