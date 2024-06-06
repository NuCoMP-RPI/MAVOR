#include <gtest/gtest.h>

#include "chebyshev.hpp"

double abs_tol = 1e-6;

TEST(ChebyshevSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_chebyshev_order(0,0), 1);
    EXPECT_EQ(eval_chebyshev_order(1,0), 1);
    EXPECT_EQ(eval_chebyshev_order(0,1), 0);
}

TEST(ChebyshevSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_chebyshev_order(2,4), 97, abs_tol);
    EXPECT_NEAR(eval_chebyshev_order(3.4,2), 22.12, abs_tol);
    EXPECT_NEAR(eval_chebyshev_order(1600,5), 1.67772078080008e17, abs_tol);
}

TEST(ChebyshevSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_chebyshev_order(0.5,5), 0.5, abs_tol);
    EXPECT_NEAR(eval_chebyshev_order(0.1, 2), -0.98, abs_tol);
    EXPECT_NEAR(eval_chebyshev_order(0.2, 2), -0.92, abs_tol);
    EXPECT_NEAR(eval_chebyshev_order(0.9, 3), 0.216, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
