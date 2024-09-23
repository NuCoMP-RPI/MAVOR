#include <math.h>

#include <gtest/gtest.h>

#include "basis_exponential.hpp"

double abs_tol = 1e-6;

TEST(ExponentialSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_exponential_order(0,0), 1);
    EXPECT_EQ(eval_exponential_order(1,0), 1);
    EXPECT_EQ(eval_exponential_order(0,1), 1);
}

TEST(ExponentialSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_exponential_order(2,4), 2980.95798704, abs_tol);
    EXPECT_NEAR(eval_exponential_order(3.4,2), 897.84729165, abs_tol);
    ASSERT_TRUE(std::isinf(eval_exponential_order(1600,5)));
}

TEST(ExponentialSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_exponential_order(0.5,5), 12.1824939607, abs_tol);
    EXPECT_NEAR(eval_exponential_order(0.1, 2), 1.22140275816, abs_tol);
    EXPECT_NEAR(eval_exponential_order(0.2, 2), 1.49182469764, abs_tol);
    EXPECT_NEAR(eval_exponential_order(0.9, 3), 14.8797317249, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
