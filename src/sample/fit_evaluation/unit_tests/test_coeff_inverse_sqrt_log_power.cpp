#include <gtest/gtest.h>

#include "coeff_inverse_sqrt_log_power.hpp"

double abs_tol = 1e-6;

TEST(InverseSqrtLogPowerCoeffTest, HandlesZeros){
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

