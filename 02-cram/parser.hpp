#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>

// Token definitions
enum Token {
    INPUT, PRINT, NUMBER, IDENTIFIER, L_BRACKET, R_BRACKET,
    PLUS, MINUS, ASSIGN, SEMICOLON, END
};

// Declare global variables to store the current token values
extern int yylval_int;   // For integer values from the lexer (declared as extern)
extern char* yysval;     // For identifier string values from the lexer (declared as extern)

// Declare external functions from the lexer and parser
extern int yylex();
extern int current_token;
void parse_program();
void parse_statement();
int parse_expr();
int parse_mem_access();

// Memory and synonym variables
extern std::vector<int> memory;
extern int c; // Base address synonym
extern int x; // Offset synonym

// Error reporting
void yyerror(const char *s);
void advance_token();

#endif

