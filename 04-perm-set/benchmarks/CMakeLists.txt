find_package(benchmark REQUIRED)

set(BENCH_EXE bench_permset)

add_executable(${BENCH_EXE} comp_times.cpp)
target_link_libraries(${BENCH_EXE} my_permset benchmark::benchmark)

add_custom_target(run_${BENCH_EXE}
		  COMMENT "Running benchmark"
		  COMMAND ./${BENCH_EXE})

add_dependencies(run_${BENCH_EXE} ${BENCH_EXE} my_permset)
