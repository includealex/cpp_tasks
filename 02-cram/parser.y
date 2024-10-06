%{
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

std::vector<int> memory(1000);

int c = 0; // is  [ synonym
int x = 0; // is ][ synonym

int input_var = 0;

void input(int& var) {
    std::cin >> var;
}

void print(int var) {
    std::cout << var << std::endl;
}

int yylex();
void yyerror(const char* s);

%}

%token <ival> NUMBER 
%token INPUT PRINT PLUS MINUS ASSIGN SEMICOLON
%token C_VAR X_VAR

%union {
    int ival;
}

%type <ival> expression term

%precedence ASSIGN
%precedence PLUS MINUS

%% 

program:
    program statement SEMICOLON
    |
    ;

statement:
    INPUT C_VAR { input(c); }
    | INPUT X_VAR { input(x); }
    | C_VAR ASSIGN expression { 
        c = $3;
    }
    | X_VAR ASSIGN expression { 
        x = $3;
    }
    | PRINT expression { 
        print($2);
    }
    ;

expression:
    term { $$ = $1; }
    | expression PLUS term { $$ = $1 + $3; }
    | expression MINUS term { $$ = $1 - $3; }
    ;

term:
    NUMBER { $$ = $1; }
    | C_VAR { $$ = c; }
    | X_VAR { $$ = x; }
    ;

%% 

void yyerror(const char* s) {
    std::cerr << "Error: " << s << std::endl;
}

