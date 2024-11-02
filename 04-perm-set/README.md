This is a directory related to permanent set creation. This permanent set is based on the persistent tree.

For `strings` permanent set `string_twine` is used for better performance.

For project build, run:

```bash
cmake -B build -GNinja
ninja -C build run_permset_test -j$(nproc)
```

For benchmark of showing difference between partial specialisation of strings set and default integers set to be run, you should have installed `google/benchmark`. Run with this command:

```bash
ninja -C build run_bench_permset
```

Output of benchmark being run:
```sh
Run on (20 X 4600 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 24576 KiB (x1)
Load Average: 0.84, 1.24, 1.14
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-----------------------------------------------------------
Benchmark                 Time             CPU   Iterations
-----------------------------------------------------------
integers_permset        106 ms          106 ms            6
strings_permset        5.29 ms         5.29 ms          133
```