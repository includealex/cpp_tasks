#include "metal.hpp"

union x { char payload[8]; };
class y { public: char c; };
struct z { char c; int32_t i; };

using l3 = metal::list<char,int32_t,y,uint64_t,x>;

template<class x, class y>
using smaller = metal::number<(sizeof(x) < sizeof(y))>;
using sorted = metal::sort<l3, metal::lambda<smaller>>;

static_assert(metal::same<sorted, metal::list<char,y,int32_t,uint64_t,x>>::value, "here is the main assert");

int main() {
    return 0;
}
