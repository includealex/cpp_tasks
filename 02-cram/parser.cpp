#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

#include "parser.hpp"

int yylval_int;
std::string yysval;

extern int yylex();
extern void yyerror(const char*);

extern std::vector<int> memory;

// TODO: match variables with memory
std::unordered_map<std::string, int> variables;

static int lookahead_token = 0;
int get_next_token() {
    if (lookahead_token != 0) {
        int token = lookahead_token;
        lookahead_token = 0;
        return token;
    } else {
        return yylex();
    }
}

void unget_token(int token) {
    lookahead_token = token;
}

int evaluate_expression();

void input_command() {
    int token = get_next_token();
    if (token == L_BRACKET) {
        int addr = evaluate_expression();

        if (get_next_token() != R_BRACKET) {
            yyerror("Expected closing bracket");
            return;
        }

        if (get_next_token() != SEMICOLON) {
            yyerror("Expected semicolon after memory access in input");
            return;
        }

        token = get_next_token();
        if (token == NUMBER) {
            if (addr >= 0 && addr < memory.size()) {
                memory[addr] = yylval_int;
                std::cout << "Memory[" << addr << "] set to " << yylval_int << std::endl;
            }
            else {
                yyerror("Memory address out of bounds");
            }
        }
        else {
            yyerror("Expected a number after memory address in input");
        }
    }
    else if (token == IDENTIFIER) {
        std::string var_name = yysval;

        if (get_next_token() != SEMICOLON) {
            yyerror("Expected semicolon after variable name in input");
            return;
        }

        token = get_next_token();
        if (token == NUMBER) {
            variables[var_name] = yylval_int;
        }
        else {
            yyerror("Expected a number after variable name in input");
        }
    }
    else {
        yyerror("Expected memory address or variable name after input");
    }
}

void print_command() {
    int token = get_next_token();
    if (token == L_BRACKET) {
        int base = evaluate_expression();

        if (get_next_token() != R_BRACKET) {
            yyerror("Expected closing bracket");
            return;
        }
        if (base >= 0 && base < memory.size()) {
            std::cout << memory[base] << std::endl;
        }
        else {
            yyerror("Memory address out of bounds");
        }
    }
    else if (token == IDENTIFIER) {
        std::string var_name = yysval;
        token = get_next_token();

        if (token == L_BRACKET) {
            int offset = evaluate_expression();

            if (get_next_token() != R_BRACKET) {
                yyerror("Expected closing bracket after offset");
                return;
            }

            if (variables.find(var_name) != variables.end()) {
                int base = variables[var_name];
                int mem_addr = base + offset;

                if (mem_addr >= 0 && mem_addr < memory.size()) {
                    std::cout << memory[mem_addr] << std::endl;
                }
                else {
                    yyerror("Memory address out of bounds");
                }
            }
            else {
                yyerror("Undefined variable as base in expression");
            }
        }
        else {
            unget_token(token);
            if (variables.find(var_name) != variables.end()) {
                std::cout << variables[var_name] << std::endl;
            }
            else {
                yyerror("Undefined variable");
            }
        }
    }
    else {
        yyerror("Expected memory address or variable name after print");
    }
}

void assignment_command() {
    std::string var_name = yysval;

    if (get_next_token() != ASSIGN) {
        yyerror("Expected '=' in assignment");
        return;
    }

    int value = evaluate_expression();
    variables[var_name] = value;
    std::cout << "Assigned " << value << " to variable " << var_name << std::endl;
}

int evaluate_expression() {
    int result;
    int token = get_next_token();

    if (token == NUMBER) {
        result = yylval_int;
    }

    // TODO: add here synonym!
    else if (token == IDENTIFIER) {
        std::string var_name = yysval;
        if (variables.find(var_name) != variables.end()) {
            result = variables[var_name];
        }
        else {
            yyerror("Undefined variable in expression");
            result = 0;
        }
    }
    else {
        yyerror("Expected a number or variable in expression");
        return 0;
    }

    // Logic after variable entered.
    // Implemented in iterative way.
    token = get_next_token();
    if (token == PLUS) {
        int rhs = evaluate_expression();
        result += rhs;
    }
    else if (token == MINUS) {
        int rhs = evaluate_expression();
        result -= rhs;
    }
    else {
        unget_token(token);
    }

    return result;
}

void yyerror(const char* s) {
    std::cerr << "Error: " << s << std::endl;
}

int yyparse() {
    int token;
    while ((token = get_next_token())) {
        switch (token) {
            case INPUT:
                input_command();
                break;
            case PRINT:
                print_command();
                break;

            // TODO: Identifier can be a synonym!
            case IDENTIFIER:
                assignment_command();
                break;
            case SEMICOLON:
                break;
            default:
                yyerror("Unexpected token");
        }
    }
    return 0;
}

