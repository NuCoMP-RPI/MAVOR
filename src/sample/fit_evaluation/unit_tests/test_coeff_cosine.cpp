#include <gtest/gtest.h>

#include "coeff_cosine.hpp"

double abs_tol = 1e-6;

TEST(CosineCoeffTest, Naive){
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

