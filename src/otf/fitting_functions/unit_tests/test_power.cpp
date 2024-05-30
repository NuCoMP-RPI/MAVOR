#include <gtest/gtest.h>

#include "power.hpp"

TEST(PowerSeriesTest, HandlesCorrectUsage){
    EXPECT_EQ(eval_power_order(0,0), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
