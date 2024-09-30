%option noyywrap

%{

#include <iostream>
#include <string>

#include "token_type.hpp"

%}

%%

[ \r\n\t]+ { }
"char"  { return token_type::CHAR; }
"const" { return token_type::CONST; }
"\*"    { return token_type::STAR; }
"\[\]"  { return token_type::BRACKETS; }
.       { std::cerr << "Incorrect symbol entered '" << *yytext << "'" << std::endl; exit(1); }
<<EOF>> { return token_type::END; }

%%

static YY_BUFFER_STATE buffer;

void scan_string(const char* str) {
    yy_switch_to_buffer(buffer);
    buffer = yy_scan_string(str);
}

void delete_buff() {
    yy_flush_buffer(buffer);
    yy_delete_buffer(buffer);
    buffer = 0;
}
