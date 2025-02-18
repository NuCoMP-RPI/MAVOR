add_library(elastic_lib)

target_sources(elastic_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/elastic.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/add_elastic.cpp"
              )

target_link_libraries(elastic_lib PRIVATE common_lib)

target_include_directories(elastic_lib PUBLIC ${highfive_SOURCE_DIR}/include)
target_link_libraries(elastic_lib PUBLIC hdf5-static)

target_link_libraries(elastic_lib PRIVATE ENDFtk)
target_include_directories(elastic_lib PRIVATE ENDFtk)

target_include_directories(elastic_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/elastic")
target_include_directories(elastic_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/common")