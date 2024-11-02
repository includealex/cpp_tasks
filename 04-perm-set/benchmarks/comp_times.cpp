#include <benchmark/benchmark.h>

#include "permset_impl.hpp"

static void integers_permset(benchmark::State& state) {
  for (auto _ : state) {
    custom::PermSet<std::size_t> set;

    std::size_t big_num = 1e3;
    for (std::size_t i = 0; i < big_num; ++i) {
        set.insert(i);
    }
  }
}

static void strings_permset(benchmark::State& state) {
  for (auto _ : state) {
    custom::PermSet<std::string> set;

    int big_num = 1e3;
    for (int i = 0; i < big_num; ++i) {
        std::string str = "string_" + std::to_string(i);
        set.insert(str);
    }
  }
}

BENCHMARK(integers_permset)->Unit(benchmark::kMillisecond);
BENCHMARK(strings_permset)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
