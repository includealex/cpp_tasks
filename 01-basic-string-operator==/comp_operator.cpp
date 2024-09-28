#include "comp_operator.hpp"
#include <iostream>

namespace custom {

    // Custom operator== for std::string
    template<typename CharT, typename Traits, typename Alloc>
    bool operator==(const std::basic_string<CharT, Traits, Alloc>& lhs, 
                    const std::basic_string<CharT, Traits, Alloc>& rhs) {

        std::cout << "Custom operator== is called for std::basic_string!" << std::endl;
        return lhs.compare(rhs) == 0;
    }

    template bool operator==(const std::basic_string<char>&, const std::basic_string<char>&);

} // namespace custom

