add_subdirectory(common)
add_subdirectory(predefined)
add_subdirectory(njoy)
add_subdirectory(sab)
add_subdirectory(otf)

add_executable(mavor)

target_sources(mavor PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/mavor.cpp")

target_link_libraries(mavor PRIVATE 
                      predefined_lib
                      common_lib                      
                      njoy_lib 
                      sab_lib 
                      otf_lib)

set_target_properties(mavor PROPERTIES OUTPUT_NAME "mavor")
target_include_directories(mavor PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(mavor PRIVATE "${CMAKE_SOURCE_DIR}/include/predefined")
target_include_directories(mavor PRIVATE "${CMAKE_SOURCE_DIR}/include/common")
target_include_directories(mavor PRIVATE "${CMAKE_SOURCE_DIR}/include/njoy")
target_include_directories(mavor PRIVATE "${CMAKE_SOURCE_DIR}/include/otf")
target_include_directories(mavor PRIVATE "${CMAKE_SOURCE_DIR}/include/sab")
target_compile_features(mavor PRIVATE cxx_std_20)

# Link CLI11
target_link_libraries(mavor PRIVATE CLI11::CLI11)

set_target_properties(mavor PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
install(TARGETS mavor RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})