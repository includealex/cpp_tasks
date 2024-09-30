project(COWTest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRECTORIES})

enable_testing()

file(GLOB_RECURSE COWTEST_SRC test_cow.cpp)
set(EXEC_NAME cow_test)

add_executable(${EXEC_NAME} ${COWTEST_SRC})

if(SANITIZERS)
	target_compile_options(${EXEC_NAME} PUBLIC -fsanitize=address -g)
	set_target_properties(${EXEC_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()

target_link_libraries(${EXEC_NAME} GTest::Main)

add_custom_target(run_${EXEC_NAME}
	  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME})

add_dependencies(run_${EXEC_NAME} ${EXEC_NAME})