#include <gtest/gtest.h>

#include "mysort.hpp"

namespace custom {

TEST(MetalSortTest, Simple) {
    union x { char payload[8]; };
    class y { public: char c; };
    struct z { char c; int32_t i; };

    using l3 = metal::list<char, int32_t, y, uint64_t, x>;
    using sorted = stable_sort<l3>;
    using expected = metal::list<char, y, int32_t, uint64_t, x>;

    static_assert(metal::same<sorted, expected>::value);
}

} // namespace custom

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
