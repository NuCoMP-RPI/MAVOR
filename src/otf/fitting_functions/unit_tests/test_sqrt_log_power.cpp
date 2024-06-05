#include <math.h>

#include <gtest/gtest.h>

#include "sqrt_log_power.hpp"

double abs_tol = 1e-6;

TEST(SqrtLogPowerSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_sqrt_log_power_order(0,0), 1);
    EXPECT_EQ(eval_sqrt_log_power_order(1,0), 1);
    ASSERT_TRUE(std::isnan(eval_sqrt_log_power_order(0,1)));
}

TEST(SqrtLogPowerSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_sqrt_log_power_order(2,4), 0.480453013918, abs_tol);
    EXPECT_NEAR(eval_sqrt_log_power_order(3.4,2), 1.22377543162, abs_tol);
    EXPECT_NEAR(eval_sqrt_log_power_order(1600,5), 147.846534068, abs_tol);
}

TEST(SqrtLogPowerSeriesTest, HandlesScaledRegion){
    ASSERT_TRUE(std::isnan(eval_sqrt_log_power_order(0.5,5)));
    ASSERT_TRUE(std::isnan(eval_sqrt_log_power_order(0.1,2)));
    ASSERT_TRUE(std::isnan(eval_sqrt_log_power_order(0.2,2)));
    ASSERT_TRUE(std::isnan(eval_sqrt_log_power_order(0.9,3)));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
