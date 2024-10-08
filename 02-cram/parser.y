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
%token L_BRACKET R_BRACKET

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
    INPUT L_BRACKET { input(c); }
    | INPUT R_BRACKET L_BRACKET { input(x); }
    | L_BRACKET ASSIGN expression {
        c = $3;
    }
    | R_BRACKET L_BRACKET ASSIGN expression {
        x = $4;
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
    | L_BRACKET { $$ = c; }
    | R_BRACKET L_BRACKET { $$ = x; }
    ;

%% 

void yyerror(const char* s) {
    std::cerr << "Error: " << s << std::endl;
}

