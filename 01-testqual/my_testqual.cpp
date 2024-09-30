#include "my_testqual.hpp"

// replaces `const char' with `char const'
void const_char_to_char_const(std::vector<int>& vec) {
    if (vec.size() <= 1) {
        std::cout << "Tried to work via many-elemented array when it was single-elemented." << std::endl;
        return;
    }

    if (vec[0] == token_type::CONST and vec[1] == token_type::CHAR) {
        std::swap(vec[0], vec[1]);
    }
}

std::vector<int> parse_str(const std::string& input) {
    std::vector<int> res;

    my_lexer lexer(input);
    int token = lexer.getNextToken();
    while (token != token_type::END) {
        res.push_back(token);
        token = lexer.getNextToken();
    }

    if (res.size() >= 1) {
        const_char_to_char_const(res);
    }

    return res;
}

bool inadequate_U(std::vector<int>& vec) {
    auto u_num = std::count(vec.begin(), vec.end(), token_type::CHAR);
    if (u_num != 1) {
        std::cout << "Given string contains " << u_num << " chars, that's unexpected." << std::endl;
        return true;
    }

    return false;
}

bool doubled_const(std::vector<int>& vec) {
    for (auto i = 1; i < vec.size(); ++i) {
        if (vec[i] == token_type::CONST && vec[i-1] == token_type::CONST) {
            std::cout << "String contains doubled+ const one after another, that's unexpected." << std::endl;
            return true;
        }
    }

    return false;
}

bool bad_brackets(std::vector<int>& vec) {
    int idx = 0;
    auto vec_sz = vec.size();
    while (vec[idx] != token_type::BRACKETS) {
        ++idx;
        if (idx == vec_sz) {
            return false;
        }
    }

    for (auto i = idx; i < vec_sz; ++i) {
        if (vec[i] != token_type::BRACKETS) {
            std::cout << "String contains bad brackets inside, that's unexpected." << std::endl;
            return true;
        }
    }

    return false;
}

bool type_checker(std::vector<int>& vec) {
    if (inadequate_U(vec)) {
        return true;
    }

    if (doubled_const(vec)) {
        return true;
    }

    if (bad_brackets(vec)) {
        return true;
    }

    return false;
}

bool n_pointers_differ(std::vector<int>& vec1, std::vector<int>& vec2) {
    auto count_p = [] (int i) {
        return (i == token_type::STAR || i == token_type::BRACKETS);
    };
    auto p1_num = std::count_if(vec1.begin(), vec1.end(), count_p);
    auto p2_num = std::count_if(vec2.begin(), vec2.end(), count_p);
    if (p1_num != p2_num) {
        return true;
    }

    return false;
}

std::vector<int> get_cv(std::vector<int>& vec) {
    std::vector<int> res;

    auto vec_sz = vec.size();
    for (int i = vec_sz - 1; i >= 0; --i) {
        auto cur_el = vec[i];
        if (cur_el == token_type::STAR || cur_el == token_type::BRACKETS || cur_el == token_type::CHAR) {
            if (i + 1 < vec_sz) {
                if (vec[i+1] == token_type::CONST) {
                    res.push_back(cv_type::CNST);
                    continue;
                }
            }

            res.push_back(cv_type::EMPT);
        }
    }

    return res;
}

bool check_cv(std::vector<int>& vec1, std::vector<int>& vec2) {
    auto res1 = get_cv(vec1);
    auto res2 = get_cv(vec2);

    for (size_t i = 0; i < vec1.size(); ++i) {
        std::cout << vec1[i] << std::endl;
    }

    if (res1.size() != res2.size()) {
        std::cout << "Something wrong with cv_qualifiers number" << std::endl;
        return false;
    }

    auto j = 1;
    for (auto i = 1; i < res1.size(); ++i) {
        if (res1[i] != res2[i]) {
            for (; j < i; ++j) {
                if (res1[j] != cv_type::CNST) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool check_right_brackets(std::vector<int>& vec) {
    auto it = std::find(vec.rbegin(), vec.rend(), token_type::BRACKETS);
    if (it != vec.rend()) {
        return true;
    }

    return false;
}

bool check_const_left_brackets(std::vector<int>& vec) {
    if (vec.size() < 3) {
        return false;
    }
    
    auto it = std::find(vec.rbegin(), vec.rend(), token_type::BRACKETS);
    if (it != vec.rbegin()) {
        return false;
    }

    int secondLast = vec[vec.size() - 2];
    if (secondLast != token_type::CONST) {
        return false;
    }

    return true;
}

bool check_qualcomb(std::vector<int>& vec1, std::vector<int>& vec2) {
    if (check_const_left_brackets(vec1)) {
        std::cout << "here" << std::endl;
        return false;
    }

    if (check_right_brackets(vec2)) {
        return false;
    }

    if (type_checker(vec1) || type_checker(vec2)) {
        return false;
    }

    if (n_pointers_differ(vec1, vec2)) {
        return false;
    }

    return check_cv(vec1, vec2);
}

bool my_testqual(const std::string& str1, const std::string& str2) {
    auto vec1 = parse_str(str1);
    auto vec2 = parse_str(str2);

    return check_qualcomb(vec1, vec2);
}

