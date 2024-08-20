add_library(fitting_functions_lib)

target_sources(fitting_functions_lib PRIVATE
               "${CMAKE_CURRENT_LIST_DIR}/basis_chebyshev.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_cosine.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_exponential.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_inverse_exponential.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_inverse_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_inverse_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_inverse_sqrt_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_inverse_sqrt_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_legendre.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_sine_cosine.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_sine.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_sqrt_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/basis_sqrt_power.cpp"
               )

target_include_directories(fitting_functions_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/otf/fitting_functions"
                                                         "${CMAKE_SOURCE_DIR}/include/common")
if(COMPILE_TESTS)
    add_subdirectory(unit_tests)
endif(COMPILE_TESTS)