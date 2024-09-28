#include <iostream>
#include <string>

#include "comp_operator.hpp"

int main() {
    std::basic_string<char> str1 = "Hello";
    std::basic_string<char> str2 = "Hello";
    std::basic_string<char> str3 = "World";


    if (custom::operator==(str1, str2)) {
        std::cout << "str1 and str2 are equal" << std::endl;
    } else {
        std::cout << "str1 and str2 are not equal" << std::endl;
    }

    if (custom::operator==(str1, str3)) {
        std::cout << "str1 and str3 are equal" << std::endl;
    } else {
        std::cout << "str1 and str3 are not equal" << std::endl;
    }

    return 0;
}
