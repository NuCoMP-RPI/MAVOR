add_library(fitting_functions_lib)

target_sources(fitting_functions_lib PRIVATE
               "${CMAKE_CURRENT_LIST_DIR}/fitting_function.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/chebyshev.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/cosine.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/exponential.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/inverse_exponential.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/inverse_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/inverse_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/inverse_sqrt_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/inverse_sqrt_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/legendre.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/sine_cosine.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/sine.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/sqrt_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/sqrt_power.cpp"
               )

target_include_directories(fitting_functions_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/otf/fitting_functions"
                                                         "${CMAKE_SOURCE_DIR}/include/common")