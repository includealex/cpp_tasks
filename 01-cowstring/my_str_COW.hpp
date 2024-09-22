#ifndef MY_STR_COW_HPP_
#define MY_STR_COW_HPP_

#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

namespace COW {

template<typename CharT, typename Allocator = std::allocator<CharT>>
class my_str_COW final {
 public:
    my_str_COW() : _buff{std::make_shared<storage>()}, _begin{0}, _end{0} {}

    template<std::size_t N>
    explicit my_str_COW (const CharT (&str)[N]) : _buff{std::make_shared<storage>(N-1)}, _begin{0}, _end{N-2} {
        std::copy(str, str + (N - 1), _buff->begin());
    }

    my_str_COW(const my_str_COW& other, std::size_t begin, std::size_t end) : _buff{other._buff}, _begin{begin}, _end{end} {
        if (begin > end || begin < 0 || end >= other.size()) {
            throw std::out_of_range("Invalid range for substring!");
        }
    }

    my_str_COW(my_str_COW&& other) noexcept : _buff{std::move(other._buff)}, _begin{other._begin}, _end{other._end} {
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
        return _end - _begin + 1;
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

    my_str_COW substr(std::size_t begin, std::size_t end) {
        if( begin > end ) {
            throw std::invalid_argument{ "substr(): The substring has range [begin,end]. End should be greater or equal to begin" };
        }
        begin += offset();
        end += offset();
        return my_str_COW(*this, begin, end);
    }

    void* cur_addr() const {
        if (!_buff || offset() < 0 || offset() >= _buff->size()) {
            throw std::out_of_range("Offset is out of bounds");
        }
        return static_cast<void*>(&_buff->at(offset()));
    }

    friend std::ostream& operator<<(std::ostream& os, const my_str_COW& str) {
        for(auto i = 0; i < str.size(); ++i) {
            os << str[i];
        }

        return os << "\0";
    }

 private:
    using storage = std::vector<CharT>;

    std::size_t _begin;
    std::size_t _end;

    std::shared_ptr<storage> _buff;

    void _detach() {
        if (_buff.unique()) {
            return;
        }

        std::size_t new_size = size() + offset();
        if (new_size == 0) {
            throw std::runtime_error("Cannot detach: new buffer size is zero.");
        }

        auto new_buff = std::make_shared<storage>(new_size);
        std::copy(_buff->begin(), _buff->begin() + new_size, new_buff->begin());
        _buff = new_buff;

        return;
    }

    void _validate_index(std::size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of bounds");
        }

        return;
    }
};

} // namespace COW

#endif // MY_STR_COW_HPP_

