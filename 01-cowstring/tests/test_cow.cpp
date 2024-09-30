#include <gtest/gtest.h>

#include "../src/my_str_COW.hpp"

using namespace COW;

TEST(MyStrCOWTest, DefaultConstructor) {
    my_str_COW<char> str;
    EXPECT_EQ(str.size(), 1);
    EXPECT_EQ(str[0], '\0');
}

TEST(MyStrCOWTest, ConstructorFromStringLiteral) {
    my_str_COW<char> str("hello");
    EXPECT_EQ(str.size(), 5);
    EXPECT_EQ(str[0], 'h');
    EXPECT_EQ(str[1], 'e');
    EXPECT_EQ(str[2], 'l');
    EXPECT_EQ(str[3], 'l');
    EXPECT_EQ(str[4], 'o');
}

TEST(MyStrCOWTest, CopyConstructor) {
    my_str_COW<char> original("copy");
    my_str_COW<char> copy = original;

    EXPECT_EQ(copy.size(), 4);
    EXPECT_EQ(copy[0], 'c');
    EXPECT_EQ(copy[1], 'o');
    EXPECT_EQ(copy[2], 'p');
    EXPECT_EQ(copy[3], 'y');
}

TEST(MyStrCOWTest, MoveConstructor) {
    my_str_COW<char> original("move");
    my_str_COW<char> moved = std::move(original);

    EXPECT_EQ(moved.size(), 4);
    EXPECT_EQ(moved[0], 'm');
    EXPECT_EQ(moved[1], 'o');
    EXPECT_EQ(moved[2], 'v');
    EXPECT_EQ(moved[3], 'e');
}

TEST(MyStrCOWTest, CopyAssignment) {
    my_str_COW<char> str1("assignment");
    my_str_COW<char> str2 = str1;

    EXPECT_EQ(str2.size(), 10);
    EXPECT_EQ(str2[0], 'a');
    EXPECT_EQ(str2[9], 't');
}

TEST(MyStrCOWTest, MoveAssignment) {
    my_str_COW<char> str1("assignment");
    my_str_COW<char> str2 = std::move(str1);

    EXPECT_EQ(str2.size(), 10);
    EXPECT_EQ(str2[0], 'a');
    EXPECT_EQ(str2[9], 't');
}

TEST(MyStrCOWTest, IndexOperatorConst) {
    const my_str_COW<char> str("index");
    EXPECT_EQ(str[0], 'i');
    EXPECT_EQ(str[4], 'x');
    EXPECT_THROW(str[5], std::out_of_range);
}

TEST(MyStrCOWTest, IndexOperatorNonConst) {
    my_str_COW<char> str("change");
    EXPECT_EQ(str[0], 'c');
    str[0] = 'C';
    EXPECT_EQ(str[0], 'C');
}

TEST(MyStrCOWTest, Substring) {
    my_str_COW<char> str("substring");
    auto sub = str.substr(3, 5);
    EXPECT_EQ(sub.size(), 3);
    EXPECT_EQ(sub[0], 's');
    EXPECT_EQ(sub[1], 't');
    EXPECT_EQ(sub[2], 'r');
    EXPECT_THROW(str.substr(0, 20), std::out_of_range);
}

TEST(MyStrCOWTest, Concatenation) {
    my_str_COW<char> str1("hello ");
    my_str_COW<char> str2("world");
    auto concat = str1.concat(str2);
    EXPECT_EQ(concat.size(), 11);
    EXPECT_EQ(concat[0], 'h');
    EXPECT_EQ(concat[5], ' ');
    EXPECT_EQ(concat[6], 'w');
    EXPECT_EQ(concat[10], 'd');
}

TEST(MyStrCOWTest, Search) {
    my_str_COW<char> str("hello world");
    my_str_COW<char> substr("world");
    auto positions = str.search(substr);
    EXPECT_EQ(positions.size(), 1);
    EXPECT_EQ(positions[0], 6);

    my_str_COW<char> l ("l");
    auto l_num = str.search(l);
    EXPECT_EQ(l_num.size(), 3);
}

TEST(MyStrCOWTest, Tokenization) {
    my_str_COW<char> str("tokenize,this,string");
    my_str_COW<char> delimiter(",");
    auto tokens = str.tokenize(delimiter);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0].size(), 8);   // "tokenize"
    EXPECT_EQ(tokens[1].size(), 4);   // "this"
    EXPECT_EQ(tokens[2].size(), 6);   // "string"
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

