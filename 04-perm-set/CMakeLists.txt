cmake_minimum_required(VERSION 3.30.5)
project(PermSetLib VERSION 1.0.0 DESCRIPTION "Permanent set library")

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.[ch]pp)

add_library(my_permset STATIC ${ALL_CXX_SOURCE_FILES})

target_include_directories(my_permset PUBLIC includes/)

add_subdirectory(tests)
add_subdirectory(benchmarks)

set_target_properties (my_permset PROPERTIES
    CXX_STANDARD          17
    CXX_STANDARD_REQUIRED ON
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")