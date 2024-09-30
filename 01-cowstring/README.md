If you want to run tests, just do:

```bash
cmake -B build -GNinja
ninja -C build run_cow_test -j $(nproc)
```

For simplest program presented in `main.cpp` try run:

```bash
cmake -B build -GNinja
ninja -C build run_simplest
```

For memory leaks check, use this:

```bash
cmake -B build -GNinja -DSANITIZERS=1
ninja -C build run_simplest
```

