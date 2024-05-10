add_library(common_lib)

target_sources(common_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/runtime_variables.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/integration.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/interpolation.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/linearize.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/utilities.cpp")
                              
target_include_directories(common_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/common")