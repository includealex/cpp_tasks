This is a program that sorts a cortege of types usign `metal` metaprogramming library.

For `metal.hpp` installation, run:

```bash
aria2c https://github.com/brunocodutra/metal/releases/download/v2.1.4/metal.hpp -d includes/
```

For tests to be run:

```bash
cmake -B build -GNinja
ninja -C build run_physmul_test
```

