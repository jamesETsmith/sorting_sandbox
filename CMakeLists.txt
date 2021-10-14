cmake_minimum_required (VERSION 3.14)
project (sorting_sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Special compile flags (i.e. optimizations) for release builds
execute_process(COMMAND cat /sys/devices/cpu/caps/pmu_name OUTPUT_VARIABLE ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)
if (ARCH STREQUAL "")
    message(WARNING "Architecture not found, using march=native.")
    set(ARCH "native")
else()
    message(STATUS "Using the compiler optimizations for march=${ARCH}")
endif()

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

#
# Source and Building
#

include_directories(${CMAKE_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(src/test)
