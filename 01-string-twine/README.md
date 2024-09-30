For simlest example, run:

```bash

cmake -B build -GNinja
ninja -C build run_simplest

```

For memory leaks check, add flag `-DSANITIZERS=1`

For tests run:

```bash

cmake -B build -GNinja
ninja -C build run_string_twine_test

```
