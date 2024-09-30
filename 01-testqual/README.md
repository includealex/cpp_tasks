`01-testqual` run command to run simplest example from the slide:

```bash
make run_simplest
```

`01-testqual` to have binary working with `argc` as given arguments:

```bash
make tq.out
./tq.out "const char **" "char **"
```

For generated tests run, use (takes approximately less than a minute):

```bash
make test_generated
```

In this task such a function should be written, that checks if conversion can be done for different types.
Types are presented as strings that can include `const`, `char`, `[]` and `*`.

My examples:
 - my_testqual("const char **", "char **") // -> false
 - my_testqual("const char **", "const char * const *") // -> true
 - my_testqual("char const**", "const char **") // -> true

Useful info to read:
- Blog with cv briefly to read:
    https://blog.panicsoftware.com/qualification-conversion/
- Spiral rule:
    https://c-faq.com/decl/spiral.anderson.html
- Reading inside-out:
    https://stackoverflow.com/questions/34548762/c-isnt-that-hard-void-f/34560439#34560439
- Declarations mirror use:
    https://stackoverflow.com/questions/34548762/c-isnt-that-hard-void-f/34552915#34552915

