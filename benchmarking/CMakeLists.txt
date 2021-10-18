# Benchmarking with Google Benchmark

# Grab all benchmarks
file(GLOB BENCH_FILES bench_*.cpp)

# For each file: strip the name, print the name, add it as an exe, and link to all necessary libs
foreach(BENCH_SRC ${BENCH_FILES})
  get_filename_component(BENCH_NAME ${BENCH_SRC} NAME_WE)
  MESSAGE(STATUS "Configuring benchmark: ${BENCH_NAME}")
  add_executable(${BENCH_NAME} ${BENCH_SRC})
  target_link_libraries(${BENCH_NAME} PRIVATE OpenMP::OpenMP_CXX benchmark::benchmark)

  #
#   add_BENCH(NAME ${BENCH_NAME} COMMAND ${BENCH_NAME})
endforeach()


