#include <gtest/gtest.h>

#include "coeff_sine_cosine.hpp"

double abs_tol = 1e-6;

double x1 = 1;
double x2 = -0.83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

TEST(SineCosineCoeffTest, Naive){
    EXPECT_NEAR(naive_sine_cosine(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_sine_cosine(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(naive_sine_cosine(x1, three_coeff), 1.5, abs_tol);
    EXPECT_NEAR(naive_sine_cosine(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_sine_cosine(x2, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(naive_sine_cosine(x2, three_coeff), 1.719077, abs_tol);
    EXPECT_NEAR(naive_sine_cosine(x2, eight_coeff), 1.438700, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

