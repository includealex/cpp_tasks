#ifndef MY_STR_COW_HPP_
#define MY_STR_COW_HPP_

#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

namespace COW {

template<typename CharT>
class my_str_COW final {
 public:
    my_str_COW() : _begin{0}, _end{0}, _buff{std::make_shared<storage>(1)} {
        (*_buff)[0] = '\0';  // null-terminate empty cow string
    }

    template<std::size_t N>
    explicit my_str_COW (const CharT (&str)[N]) : _begin{0}, _end{N - 2}, _buff{std::make_shared<storage>(N)} {
        std::copy(str, str + (N - 1), _buff->begin());
        (*_buff)[N - 1] = '\0';  // append the null terminator
    }

    my_str_COW(const my_str_COW& other) : _begin{other._begin}, _end{other._end}, _buff{other._buff} {};

    my_str_COW(my_str_COW&& other) noexcept : _begin{other._begin}, _end{other._end}, _buff{std::move(other._buff)} {
        other._begin = 0;
        other._end = 0;
    }

    my_str_COW& operator=(const my_str_COW& other) {
        if (this != &other) {
            _buff = other._buff;
            _begin = other._begin;
            _end = other._end;
        }

        return *this;
    }

    my_str_COW& operator=(my_str_COW&& other) noexcept {
        if (this != &other) {
            _buff = std::move(other._buff);
            _begin = other._begin;
            _end = other._end;

            other._begin = 0;
            other._end = 0;
        }

        return *this;
    }

    ~my_str_COW() = default;

    std::size_t offset() const {
        return _begin;
    }

    std::size_t size() const {
        return _end - _begin + 1;  // size does not include the null terminator
    }

    CharT operator[](std::size_t index) const {
        _validate_index(index);
        return (*_buff)[index + offset()];
    }

    CharT& operator[](std::size_t index) {
        _detach();
        _validate_index(index);
        return (*_buff)[index + offset()];
    }

    my_str_COW substr(std::size_t begin, std::size_t end) const {
        if (begin > end || begin < 0 || end >= size()) {
            throw std::out_of_range("Invalid range for substring");
        }

        begin += offset();
        end += offset();
        return my_str_COW(_buff, begin, end);
    }

    void* cur_addr() const {
        if (!_buff || offset() < 0 || offset() >= _buff->size()) {
            throw std::out_of_range("Offset is out of bounds");
        }
        return static_cast<void*>(&_buff->at(offset()));
    }

    my_str_COW concat(const my_str_COW& other) const {
        std::size_t new_size = size() + other.size();
        auto new_buff = std::make_shared<storage>(new_size + 1);  // +1 for null terminator

        std::copy(_buff->begin() + offset(), _buff->begin() + offset() + size(), new_buff->begin());
        std::copy(other._buff->begin() + other.offset(), other._buff->begin() + other.offset() + other.size(), new_buff->begin() + size());

        (*new_buff)[new_size] = '\0';  // Null-terminate

        return my_str_COW(new_buff, 0, new_size - 1);
    }

    std::vector<std::size_t> search(const my_str_COW& substr) const {
        std::vector<std::size_t> result;

        if (substr.size() > size()) {
            throw std::out_of_range("Substring is longer than the string.");
        }

        const my_str_COW<CharT> dollar_sign {"$"};
        auto pre_str = substr.concat(dollar_sign);

        auto concat_str = pre_str.concat(*this);
        std::vector<std::size_t> z(concat_str.size(), 0);
        std::size_t l = 0, r = 0;

        for (std::size_t i = 1; i < concat_str.size(); ++i) {
            if (i <= r) {
                z[i] = std::min(r - i, z[i - l]);
            }

            while (i + z[i] < concat_str.size() && concat_str[i + z[i]] == concat_str[z[i]]) {
                ++z[i];
            }

            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }

            if (z[i] == substr.size()) {
                result.push_back(i - substr.size() - 1);
            }
        }

        if (result.empty()) {
            std::cout << "Substring \"" << substr << "\" not found." << std::endl;
        }

        return result;
    }

    std::vector<my_str_COW> tokenize(const my_str_COW& delimiter) const {
        std::vector<my_str_COW> tokens;

        auto delim_idxs = search(delimiter);

        if (delim_idxs.empty()) {
            tokens.push_back(*this);
            return tokens;
        }

        size_t start = 0;
        auto delim_sz = delimiter.size();
        auto str_sz = size();
        for (auto idx : delim_idxs) {
            if (idx > start) {
                auto cur_el = substr(start, idx - 1);
                tokens.push_back(cur_el); 
            }
            start = idx + delim_sz;
        }
        if (start < str_sz) {
            auto cur_el = substr(start, str_sz - 1);
            tokens.push_back(cur_el);
        }

        return tokens;
    }

    friend std::ostream& operator<<(std::ostream& os, const my_str_COW& str) {
        for(size_t i = 0; i < str.size(); ++i) {
            os << str[i];
        }

        return os << '\0';
    }

 private:
    using storage = std::vector<CharT>;

    std::size_t _begin;
    std::size_t _end;

    std::shared_ptr<storage> _buff;

    my_str_COW(std::shared_ptr<storage> buff, std::size_t begin, std::size_t end) : _begin(begin), _end(end), _buff(std::move(buff)) {}

    void _detach() {
        if (_buff.unique()) {
            return;
        }

        std::size_t new_size = _buff->size();  // include null terminator

        auto new_buff = std::make_shared<storage>(new_size);
        std::copy(_buff->begin(), _buff->end(), new_buff->begin());
        _buff = new_buff;
    
        return;
    }

    void _validate_index(std::size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of bounds");
        }
    }
};

} // namespace COW

#endif // MY_STR_COW_HPP_

