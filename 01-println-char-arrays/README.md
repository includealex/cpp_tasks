
# 1. Question overview

This is a simplest view on `println` in `c++23` questions. Firstly, we know this signature:

```c
template<class... Args>
void println(format_string<Args...> fmt, Args&&... args);

template<class... Args>
void println(FILE* stream, format_string<Args...> fmt, Args&&... args);
```

Case of using `println` in simplest program:

```c
#include <cstring>
#include <iostream>
#include <print>

int main() {
    char Hello[20];
    strcpy(Hello, "Hello, world!");

    std::cout << Hello << std::endl; // Hello, world!
    std::println("{0}", Hello);      // Hello, world! + garbage out?
    std::println("{0}", +Hello);     // Hello, world!
}
```

The case question is **if it really gives garbage out** or not and **why**?

# 2. Standard study

Briefly from `c++23 standard`: 

- Mentioned in `31.7.6.3.5 Print`:

```c
template<class... Args>
void println(ostream& os, format_string<Args...> fmt, Args&&... args);

// Equivalent to:
print(os, "{}\n", format(fmt, std::forward<Args>(args)...));
```

- Mentioned in `31.7.10 Print functions`:

```c
template<class... Args>
void println(format_string<Args...> fmt, Args&&... args);
// Equivalent to:
println(stdout, fmt, std::forward<Args>(args)...);


template<class... Args>
void println(FILE* stream, format_string<Args...> fmt, Args&&... args);
// Equivalent to:
print(stream, "{}\n", format(fmt, std::forward<Args>(args)...));
```

# 3. Result

## 3.1 theoretical
Knowing these equivalents, we can take a look into our example from the `1.`. Given `const char*` will be fromatted to `fmt` via `format_strings` function. All the inapropriate characters will not be printed out.

Expected theoretical output:

```bash
Hello, world!
Hello, world!
Hello, world!
```

## 3.2 practical

Running this simplest case with the trunk `gcc` version  and `-std=c++23 -O3` flags gives this output:

```bash
Hello, world!
Hello, world!
Hello, world!
```

As we can see, there is no garbage out. `const char*` will be formatted and printed without any garbage information.

