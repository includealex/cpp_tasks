#include "comp_operator.hpp"
#include <iostream>

namespace custom {

template<typename CharT, typename Traits1, typename Alloc1, typename Traits2, typename Alloc2>
int custom_compare(const std::basic_string<CharT, Traits1, Alloc1>& lhs,
                   const std::basic_string<CharT, Traits2, Alloc2>& rhs) {
    size_t lhs_size = lhs.size();
    size_t rhs_size = rhs.size();
    size_t min_size = std::min(lhs_size, rhs_size);

    for (size_t i = 0; i < min_size; ++i) {
        if (lhs[i] < rhs[i]) {
            return -1;
        } else if (lhs[i] > rhs[i]) {
            return 1;
        }
    }

    if (lhs_size < rhs_size) {
        return -1;
    } else if (lhs_size > rhs_size) {
        return 1;
    }

    return 0;
}

template<typename CharT, typename Traits1, typename Alloc1, typename Traits2, typename Alloc2>
bool operator==(const std::basic_string<CharT, Traits1, Alloc1>& lhs,
                const std::basic_string<CharT, Traits2, Alloc2>& rhs) {
    std::cout << "Custom operator== for different allocators/traits is called!" << std::endl;

    return custom_compare(lhs, rhs) == 0;
}

template bool operator==(const std::basic_string<char>&, const std::basic_string<char>&);
template int custom_compare(const std::basic_string<char>&, const std::basic_string<char>&);

} // namespace custom

