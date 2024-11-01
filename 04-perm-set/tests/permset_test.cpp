#include <gtest/gtest.h>
#include "permset_impl.hpp"

namespace custom {

TEST(PermSetTest, InsertAndContains) {
    custom::PermanentSet<int> set;

    set.insert(10);
    set.insert(5);
    set.insert(15);

    EXPECT_TRUE(set.contains(10));
    EXPECT_TRUE(set.contains(5));
    EXPECT_TRUE(set.contains(15));
    EXPECT_FALSE(set.contains(20));
}

TEST(PermSetTest, DuplicateInsertion) {
    custom::PermanentSet<int> set;

    set.insert(10);
    set.insert(10);
    set.insert(5);

    EXPECT_TRUE(set.contains(10));
    EXPECT_TRUE(set.contains(5));
    EXPECT_FALSE(set.contains(20));
}

TEST(PermSetTest, inorderMultipleElements) {
    custom::PermanentSet<int> set;

    set.insert(10);
    set.insert(5);
    set.insert(15);
    set.insert(7);
    set.insert(2);

    std::vector<int> expected = {2, 5, 7, 10, 15};
    EXPECT_EQ(set.inorder(), expected);
}

TEST(PermSetTest, inorderSingleElement) {
    custom::PermanentSet<int> set;

    set.insert(10);

    std::vector<int> expected = {10};
    EXPECT_EQ(set.inorder(), expected);
}

TEST(PermSetTest, inorderEmptySet) {
    custom::PermanentSet<int> set;

    std::vector<int> expected = {};
    EXPECT_EQ(set.inorder(), expected);
}

TEST(PermSetTest, inorderWithDuplicates) {
    custom::PermanentSet<int> set;

    set.insert(10);
    set.insert(5);
    set.insert(10);
    set.insert(15);
    set.insert(5);

    std::vector<int> expected = {5, 10, 15};
    EXPECT_EQ(set.inorder(), expected);
}

} // namespace custom

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}