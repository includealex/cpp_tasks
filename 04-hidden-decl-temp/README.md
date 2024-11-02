# 1. Question overview

```c++
template <typename T> struct A {
    using M = T;
    struct B { 
        using M = void; 
        struct C;
    };
};

template <typename T> struct A<T>::B::C : A<T> {
    M m;
};

int main() {
    A<int>::B::C x;
}
```

`gcc 14.2` and `clang 19.1` behave differently with this piece of code:

`gcc` output:
```sh
Compiler returned: 0
```

`clang` output:
```sh
<source>:10:7: error: field has incomplete type 'M' (aka 'void')
   10 |     M m; // void or int?
      |       ^
1 error generated.
Compiler returned: 1
```

As we can see, `gcc` refers to `M` as to `integer`, while `clang` sees `void`.

**Why? Who is correct?**


# 2. Standard study.

Taken look into `[basic.lookup.qual]`, we understand, why does reimplementing our program without templates will return type which was specified in the string `using M = T` in the outer loop.

Quotations:

_Unless otherwise specified, a qualified name undergoes qualified name lookup in its lookup context from the point where it appears unless the lookup context either **is dependent** and is not the current instantiation (13.8.3.2) or is not a class or **class template**_.

Shadowing example:

```c++
struct Outer {
    using Type = int;
    struct Inner {
        using Type = double; // Shadows Outer::Type
        void func() {
            Type var = 3.14; // Refers to Inner::Type (double)
        }
    };
};
```

Sections `[temp.inst]` and `[temp.dep]` both provide details on how names in templates are looked up in phases. Clarification is that during instantiation, names within a dependent base class (like `A<T>`) are only considered if they are not **hidden by declarations in the derived class** (here, `B::C`). Thus, `M` is resolved within `B` as `void` before any consideration of `A<T>::M` (which would be `int`). Since `B::M` exists, it hides `A<T>::M`, so `M` in `C` will resolve to void.

# 3. Conclusion

According to the standard, we see that in this question `clang` is right.

