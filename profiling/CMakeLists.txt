# Kernels for Profiling

# Grab all kernels
file(GLOB PROF_FILES prof_*.cpp)

# For each file: strip the name, print the name, add it as an exe, and link to all necessary libs
foreach(PROF_SRC ${PROF_FILES})
  get_filename_component(PROF_NAME ${PROF_SRC} NAME_WE)
  MESSAGE(STATUS "Configuring Profiling Kernels: ${PROF_NAME}")
  add_executable(${PROF_NAME} ${PROF_SRC})
  target_link_libraries(${PROF_NAME} PRIVATE OpenMP::OpenMP_CXX)

endforeach()


