cmake_minimum_required(VERSION 3.30)
project(my_str_COW VERSION 1.0)

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES *.cpp *.hpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

add_executable(a.out src/main.cpp)

target_include_directories(a.out PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_custom_target(run_simplest
    COMMAND ./a.out
    DEPENDS a.out
    COMMENT "Running the simplest executable"
)

add_subdirectory(tests)