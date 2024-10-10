#include "parser.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "globals.h"  // Globals are already defined here

// Global variables from lexer
int current_token;   // Stores the current token
int yylval_int;      // For holding integer token values (defined here)
char* yysval;        // For holding identifier token values (defined here)

// Memory and synonyms
// No need to define or initialize memory, c, or x here as they are in globals.cpp

// Move to the next token
void advance_token() {
    current_token = yylex(); // Call the lexer to get the next token
}
// Function to report an error
void yyerror(const char *s) {
    std::cerr << "Error: " << s << std::endl;
    exit(1);
}

// Function to parse the entire program
void parse_program() {
    while (current_token != 0) { // 0 is EOF
        parse_statement();
    }
}

// Function to parse individual statements
void parse_statement() {
    if (current_token == INPUT) {
        // Input statement: input a;
        advance_token();
        if (current_token != IDENTIFIER) yyerror("Expected identifier after 'input'");
        advance_token();
        if (current_token != SEMICOLON) yyerror("Expected ';' after input");
        advance_token();

        // Simulate reading input into memory
        int value;
        std::cin >> value;
        std::cout << "Input value: " << value << std::endl;
        memory[5] = value;  // Just for testing, assigning input to memory[5]

    } else if (current_token == PRINT) {
        // Print statement: print a; or print [8];
        advance_token();

        if (current_token == IDENTIFIER) {
            // Print a variable, like print a;
            std::string var_name = yysval;
            advance_token();
            if (current_token != SEMICOLON) yyerror("Expected ';' after print");
            advance_token();

            if (var_name == "a") {
                std::cout << "Print: " << memory[5] << std::endl;  // Assuming a is memory[5]
            } else {
                yyerror("Unknown variable to print");
            }

        } else if (current_token == L_BRACKET) {
            // Print a memory value, like print [8];
            advance_token();
            int index = parse_expr();  // Get the index for memory access
            if (current_token != R_BRACKET) yyerror("Expected ']' after memory index");
            advance_token();
            if (current_token != SEMICOLON) yyerror("Expected ';' after print memory access");
            advance_token();

            if (index >= 0 && index < memory.size()) {
                std::cout << "Print: " << memory[index] << std::endl;
            } else {
                yyerror("Memory index out of bounds");
            }

        } else {
            yyerror("Expected identifier or '[' after 'print'");
        }

    } else if (current_token == IDENTIFIER) {
        // Handle variable assignments and memory assignments
        std::string var_name = yysval;  // Store the identifier (e.g., "a")
        advance_token();
        
        if (current_token == L_BRACKET) {
            // Handle array assignment like a[5] = ...
            advance_token();
            int index = parse_expr();  // Get index inside []
            if (current_token != R_BRACKET) yyerror("Expected ']' after index");
            advance_token();
            
            if (current_token != ASSIGN) yyerror("Expected '=' after memory access");
            advance_token();
            int value = parse_expr();  // Parse the right-hand side expression
            if (current_token != SEMICOLON) yyerror("Expected ';' after assignment");
            advance_token();
            
            // Assign the value to memory
            memory[index] = value;

        } else if (current_token == ASSIGN) {
            // Handle direct assignment like a = [6];
            advance_token();
            int value = parse_expr();  // Parse the right-hand side expression
            if (current_token != SEMICOLON) yyerror("Expected ';' after assignment");
            advance_token();
            
            // Handle direct assignment to a variable (in this case, 'a')
            if (var_name == "a") {
                memory[5] = value;  // Example: assign to memory[5] for variable 'a'
            } else {
                yyerror("Unknown variable");
            }

        } else {
            yyerror("Expected '=' or '[' after variable");
        }

    } else {
        yyerror("Unexpected statement");
    }
}


// Function to parse expressions (numbers, memory accesses, and arithmetic)
int parse_expr() {
    int value;
    if (current_token == NUMBER) {
        value = yylval_int; // Store the number value
        advance_token();
    } else if (current_token == L_BRACKET || current_token == IDENTIFIER) {
        value = parse_mem_access(); // Parse a memory access
    } else {
        yyerror("Expected expression");
    }

    // Handle addition or subtraction
    while (current_token == PLUS || current_token == MINUS) {
        int op = current_token;
        advance_token();
        int next_value = parse_expr();
        if (op == PLUS) value += next_value;
        else if (op == MINUS) value -= next_value;
    }

    return value;
}

// Function to parse memory access patterns
int parse_mem_access() {
    if (current_token == L_BRACKET) {
        advance_token();
        int address = parse_expr(); // Inside the brackets
        if (current_token != R_BRACKET) yyerror("Expected ']' after memory access");
        advance_token();
        return address;
    } else if (current_token == IDENTIFIER) {
        if (strcmp(yysval, "a") == 0) {
            advance_token();
            if (current_token != L_BRACKET) yyerror("Expected '[' after 'a'");
            advance_token();
            int address = parse_expr(); // Index inside the array
            if (current_token != R_BRACKET) yyerror("Expected ']' after array index");
            advance_token();
            return address;
        }
    }

    yyerror("Invalid memory access");
    return 0; // Dummy return
}
