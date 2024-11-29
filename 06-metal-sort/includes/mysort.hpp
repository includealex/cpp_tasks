#ifndef INCLUDES_MYSORT_HPP_
#define INCLUDES_MYSORT_HPP_

#include "metal.hpp"

namespace custom {

template<class x, class y>
using smaller = metal::number<(sizeof(x) < sizeof(y))>;

template<typename List>
using stable_sort = metal::sort<List, metal::lambda<smaller>>;

} // namespace custom

#endif // INCLUDES_MYSORT_HPP_
