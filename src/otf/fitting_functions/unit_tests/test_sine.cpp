#include <gtest/gtest.h>

#include "sine.hpp"

double abs_tol = 1e-6;

TEST(SineSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_sine_order(0,0), 1);
    EXPECT_EQ(eval_sine_order(1,0), 1);
    EXPECT_EQ(eval_sine_order(0,1), 0);
}

TEST(SineSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_sine_order(2,4), 0, abs_tol);
    EXPECT_NEAR(eval_sine_order(3.4,2), -0.951056516295, abs_tol);
    EXPECT_NEAR(eval_sine_order(1600,5), 0, abs_tol);
}

TEST(SineSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_sine_order(0.5,5), 0, abs_tol);
    EXPECT_NEAR(eval_sine_order(0.1, 2), 0.951056516295, abs_tol);
    EXPECT_NEAR(eval_sine_order(0.2, 2), 0.587785252292, abs_tol);
    EXPECT_NEAR(eval_sine_order(0.9, 3), -0.951056516295, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
