add_library(fit_evaluation_lib)

target_sources(fit_evaluation_lib PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/set_evaluation.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_chebyshev.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_cosine.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_exponential.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_inverse_exponential.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_inverse_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_inverse_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_inverse_sqrt_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_inverse_sqrt_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_legendre.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_sine_cosine.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_sine.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_sqrt_log_power.cpp"
               "${CMAKE_CURRENT_LIST_DIR}/coeff_sqrt_power.cpp"
               )
                              
target_include_directories(fit_evaluation_lib PRIVATE "${CMAKE_SOURCE_DIR}/include/sample/fit_evaluation" 
                                                      "${CMAKE_SOURCE_DIR}/include/common")

if(COMPILE_TESTS)
    add_subdirectory(unit_tests)
endif(COMPILE_TESTS)