#include <iostream>
#include <vector>

extern int yyparse();
extern std::vector<int> memory;

int main() {
    for (int i = 0; i < memory.size(); ++i) {
        memory[i] = i * 2;
    }

    std::cout << "Welcome to the [RAM Interpreter!" << std::endl;
    yyparse();
    return 0;
}

