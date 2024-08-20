#include <gtest/gtest.h>

#include "basis_sine_cosine.hpp"

double abs_tol = 1e-6;

TEST(SineCosineSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_sine_cosine_order(0,0), 1);
    EXPECT_EQ(eval_sine_cosine_order(1,0), 1);
    EXPECT_EQ(eval_sine_cosine_order(0,1), 1);
}

TEST(SineCosineSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_sine_cosine_order(2,4), -9.7971743931788257e-16, abs_tol);
    EXPECT_NEAR(eval_sine_cosine_order(3.4,2), 0.5877852522924738, abs_tol);
    EXPECT_NEAR(eval_sine_cosine_order(1600,5), 1, abs_tol);
}

TEST(SineCosineSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_sine_cosine_order(0.5,5), 1, abs_tol);
    EXPECT_NEAR(eval_sine_cosine_order(0.1, 2), 0.58778525229247314, abs_tol);
    EXPECT_NEAR(eval_sine_cosine_order(0.2, 2), 0.95105651629515353, abs_tol);
    EXPECT_NEAR(eval_sine_cosine_order(0.9, 3), 0.80901699437494734, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
