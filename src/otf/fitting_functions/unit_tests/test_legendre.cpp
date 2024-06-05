#include <gtest/gtest.h>

#include "legendre.hpp"

double abs_tol = 1e-6;

TEST(LegendreSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_legendre_order(0,0), 1);
    EXPECT_EQ(eval_legendre_order(1,0), 1);
    EXPECT_EQ(eval_legendre_order(0,1), 0);
}

TEST(LegendreSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_legendre_order(2,4), 55.375, abs_tol);
    EXPECT_NEAR(eval_legendre_order(3.4,2), 16.84, abs_tol);
    EXPECT_NEAR(eval_legendre_order(1600,5), 8.2575324160002992e16, abs_tol);
}

TEST(LegendreSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_legendre_order(0.5,5), 0.08984375, abs_tol);
    EXPECT_NEAR(eval_legendre_order(0.1, 2), -0.485, abs_tol);
    EXPECT_NEAR(eval_legendre_order(0.2, 2), -0.44, abs_tol);
    EXPECT_NEAR(eval_legendre_order(0.9, 3), 0.4725, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
