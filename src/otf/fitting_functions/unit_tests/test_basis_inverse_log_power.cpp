#include <gtest/gtest.h>

#include "basis_inverse_log_power.hpp"

double abs_tol = 1e-6;

TEST(InverseLogPowerSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_inverse_log_power_order(0,0), 1);
    EXPECT_EQ(eval_inverse_log_power_order(1,0), 1);
    EXPECT_EQ(eval_inverse_log_power_order(0,1), 0);
}

TEST(InverseLogPowerSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_inverse_log_power_order(2,4), 4.33209683509, abs_tol);
    EXPECT_NEAR(eval_inverse_log_power_order(3.4,2), 0.667723313418, abs_tol);
    EXPECT_NEAR(eval_inverse_log_power_order(1600,5), 0.0000457485890289, abs_tol);
}

TEST(InverseLogPowerSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_inverse_log_power_order(0.5,5), -6.24989462064, abs_tol);
    EXPECT_NEAR(eval_inverse_log_power_order(0.1, 2), 0.188611697012, abs_tol);
    EXPECT_NEAR(eval_inverse_log_power_order(0.2, 2), 0.386057100904, abs_tol);
    EXPECT_NEAR(eval_inverse_log_power_order(0.9, 3), -855.000438616, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
