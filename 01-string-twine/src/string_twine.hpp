#ifndef STRING_TWINE_HPP_
#define STRING_TWINE_HPP_

/*
    What is basic_string?
    template <typename CharT> class basic_string {
     private:
        CharT *data;
        size_t size;
        union {
            size_t capacity;
            enum {SZ = (sizeof(data) + 2 * sizeof(size_t) + 31) / 32};
            CharT small_str[SZ];
        } sso;
     public:
        // 89 methods
    };

    Expected program to work:
    std::string_view sv = "Hello,";
    std::string_view sv2 = "World!";

    auto s = custom::string_twine(sv, " ", sv2).to_str();
    std::cout << s << std::endl;

    to_str() method works not only with `std::string_view', but
    also with `char*' type.

*/

#include <iostream>
#include <string>
#include <string_view>
#include <memory>

namespace custom {

// O(log N) concatenation via binary tree implementation
class string_twine {
 public:
    explicit string_twine(std::string_view s) : _left(nullptr), _right(nullptr), _str(s), _size(s.size()) {}

    string_twine(const string_twine& lhs, const string_twine& rhs)
        :  _left(std::make_shared<string_twine>(lhs)),
          _right(std::make_shared<string_twine>(rhs)),
          _size(lhs.size() + rhs.size()) {}

    template <typename... ArgsT>
    string_twine(ArgsT&&... args) {
        *this = _rec_concat(std::forward<ArgsT>(args) ...);
    }

    size_t size() const {
        return _size;
    }

    std::string to_str() const {
        std::string res;
        res.reserve(_size);
        _to_string(res);
        return res;
    }

 private:
    std::shared_ptr<string_twine> _left, _right;
    std::string_view _str;
    size_t _size = 0;

    void _to_string(std::string& res) const {
        if (_left && _right) {
            _left->_to_string(res);
            _right->_to_string(res);
        }
        else {
            res.append(_str);
        }
    }

    static string_twine _concat(const string_twine& lhs, const string_twine& rhs) {
        return string_twine(lhs, rhs);
    }

    template<typename FirstT, typename... RestT>
    static string_twine _rec_concat(FirstT&& first, RestT&&... rest) {
        return _concat(string_twine(std::forward<FirstT>(first)), _rec_concat(std::forward<RestT>(rest)...));
    }

    static string_twine _rec_concat(std::string_view last) {
        return string_twine(last);
    }

    static string_twine _rec_concat(const char* last) {
        return string_twine(std::string_view(last));
    }

};

} // namespace custom

#endif // STRING_TWINE_HPP_

