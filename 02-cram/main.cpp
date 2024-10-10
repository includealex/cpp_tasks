#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "globals.h"  // Include the global variables

void parse_statement(const std::string& statement, std::ifstream& input_file);
void handle_input(const std::string& var_name, std::ifstream& input_file);
void handle_print(const std::string& arg);

int main(int argc, char* argv[]) {
    // Check if input file is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.cram>" << std::endl;
        return 1;
    }

    // Open the input file
    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    // Initialize memory
    for (int i = 0; i < memory.size(); ++i) {
        memory[i] = i * 2;
    }

    std::cout << "Welcome to the [RAM Interpreter!" << std::endl;

    std::string line;
    while (std::getline(input_file, line)) {
        if (!line.empty() && line.back() == ';') {
            line.pop_back(); // Remove semicolon
        }

        if (line.empty()) {
            continue;
        }

        parse_statement(line, input_file);
    }

    input_file.close();
    return 0;
}


void parse_statement(const std::string& statement, std::ifstream& input_file) {
    std::istringstream iss(statement);
    std::string command;

    iss >> command; // Read the command (input/print)

    if (command == "input") {
        std::string var_name;
        iss >> var_name; // Read the variable name or memory access
        handle_input(var_name, input_file); // Pass the file stream to handle input
    } else if (command == "print") {
        std::string arg;
        iss >> arg; // Read what to print (variable or memory access)
        handle_print(arg);
    } else {
        std::cerr << "Error: Unknown command '" << command << "'." << std::endl;
    }
}

void handle_input(const std::string& var_name, std::ifstream& input_file) {
    int value;
    if (input_file >> value) { // Read the integer value from the input file
        if (var_name == "a") {
            memory[5] = value; // Example: assign to memory[5] for variable a
            std::cout << "Input value: " << value << std::endl;
        } else if (var_name == "[") {
            c = value; // Assign the input value to 'c' (which is synonymous with '[')
            std::cout << "Input value for [ (c): " << value << std::endl;
        } else if (var_name == "][") {
            x = value; // Assign the input value to 'x' (which is synonymous with '][')
            std::cout << "Input value for ][ (x): " << value << std::endl;
        } else {
            std::cerr << "Error: Unknown variable or synonym '" << var_name << "'." << std::endl;
        }
    } else {
        std::cerr << "Error: Expected integer after 'input " << var_name << "'." << std::endl;
    }

    // Clear the fail state and ignore the rest of the line after reading value
    input_file.clear();
    input_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void handle_print(const std::string& arg) {
    if (arg == "a") {
        std::cout << memory[5] << std::endl; // Print value stored in memory[5]
    } else if (arg == "[") {
        std::cout << memory[c] << std::endl; // Print value stored at memory[c]
    } else if (arg == "][") {
        std::cout << memory[x] << std::endl; // Print value stored at memory[x]
    } else if (arg[0] == '[' && arg.back() == ']') {
        // Handle memory access like [8]
        try {
            int index = std::stoi(arg.substr(1, arg.size() - 2)); // Extract the index
            if (index >= 0 && index < memory.size()) {
                std::cout << memory[index] << std::endl; // Print the memory value
            } else {
                std::cerr << "Error: Memory index out of bounds." << std::endl;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid memory index." << std::endl;
        }
    } else {
        std::cerr << "Error: Invalid argument for print." << std::endl;
    }
}
