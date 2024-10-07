#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdexcept>

#include "file_reading.hpp"

// Test cases for the split function
TEST(SplitFunctionTest, HandlesEmptyString) {
    std::string input = "";
    std::vector<std::string> expected = {};
    EXPECT_EQ(split(input, ','), expected);
}

TEST(SplitFunctionTest, SingleDelimiter) {
    std::string input = "a,b,c";
    std::vector<std::string> expected = {"a", "b", "c"};
    EXPECT_EQ(split(input, ','), expected);
}

TEST(SplitFunctionTest, MultipleDelimiters) {
    std::string input = "a,,b,c";
    std::vector<std::string> expected = {"a", "", "b", "c"};
    EXPECT_EQ(split(input, ','), expected);
}

TEST(SplitFunctionTest, HandlesNoDelimiter) {
    std::string input = "abc";
    std::vector<std::string> expected = {"abc"};
    EXPECT_EQ(split(input, ','), expected);
}

TEST(SplitFunctionTest, HandlesDifferentDelimiter) {
    std::string input = "a;b;c";
    std::vector<std::string> expected = {"a", "b", "c"};
    EXPECT_EQ(split(input, ';'), expected);
}

TEST(ENDFFloatTest, HandlesValidNumber) {
    EXPECT_DOUBLE_EQ(ENDF_float(" 123.45 "), 123.45);
    EXPECT_DOUBLE_EQ(ENDF_float("-123.45"), -123.45);
    EXPECT_DOUBLE_EQ(ENDF_float("+123.45"), 123.45);
}

TEST(ENDFFloatTest, HandlesScientificNotation) {
    EXPECT_DOUBLE_EQ(ENDF_float("1.23e+5"), 1.23e5);
    EXPECT_DOUBLE_EQ(ENDF_float("1.24e-5"), 1.24e-5);
}

TEST(ENDFFloatTest, HandlesENDFFormat) {
    EXPECT_DOUBLE_EQ(ENDF_float("1.23+5"), 1.23e5);
    EXPECT_DOUBLE_EQ(ENDF_float("1.24-5"), 1.24e-5);
}

TEST(ENDFFloatTest, HandlesInvalidNumber) {
    EXPECT_THROW(ENDF_float("abc"), std::invalid_argument);
    EXPECT_THROW(ENDF_float(""), std::invalid_argument);
}

TEST(ENDFFloatTest, HandlesEmptyString) {
    EXPECT_THROW(ENDF_float("   "), std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
