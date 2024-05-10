add_library(otf_lib)

target_sources(otf_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/otf.cpp")
               
target_include_directories(otf_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/otf")