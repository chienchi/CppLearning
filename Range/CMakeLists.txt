add_executable(range_omp range_omp.cpp)
target_compile_options(range_omp PUBLIC -fopenmp)
target_link_libraries(range_omp gomp)