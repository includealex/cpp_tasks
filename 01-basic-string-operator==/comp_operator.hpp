#ifndef COMP_OPERATOR_HPP
#define COMP_OPERATOR_HPP

#include <string>

namespace custom {

template<typename CharT, typename Traits1, typename Alloc1, typename Traits2, typename Alloc2>
bool operator==(const std::basic_string<CharT, Traits1, Alloc1>& lhs,
                const std::basic_string<CharT, Traits2, Alloc2>& rhs);

template<typename CharT, typename Traits1, typename Alloc1, typename Traits2, typename Alloc2>
int custom_compare(const std::basic_string<CharT, Traits1, Alloc1>& lhs,
                   const std::basic_string<CharT, Traits2, Alloc2>& rhs);

} // custom

#endif // COMP_OPERATOR_HPP

