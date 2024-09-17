#ifndef MY_LEXER_HPP_
#define MY_LEXER_HPP_

#include <string>
#include <type_traits>
#include <vector>

#include "token_type.hpp"

extern int yylex_destroy();
extern int yylex(void);
extern void scan_string(const char* str);
extern void delete_buff();

class my_lexer final {
 public:
    my_lexer(const std::string& input) : input_(input) {
        scan_string(input_.c_str());
    }

    int getNextToken() {
        return yylex();
    }

    ~my_lexer() {
        delete_buff();
        yylex_destroy();
    }
 private:
    std::string input_;
};

#endif // MY_LEXER_HPP_
