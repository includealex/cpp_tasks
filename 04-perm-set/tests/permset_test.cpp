#include <gtest/gtest.h>
#include "permset_impl.hpp"

namespace custom {

TEST(PermSetTest, InsertAndContains) {
    custom::PermSet<std::size_t> set;

    set.insert(10);
    set.insert(5);
    set.insert(15);

    EXPECT_TRUE(set.contains(10));
    EXPECT_TRUE(set.contains(5));
    EXPECT_TRUE(set.contains(15));
    EXPECT_FALSE(set.contains(20));
}

TEST(PermSetTest, DuplicateInsertion) {
    custom::PermSet<std::size_t> set;

    set.insert(10);
    set.insert(10);
    set.insert(5);

    EXPECT_TRUE(set.contains(10));
    EXPECT_TRUE(set.contains(5));
    EXPECT_FALSE(set.contains(20));
}

TEST(PermSetTest, InorderMultipleElements) {
    custom::PermSet<std::size_t> set;

    set.insert(10);
    set.insert(5);
    set.insert(15);
    set.insert(7);
    set.insert(2);

    std::vector<std::size_t> expected = {2, 5, 7, 10, 15};
    EXPECT_EQ(set.inorder(), expected);
}

TEST(PermSetTest, InorderSingleElement) {
    custom::PermSet<std::size_t> set;

    set.insert(10);

    std::vector<std::size_t> expected = {10};
    EXPECT_EQ(set.inorder(), expected);
}

TEST(PermSetTest, InorderEmptySet) {
    custom::PermSet<std::size_t> set;

    std::vector<std::size_t> expected = {};
    EXPECT_EQ(set.inorder(), expected);
}

TEST(PermSetTest, InorderWithDuplicates) {
    custom::PermSet<std::size_t> set;

    set.insert(10);
    set.insert(5);
    set.insert(10);
    set.insert(15);
    set.insert(5);

    std::vector<std::size_t> expected = {5, 10, 15};
    EXPECT_EQ(set.inorder(), expected);
}

TEST(PermSetTest, InsertUndoRedo) {
    custom::PermSet<std::size_t> set;

    set.insert(10);
    set.insert(5);
    set.insert(15);

    EXPECT_EQ(set.inorder(), (std::vector<std::size_t>{5, 10, 15}));

    set.undo();
    EXPECT_EQ(set.inorder(), (std::vector<std::size_t>{5, 10}));

    set.redo();
    EXPECT_EQ(set.inorder(), (std::vector<std::size_t>{5, 10, 15}));

    set.insert(20);
    EXPECT_EQ(set.inorder(), (std::vector<std::size_t>{5, 10, 15, 20}));

    set.undo();
    EXPECT_EQ(set.inorder(), (std::vector<std::size_t>{5, 10, 15}));
}

TEST(PermSetTest, DifficultUndoRedo) {
    custom::PermSet<std::size_t> set;

    set.insert(4);
    set.insert(3);
    set.insert(2);
    set.insert(8);
    set.insert(7);
    set.insert(10);
    EXPECT_EQ(set.inorder(), (std::vector<std::size_t>{2, 3, 4, 7, 8, 10}));

    set.insert(5);
    EXPECT_EQ(set.inorder(), (std::vector<std::size_t>{2, 3, 4, 5, 7, 8, 10}));

    set.undo();
    EXPECT_EQ(set.inorder(), (std::vector<std::size_t>{2, 3, 4, 7, 8, 10}));
}

TEST(PermSetTest, LargeInsertionAndUndoRedo) {
    custom::PermSet<std::size_t> set;
    std::vector<std::size_t> elements;

    std::size_t big_num = 1e3;
    for (std::size_t i = 0; i < big_num; ++i) {
        set.insert(i);
        elements.push_back(i);
    }

    std::vector<std::size_t> initialInorder = set.inorder();
    EXPECT_EQ(initialInorder, elements);

    set.undo();
    std::vector<std::size_t> afterUndoInorder = set.inorder();
    EXPECT_EQ(afterUndoInorder, std::vector<std::size_t>(elements.begin(), elements.end() - 1));

    set.redo();
    std::vector<std::size_t> afterRedoInorder = set.inorder();
    EXPECT_EQ(afterRedoInorder, elements);
}

} // namespace custom

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
