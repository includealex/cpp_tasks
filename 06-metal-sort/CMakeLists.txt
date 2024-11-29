cmake_minimum_required(VERSION 3.30.5)
project(PhysMultLib VERSION 1.0.0 DESCRIPTION "Sort of tuple")

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.[ch]pp)

add_library(my_tuplesort STATIC ${ALL_CXX_SOURCE_FILES})

target_include_directories(my_tuplesort PUBLIC includes/)

add_subdirectory(tests)

set_target_properties (my_tuplesort PROPERTIES
    CXX_STANDARD          17
    CXX_STANDARD_REQUIRED ON
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")