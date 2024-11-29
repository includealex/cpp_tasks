# 1. Question overview:

```
struct Type {
    int a; const int& b;
    constexpr Type() : a(1), b(a) {}
};

constexpr auto get() { return Type(); }
constexpr Type t2 = get();
constexpr int c2 = t2.a;
```

`gcc 14.2` and `clang 19.1` behave differently with this piece of code:

`clang` output:

```sh
Compiler returned: 0
```

`gcc` output:

```sh
<source>:17:25: error: 'Type{1, ((const int&)(&<anonymous>.Type::a))}' is not a constant expression
   17 | constexpr Type t2 = get();
      |                         ^
Compiler returned: 1
```

**Why? Who is right?**

# 2. Standard study.

Taken from the `[expr.const]`, _An expression E is a core constant expression unless the evaluation of E... would evaluate on of the following ... a reference to a subobject of an object (or its complete object) that is not usable in constant expressions._

Having an info from `[dcl.constexpr]` a constant expression invoking a constexpr constructor must satisfy all the rules for a core constant expression during the evaluation of the constructor.

Thus in our case, constructor of `Type` will break inside the `get()` function due to the fact that `a` is not a constexpr, thus `b(a)` should throw compilation error.

# 3. Conclusion

According to the arguments above, `gcc` is correct.

