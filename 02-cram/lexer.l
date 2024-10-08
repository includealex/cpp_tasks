%{
#include "parser.tab.h"
#include <iostream>
%}

%%

input        { return INPUT; }
print        { return PRINT; }
[0-9]+       { yylval.ival = atoi(yytext); return NUMBER; }
"["          { return L_BRACKET; }
"]"          { return R_BRACKET; }
"+"          { return PLUS; }
"-"          { return MINUS; }
"="          { return ASSIGN; }
";"          { return SEMICOLON; }
[ \t\n]      { /* Skip whitespace */ }

%%

int yywrap() {
    return 1;
}

