#include <gtest/gtest.h>

#include "cosine.hpp"

double abs_tol = 1e-6;

TEST(CosineSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_cosine_order(0,0), 1);
    EXPECT_EQ(eval_cosine_order(1,0), 1);
    EXPECT_EQ(eval_cosine_order(0,1), 1);
}

TEST(CosineSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_cosine_order(2,4), 1, abs_tol);
    EXPECT_NEAR(eval_cosine_order(3.4,2), 0.309016994375, abs_tol);
    EXPECT_NEAR(eval_cosine_order(1600,5), 1, abs_tol);
}

TEST(CosineSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_cosine_order(0.5,5), -1, abs_tol);
    EXPECT_NEAR(eval_cosine_order(0.1, 2), 0.309016994375, abs_tol);
    EXPECT_NEAR(eval_cosine_order(0.2, 2), -0.809016994375, abs_tol);
    EXPECT_NEAR(eval_cosine_order(0.9, 3), -0.309016994375, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
