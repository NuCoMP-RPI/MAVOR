#include "arange.hpp"
#include <gtest/gtest.h>

TEST(ArangeTest, ArangeFloat) {
    std::vector<float> result = arange(0.0f, 1.0f, 0.2f);
    std::vector<float> expected = {0.0f, 0.2f, 0.4f, 0.6f, 0.8f};

    ASSERT_EQ(result.size(), expected.size()) << "Vectors are of unequal length";

    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_NEAR(result[i], expected[i], 1e-5) << "Mismatch at index " << i;
    }
}

TEST(ArangeTest, ArangeInt) {
    std::vector<int> result = arange(0, 5, 1);
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