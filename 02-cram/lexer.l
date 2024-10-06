%{
#include "parser.tab.h"
#include <iostream>
%}

%%

input        { return INPUT; }
print        { return PRINT; }
[0-9]+       { yylval.ival = atoi(yytext); return NUMBER; }
"["          { return C_VAR; }   // Return C_VAR for [
"]"          { /* Do nothing here; handled by X_VAR */ }
"][ "        { return X_VAR; }   // Return X_VAR for ][
"+"          { return PLUS; }
"-"          { return MINUS; }
"="          { return ASSIGN; }
";"          { return SEMICOLON; }
[ \t\n]      { /* Skip whitespace */ }

%%

int yywrap() {
    return 1;
}
