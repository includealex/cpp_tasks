#include <iostream>
#include <cassert>

#include "mult.hpp"

void test_multiplication() {
    constexpr auto length = 3.0_m;
    constexpr auto time = 2.0_s;

    constexpr auto speed = length / time;
    static_assert(std::is_same_v<decltype(speed), Speed>, "Speed should have correct dimensions");
    assert(double(speed) == 1.5);

    constexpr auto acceleration = speed / time;
    static_assert(std::is_same_v<decltype(acceleration), Acceleration>, "Acceleration should have correct dimensions");
    assert(double(acceleration) == 0.75);
}

void test_division() {
    constexpr auto area = 9.0_m2;
    constexpr auto length = 3.0_m;

    constexpr auto recovered_length = area / length;
    static_assert(std::is_same_v<decltype(recovered_length), Length>, "Length should have correct dimensions");
    assert(double(recovered_length) == 3.0);
}

void test_scalar_operations() {
    constexpr Scalar scalar1{2.0};
    constexpr Scalar scalar2{4.0};

    constexpr auto scalar_mult = scalar1 * scalar2;
    assert(double(scalar_mult) == 8.0);

    constexpr auto scalar_div = scalar2 / scalar1;
    assert(double(scalar_div) == 2.0);
}

int main() {
    test_multiplication();
    test_division();
    test_scalar_operations();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
