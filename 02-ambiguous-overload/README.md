# 1. Task description:

We need to find out what is going on in such an example:

```cpp
template <class T1, class T2> struct Pair {
  template<class U1 = T1, class U2 = T2> 
  Pair(U1&&, U2&&) {}
};

struct S { 
    S() = default;
};

struct E {
    explicit E() = default;
};

int f(Pair<E, E>) {
    return 1;
}

int f(Pair<S, S>) {
    return 2;
}

static_assert(f({{}, {}}) == 2, ""); // Error or Assert or OK?

```

And to find out, what happens inside `static_assert`.

# 2. What is going on(theoretically)?

**FYI:** We have two almost similar overloads of `f` function.
```cpp
int f(Pair<E, E>) { // f1
    return 1;
}

int f(Pair<S, S>) { // f2
    return 2;
}
```

While calling `f({{}, {}})` the compiler tries to create the most suitable candidate to be constructed via `{}`.
It will try to choose between `f1` and `f2` mentioned above. But what should be chosen? Both constructors are equally valid (`explicit E()` constructor shouldn't frighten anybody, it can be used with direct initialisation). Thus it should lead to ambiguity and compilation failure.

# 3. Let's check practical result.

Compiler output(ran `x86-64 gcc(trunk)` with `-std=c++23`):
```
<Compilation failed>
<source>:22:16: error: call of overloaded 'f(<brace-enclosed initializer list>)' is ambiguous
   22 | static_assert(f({{}, {}}) == 2, ""); // Error or Assert or OK?
      |               ~^~~~~~~~~~
<source>:14:5: note: candidate: 'int f(Pair<E, E>)'
   14 | int f(Pair<E, E>) {
      |     ^
<source>:18:5: note: candidate: 'int f(Pair<S, S>)'
   18 | int f(Pair<S, S>) {
      |     ^
Compiler returned: 1
```

# 4. Is it all?

If we change `static_assert` call to
```
static_assert(f(Pair<S, S>{{}, {}}) == 2, "");
```
We'll still get an error `call to non-constexpr function`. Thus only after `constexpr addition` fixes program will work:

```cpp
template <class T1, class T2>
struct Pair {
    template<class U1 = T1, class U2 = T2>
    constexpr Pair(U1&&, U2&&) {}
};

struct S { constexpr S() = default; };
struct E { explicit constexpr E() = default; };

constexpr int f(Pair<E, E>) { return 1; }
constexpr int f(Pair<S, S>) { return 2; }

int main() {
    static_assert(f(Pair<S, S>{{}, {}}) == 2, "");
}
```


