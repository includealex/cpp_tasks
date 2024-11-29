#include <iostream>
#include "mult.hpp"

namespace custom {

void simple_test() {
    Value<M> x{10.5};
    Value<S, int> y{2};
    auto v = x / y;
    std::cout << "Velocity = " << v << std::endl;

    static_assert(std::is_convertible_v<decltype(v), Value<MpS>>);
    assert(v.val == 5.25);

    auto distance = 10.0_m;
    Value<S, double> time = 20.0_s;
    auto speed = distance / time;
    Value<MpS2, double> acceleration = distance / square(time);
    std::cout << "Speed = " << speed << " Acceleration = " << acceleration << std::endl;
}

} // namespace custom

int main() {
    custom::simple_test();

    return 0;
}
