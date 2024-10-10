%{
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "parser.hpp"

%}

%%

input                { return INPUT; }
print                { return PRINT; }
[0-9]+               { yylval_int = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9]* { yysval = strdup(yytext); return IDENTIFIER; }
"["                  { return L_BRACKET; }
"]"                  { return R_BRACKET; }
"+"                  { return PLUS; }
"-"                  { return MINUS; }
"="                  { return ASSIGN; }
";"                  { return SEMICOLON; }
[ \t\n]              { /* Skip whitespace */ }

%%

int yywrap() {
    return 1;
}

