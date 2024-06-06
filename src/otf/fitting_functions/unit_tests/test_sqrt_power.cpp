#include <math.h>

#include <gtest/gtest.h>

#include "sqrt_power.hpp"

double abs_tol = 1e-6;

TEST(SqrtPowerSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_sqrt_power_order(0,0), 1);
    EXPECT_EQ(eval_sqrt_power_order(1,0), 1);
    EXPECT_EQ(eval_sqrt_power_order(0,1), 0);
}

TEST(SqrtPowerSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_sqrt_power_order(2,4), 4, abs_tol);
    EXPECT_NEAR(eval_sqrt_power_order(3.4,2), 3.4, abs_tol);
    EXPECT_NEAR(eval_sqrt_power_order(1600,5), 102400000, abs_tol);
}

TEST(SqrtPowerSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_sqrt_power_order(0.5,5), 0.176776695297, abs_tol);
    EXPECT_NEAR(eval_sqrt_power_order(0.1, 2), 0.1, abs_tol);
    EXPECT_NEAR(eval_sqrt_power_order(0.2, 2), 0.2, abs_tol);
    EXPECT_NEAR(eval_sqrt_power_order(0.9, 3), 0.853814968245, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
