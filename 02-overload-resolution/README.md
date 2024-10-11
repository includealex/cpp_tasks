# 1. Task description:

```cpp
#include <iostream>

struct Foo {};

struct Bar : Foo {};

struct Baz : Foo {};

struct X {
    operator Bar() { 
        std::cout << "Bar\n"; return Bar{};
    }
    operator Baz() const { 
        std::cout << "Baz\n"; return Baz{}; 
    }
};

void foo(const Foo &f) {}

int main() { 
    foo(X{}); // Bar or Baz?
}
```

What will be output?

# 2. Theory.

As far as we know about overloading rules:
1. A set of overloaded names is selected;
2. A set of candidates is selected;
3. From the set of candidates, viable candidates for the given overload are selected;
4. The best of the viable candidates is selected based on the chains of implicit conversions for each parameter;
5. If the best candidate exists and is unique, then the overload is resolved successfully, otherwise the program is ill-formed.

As far as we know obaout overload resolution candidates ranking:
1. Implicit conversion sequences (which conversion is required).
2. Qualification of functions (const vs. non-const).
3. Exact matches (which function is a better match for the given argument types).

In the given example:
- `operator Bar()` **non-const**
- `operator Baz()` **const-qualified**

Step-by-step:

1. Compiler decides, how to convert `X` into a type that is passed to the `foo`. These can be both `Bar` and `Baz`. They both are derivatives from `Foo`.

2. Then we choose between **non-const** and **const-qualified**. But we now that non-const conversion operators are preferred in overload resolution if applicable. Taken info from `12.2.4.2.2` and `[base.life]` we can assume that in this case preference has more general overload (it can apply to both const and non-const objects).

Thus expected output:
```
Bar
```

# 3. Practical check.

Ran with `x86-64gcc (trunk)`. Output was similar to theoretical:

```
Bar
```

