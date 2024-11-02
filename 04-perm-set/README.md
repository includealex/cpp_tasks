This is a directory related to permanent set creation. This permanent set is based on the persistent tree.

For `strings` permanent set `string_twine` is used for better performance.

For project build, run:

```bash
cmake -B build -GNinja
ninja -C build run_permset_test -j$(nproc)
```

