add_library(sab_lib)

target_sources(sab_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/sab.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/energy_grid.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/file_read.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/file_write.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/process_file.cpp")

target_link_libraries(sab_lib PRIVATE 
                              common_lib
                              predefined_lib)

target_link_libraries(sab_lib PRIVATE ENDFtk)
target_include_directories(sab_lib PRIVATE ENDFtk)

target_include_directories(sab_lib PUBLIC ${highfive_SOURCE_DIR}/include)
target_link_libraries(sab_lib PUBLIC hdf5-static)
                              
target_include_directories(sab_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/sab")
target_include_directories(sab_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/common")
target_include_directories(sab_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/predefined")