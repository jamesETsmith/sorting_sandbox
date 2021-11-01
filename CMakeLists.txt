cmake_minimum_required (VERSION 3.14)
project (sorting_sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE RELEASE)

# Special compile flags (i.e. optimizations) for release builds
execute_process(COMMAND cat /sys/devices/cpu/caps/pmu_name OUTPUT_VARIABLE ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)
if (ARCH STREQUAL "")
    message(WARNING "Architecture not found, using march=native.")
    set(ARCH "native")
else()
    message(STATUS "Using the compiler optimizations for march=${ARCH}")
endif()

# set(CMAKE_CXX_FLAGS "-O3 -g -march=${ARCH} -Wno-narrowing -stdlib=libc++")
set(CMAKE_CXX_FLAGS "-O3 -g -march=${ARCH} -Wno-narrowing")


#
# Some RPATH settings (more later during install)
#
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#
# Dependencies
#

find_package(OpenMP)

include_directories(${CMAKE_SOURCE_DIR}/include)

#
# Source and Building
#


enable_testing()
add_subdirectory(src/test)

#
# Adding benchmarks
#

# Make sure CMake see benchmark

# add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest)
# add_subdirectory(${CMAKE_SOURCE_DIR}/external/benchmark)


# Add configure our benchmarks
# add_subdirectory(${CMAKE_SOURCE_DIR}/benchmarking)



#
# Adding Profiling Kernels
#

add_subdirectory(profiling)
