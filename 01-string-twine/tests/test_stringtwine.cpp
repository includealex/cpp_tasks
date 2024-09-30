#include <gtest/gtest.h>
#include <string>

#include "../src/string_twine.hpp"

TEST(StringTwineTest, StringViewConstructor) {
    std::string_view sv = "Hello,";
    std::string_view sv2 = "World!";

    auto s = custom::string_twine(sv, " ", sv2).to_str();
    ASSERT_EQ(s, "Hello, World!");
    ASSERT_EQ(s.size(), 13);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
