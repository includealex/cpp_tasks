#include <gtest/gtest.h>
#include "mult.hpp"

namespace custom {

TEST(PhysLib, Div) {
    Value<M> x{42.42};
    Value<S, int> y{2};
    auto v = x / y;

    ::testing::StaticAssertTypeEq<decltype(v), Value<MpS>>();
    ASSERT_EQ(v.val, 21.21);

    auto distance = 10.0_m;
    Value<S> time = 20.0_s;
    auto speed = distance / time;
    Value<MpS2> acceleration = distance / (time * time);

    ASSERT_EQ(speed.val, 0.5);
    ASSERT_EQ(acceleration.val, 0.025);

    ::testing::StaticAssertTypeEq<decltype(speed), Value<MpS, long double>>();
    ::testing::StaticAssertTypeEq<decltype(acceleration), Value<MpS2>>();
}

TEST(PhysLib, Mul) {
    Value<M> x{42.42};
    Value<S, int> y{2};
    Value<Kg, int> z {3};
    auto v = x * y * z;

    ::testing::StaticAssertTypeEq<decltype(v), Value<Unit<1,1,1>>>();
    ASSERT_EQ(v.val, 254.52);
}

} // namespace custom

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
