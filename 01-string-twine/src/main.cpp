#include <iostream>

#include "string_twine.hpp"

int main() {
    std::string_view sv = "Hello,";
    std::string_view sv2 = "World!";
    
    auto s = custom::string_twine(sv, " ", sv2).to_str();
    std::cout << "Twined string is: \"" << s << "\"" << std::endl;

    return 0;
}

