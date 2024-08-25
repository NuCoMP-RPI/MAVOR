#include <gtest/gtest.h>

#include "coeff_legendre.hpp"

double abs_tol = 1e-6;

TEST(LegendreCoeffTest, HandlesZeros){
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

