#include <gtest/gtest.h>

#include "basis_power.hpp"

double abs_tol = 1e-6;

TEST(PowerSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_power_order(0,0), 1);
    EXPECT_EQ(eval_power_order(1,0), 1);
    EXPECT_EQ(eval_power_order(0,1), 0);
}

TEST(PowerSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_power_order(2,4), 16, abs_tol);
    EXPECT_NEAR(eval_power_order(3.4,2), 11.56, abs_tol);
    EXPECT_NEAR(eval_power_order(1600,5), 1.048576e16, abs_tol);
}

TEST(PowerSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_power_order(0.5,5), 0.03125, abs_tol);
    EXPECT_NEAR(eval_power_order(0.1, 2), 0.01, abs_tol);
    EXPECT_NEAR(eval_power_order(0.9, 3), 0.729, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
