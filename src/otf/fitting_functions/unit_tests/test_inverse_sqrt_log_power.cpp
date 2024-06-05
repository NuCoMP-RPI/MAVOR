#include <math.h>

#include <gtest/gtest.h>

#include "inverse_sqrt_log_power.hpp"

double abs_tol = 1e-6;

TEST(InverseSqrtLogPowerSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_inverse_sqrt_log_power_order(0,0), 1);
    EXPECT_EQ(eval_inverse_sqrt_log_power_order(1,0), 1);
    ASSERT_TRUE(std::isnan(eval_inverse_sqrt_log_power_order(0,1)));
}

TEST(InverseSqrtLogPowerSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_inverse_sqrt_log_power_order(2,4), 2.08136898101, abs_tol);
    EXPECT_NEAR(eval_inverse_sqrt_log_power_order(3.4,2), 0.817143386082, abs_tol);
    EXPECT_NEAR(eval_inverse_sqrt_log_power_order(1600,5), 0.00676377032645, abs_tol);
}

TEST(InverseSqrtLogPowerSeriesTest, HandlesScaledRegion){
    ASSERT_TRUE(std::isnan(eval_inverse_sqrt_log_power_order(0.5, 5)));
    ASSERT_TRUE(std::isnan(eval_inverse_sqrt_log_power_order(0.1, 2)));
    ASSERT_TRUE(std::isnan(eval_inverse_sqrt_log_power_order(0.2, 2)));
    ASSERT_TRUE(std::isnan(eval_inverse_sqrt_log_power_order(0.9, 3)));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
