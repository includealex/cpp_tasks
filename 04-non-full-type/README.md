# 1. Task description:

We need to find out what is the reason of the fact that such a code compiles:

```c++
struct S; // Non-full type

template <typename T> struct Wrapper {
    T val;
};

void foo(const Wrapper<S>&) {}

Wrapper<S>& get();

int main() {
    (foo)(get()); // OK
}
```

But this code doesn't:
```c++
struct S; // Non-full type

template <typename T> struct Wrapper {
    T val;
};

void foo(const Wrapper<S>&) {}

Wrapper<S>& get();

int main() {
    foo(get()); // NOT OK
}
```

# 2. Standard study:

The behavior in these examples is supported by the C++ standard, which specifies rules for overload resolution and template instantiation.

`[basic.def.odr]`: This section states that if a type is incomplete where a complete type is required, such as in an instantiation context, the code is ill-formed. Here `get()` is odr-used. Without `()`, `foo(get())` directly instantiates `Wrapper<S>`, triggering a completeness requirement on `S`. 

Quotation with odr-used example:
```c++
auto f() {
    struct A {};
    return A{};
}

decltype(f()) g();
auto x = g();
```
_A program containing this translation unit is ill-formed because g is odr-used but not defined, and cannot be defined in any other translation unit because the local class A cannot be named outside this translation unit_.


`[expr.prim.id.unqual]`: Unqualified names in C++ (like foo in this case) are treated differently based on their usage context. Such an additional parentheses: `foo`->`(foo)` changes current context by making `(foo)` an immediate expression, this results in the need of completeness to be checked.

`[temp.inst]`: This section specifies that template instantiation _requires a completely-defined object type_ if any member of the template depends on that type. That is why when we call `foo(get())`, we check for `Wrapper<S>`, which requires `S` to be completed:
```c++
foo(get()) -> Wrapper<S> -> S -> non-full type -> compilation error -> sadness
```

That is why second example is broken.

