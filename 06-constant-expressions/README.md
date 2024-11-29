# 1. Question overview:

```c++
struct S {
    int : *new int{0};
};

enum E {
    V = *new int{1},
};
```

`gcc 14.2` and `clang 19.1` behave differently with this piece of code:

`clang` output:

```sh
Compiler returned: 0
```

`gcc` output:

```sh
<source>:2:19: error: call to non-'constexpr' function 'void* operator new(long unsigned int)'
    2 |   int : *new int{0};
      |                   ^
<built-in>: note: 'void* operator new(long unsigned int)' declared here
<source>:2:19: error: call to non-'constexpr' function 'void* operator new(long unsigned int)'
<built-in>: note: 'void* operator new(long unsigned int)' declared here
<source>:2:19: error: bit-field 'S::<anonymous>' width not an integer constant
<source>:6:17: error: call to non-'constexpr' function 'void* operator new(long unsigned int)'
    6 |   V = *new int{1},
      |                 ^
<built-in>: note: 'void* operator new(long unsigned int)' declared here
<source>:6:17: error: call to non-'constexpr' function 'void* operator new(long unsigned int)'
<built-in>: note: 'void* operator new(long unsigned int)' declared here
<source>:6:17: error: enumerator value for 'V' is not an integer constant
Compiler returned: 1
```

**Why? Who is right?**

# 2. Standard study.

The expression `int : *new int{0};` uses a dynamically allocated value as the bit-field width.

Let's TAL into `[class.bit] (11.4.10 Bit-fields)`, bit-field's **must be an ICE** (integral constant expression) with a value greater than or equal to zero. `[expr.const] (7.7 Constant expressions)` says info about ICE - it should consist of constant expressions. Thus `* new int{0}` should not be called constant expression.

Same for the enumerator. As it is mentioned in the `[dcl.enum] (9.7.1)`, `* new int{1}` should also be an ICE.

# 3. Conclusion

According to the arguments above, `gcc` is correct.

