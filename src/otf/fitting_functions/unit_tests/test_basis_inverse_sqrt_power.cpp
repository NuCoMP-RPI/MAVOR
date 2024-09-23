#include <math.h>

#include <gtest/gtest.h>

#include "basis_inverse_sqrt_power.hpp"

double abs_tol = 1e-6;

TEST(InverseSqrtPowerSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_inverse_sqrt_power_order(0,0), 1);
    EXPECT_EQ(eval_inverse_sqrt_power_order(1,0), 1);
    ASSERT_TRUE(std::isinf(eval_inverse_sqrt_power_order(0,1)));
}

TEST(InverseSqrtPowerSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_inverse_sqrt_power_order(2,4), 0.25, abs_tol);
    EXPECT_NEAR(eval_inverse_sqrt_power_order(3.4,2), 0.294117647059, abs_tol);
    EXPECT_NEAR(eval_inverse_sqrt_power_order(1600,5), 9.765625e-9, abs_tol);
}

TEST(InverseSqrtPowerSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_inverse_sqrt_power_order(0.5,5), 5.65685424949, abs_tol);
    EXPECT_NEAR(eval_inverse_sqrt_power_order(0.1, 2), 10, abs_tol);
    EXPECT_NEAR(eval_inverse_sqrt_power_order(0.2, 2), 5, abs_tol);
    EXPECT_NEAR(eval_inverse_sqrt_power_order(0.9, 3), 1.17121394821, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
