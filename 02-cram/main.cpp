#include <iostream>
#include <vector>

#include "parser.hpp"

std::vector<int> memory(100);

int main() {
    for (int i = 0; i < memory.size(); ++i) {
        memory[i] = i * 2;
    }

    std::cout << "Welcome to the [RAM Interpreter!" << std::endl;
    yyparse();
    return 0;
}

