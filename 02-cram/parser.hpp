#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

#define INPUT 1
#define PRINT 2
#define NUMBER 3
#define IDENTIFIER 4
#define L_BRACKET 5
#define R_BRACKET 6
#define PLUS 7
#define MINUS 8
#define ASSIGN 9
#define SEMICOLON 10

extern int yylval_int;
extern std::string yysval;

int yyparse();

#endif // PARSER_HPP

