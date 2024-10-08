%{
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<int> memory(1000);
std::map<std::string, int> variables;

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
%token IDENTIFIER

%union {
    int ival;
    char* sval;
}

%type <ival> expression term
%type <sval> IDENTIFIER

%precedence ASSIGN
%precedence PLUS MINUS

%% 

program:
    program statement SEMICOLON
    |
    ;

statement:
    input_s
    | assignment_s
    | print_s
    ;

input_s:
    INPUT L_BRACKET {
        input(c);
    }
    | INPUT R_BRACKET L_BRACKET {
        input(x);
    }
    | INPUT IDENTIFIER {
        input(variables[$2]);
    }

print_s:
    PRINT expression { 
        print($2);
    }
    | PRINT L_BRACKET expression R_BRACKET {
        print(memory[$3]);
    }
    | PRINT IDENTIFIER L_BRACKET expression R_BRACKET {
        print(memory[variables[$2] + $4]);
    }

assignment_s:
    L_BRACKET ASSIGN expression {
        c = $3;
    }
    | L_BRACKET ASSIGN L_BRACKET expression R_BRACKET {
        c = memory[$4];
    }
    | L_BRACKET ASSIGN IDENTIFIER L_BRACKET expression R_BRACKET {
        c = memory[variables[$3] + $5];
    }
    | R_BRACKET L_BRACKET ASSIGN expression {
        x = $4;
    }
    | R_BRACKET L_BRACKET ASSIGN L_BRACKET expression R_BRACKET {
        x = memory[$5];
    }
    | R_BRACKET L_BRACKET ASSIGN IDENTIFIER L_BRACKET expression R_BRACKET {
        x = memory[variables[$4] + $6];
    }
    | IDENTIFIER ASSIGN expression {
        variables[$1] = $3;
    }
    | IDENTIFIER ASSIGN L_BRACKET expression R_BRACKET {
        variables[$1] = memory[$4];
    }
    | IDENTIFIER ASSIGN IDENTIFIER L_BRACKET expression R_BRACKET {
        variables[$1] = (memory[variables[$3] + $5]);
    }

expression:
    term {
        $$ = $1;
    }
    | expression PLUS term {
        $$ = $1 + $3;
    }
    | expression MINUS term {
        $$ = $1 - $3;
    }
    ;

term:
    NUMBER {
        $$ = $1;
    }
    | L_BRACKET {
        $$ = c;
    }
    | R_BRACKET L_BRACKET {
        $$ = x;
    }
    | IDENTIFIER {
        $$ = variables[$1];
    }
    ;

%% 

void yyerror(const char* s) {
    std::cerr << "Error: " << s << std::endl;
}

