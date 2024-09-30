#ifndef MY_TESTQUAL_HPP_
#define MY_TESTQUAL_HPP_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "my_lexer.hpp"

enum cv_type {
    EMPT = 0,
    CNST = 1
};

bool my_testqual(const std::string& str1, const std::string& str2);

#endif //MY_TESTQUAL_HPP_
