#include <math.h>

#include <gtest/gtest.h>

#include "basis_log_power.hpp"

double abs_tol = 1e-6;

TEST(LowPowerSeriesTest, HandlesZeros){
    EXPECT_EQ(eval_log_power_order(0,0), 1);
    EXPECT_EQ(eval_log_power_order(1,0), 1);
    ASSERT_TRUE(std::isinf(eval_log_power_order(0,1)));
}

TEST(LowPowerSeriesTest, HandlesUnscaledRegion){
    EXPECT_NEAR(eval_log_power_order(2,4), 0.230835098583, abs_tol);
    EXPECT_NEAR(eval_log_power_order(3.4,2), 1.49762630704, abs_tol);
    EXPECT_NEAR(eval_log_power_order(1600,5), 21858.597636, abs_tol);
}

TEST(LowPowerSeriesTest, HandlesScaledRegion){
    EXPECT_NEAR(eval_log_power_order(0.5,5), -0.160002697757, abs_tol);
    EXPECT_NEAR(eval_log_power_order(0.1, 2), 5.30189811048, abs_tol);
    EXPECT_NEAR(eval_log_power_order(0.2, 2), 2.59029039398, abs_tol);
    EXPECT_NEAR(eval_log_power_order(0.9, 3), -0.00116959004327, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
