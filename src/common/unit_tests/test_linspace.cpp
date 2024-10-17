#include "linspace.hpp"
#include <gtest/gtest.h>

TEST(LinspaceTest, LinspaceDouble) {
    std::vector<double> result = linspace(0.0, 1.0, 5);
    std::vector<double> expected = {0.0, 0.25, 0.5, 0.75, 1.0};

    ASSERT_EQ(result.size(), expected.size()) << "Vectors are of unequal length";

    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_NEAR(result[i], expected[i], 1e-9) << "Mismatch at index " << i;
    }
}

TEST(LinspaceTest, LinspaceInt) {
    std::vector<int> result = linspace(0, 4, 5);
    std::vector<int> expected = {0, 1, 2, 3, 4};

    ASSERT_EQ(result.size(), expected.size()) << "Vectors are of unequal length";

    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], expected[i]) << "Mismatch at index " << i;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}