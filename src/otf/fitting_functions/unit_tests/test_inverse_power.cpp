#include <math.h>

#include <gtest/gtest.h>

#include "inverse_power.hpp"

double abs_tol = 1e-6;

TEST(InversePowerSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_inverse_power_order(0,0), 1);
    EXPECT_EQ(eval_inverse_power_order(1,0), 1);
    ASSERT_TRUE(std::isinf(eval_inverse_power_order(0,1)));
}

TEST(InversePowerSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_inverse_power_order(2,4), 0.0625, abs_tol);
    EXPECT_NEAR(eval_inverse_power_order(3.4,2), 0.0865051903114, abs_tol);
    EXPECT_NEAR(eval_inverse_power_order(1600,5), 9.5367431641e-17, abs_tol);
}

TEST(InversePowerSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_inverse_power_order(0.5,5), 32, abs_tol);
    EXPECT_NEAR(eval_inverse_power_order(0.1, 2), 100, abs_tol);
    EXPECT_NEAR(eval_inverse_power_order(0.2, 2), 25, abs_tol);
    EXPECT_NEAR(eval_inverse_power_order(0.9, 3), 1.3717421148, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
