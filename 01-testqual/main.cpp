#include <iostream>

#include "my_testqual.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Please, provide correct number of arguments." << std::endl;
        return 1;
    }

    const std::string str1 = argv[1];
    const std::string str2 = argv[2];

    auto result = my_testqual(str1, str2);
    std::cout << std::boolalpha << result << std::endl;

    return 0;
}

