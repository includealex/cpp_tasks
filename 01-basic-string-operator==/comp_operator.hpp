#ifndef COMP_OPERATOR_HPP
#define COMP_OPERATOR_HPP

#include <string>

namespace custom {

    template<typename CharT, typename Traits, typename Alloc>
    bool operator==(const std::basic_string<CharT, Traits, Alloc>& lhs, 
                    const std::basic_string<CharT, Traits, Alloc>& rhs);

} // namespace custom

#endif // COMP_OPERATOR_HPP

