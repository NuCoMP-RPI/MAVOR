#include <gtest/gtest.h>

#include "inverse_exponential.hpp"

double abs_tol = 1e-6;

TEST(InverseExponentialSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_inverse_exponential_order(0,0), 1);
    EXPECT_EQ(eval_inverse_exponential_order(1,0), 1);
    EXPECT_EQ(eval_inverse_exponential_order(0,1), 1);
}

TEST(InverseExponentialSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_inverse_exponential_order(2,4), 0.000335462627903, abs_tol);
    EXPECT_NEAR(eval_inverse_exponential_order(3.4,2), 0.00111377514784, abs_tol);
    EXPECT_NEAR(eval_inverse_exponential_order(1600,5), 0, abs_tol);
}

TEST(InverseExponentialSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_inverse_exponential_order(0.5,5), 0.0820849986239, abs_tol);
    EXPECT_NEAR(eval_inverse_exponential_order(0.1, 2), 0.818730753078, abs_tol);
    EXPECT_NEAR(eval_inverse_exponential_order(0.2, 2), 0.670320046036, abs_tol);
    EXPECT_NEAR(eval_inverse_exponential_order(0.9, 3), 0.0672055127397, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
