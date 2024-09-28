#include <iostream>
#include <string>
#include <memory>  // For custom allocators
#include "comp_operator.hpp"

int main() {
    std::basic_string<char> str1 = "Hello";
    
    using CustomAllocator = std::allocator<char>;
    std::basic_string<char, std::char_traits<char>, CustomAllocator> str2("Hello", CustomAllocator());

    using CustomTraits = std::char_traits<char>;
    std::basic_string<char, CustomTraits, std::allocator<char>> str3("World");

    if (custom::operator==(str1, str2)) {
        std::cout << "str1 and str3 are equal" << std::endl;
    } else {
        std::cout << "str1 and str3 are not equal" << std::endl;
    }

    if (custom::operator==(str1, str3)) {
        std::cout << "str1 and str4 are equal" << std::endl;
    } else {
        std::cout << "str1 and str4 are not equal" << std::endl;
    }

    return 0;
}

