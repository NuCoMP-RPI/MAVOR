add_library(fit_evaluation)

target_sources(fit_evaluation PRIVATE 
               "${CMAKE_CURRENT_LIST_DIR}/set_evaluation.cpp"
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
                              
target_include_directories(fit_evaluation PRIVATE "${CMAKE_SOURCE_DIR}/include/sample/fit_evaluation" 
                                                  "${CMAKE_SOURCE_DIR}/include/common")