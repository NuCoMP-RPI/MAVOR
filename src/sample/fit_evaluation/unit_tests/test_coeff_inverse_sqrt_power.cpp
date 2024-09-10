#include <gtest/gtest.h>

#include "coeff_inverse_sqrt_power.hpp"

double abs_tol = 1e-6;

double x1 = 10;
double x2 = 83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

TEST(InverseSqrtPowerCoeffTest, Naive){
    EXPECT_NEAR(naive_inverse_sqrt_power(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power(x1, two_coeff), 1.158114, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power(x1, three_coeff), 1.183114, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power(x2, two_coeff), 1.054882, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power(x2, three_coeff), 1.057894, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power(x2, eight_coeff), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, Horner){
    EXPECT_NEAR(horner_inverse_sqrt_power_custom(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom(x1, two_coeff), 1.158114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom(x1, three_coeff), 1.183114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom(x2, two_coeff), 1.054882, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom(x2, three_coeff), 1.057894, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom(x2, eight_coeff), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, HornerGen){
    EXPECT_NEAR(horner_inverse_sqrt_power_general(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general(x1, two_coeff), 1.158114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general(x1, three_coeff), 1.183114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general(x2, two_coeff), 1.054882, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general(x2, three_coeff), 1.057894, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general(x2, eight_coeff), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, Clenshaw){
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom(x1, two_coeff), 1.158114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom(x1, three_coeff), 1.183114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom(x2, two_coeff), 1.054882, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom(x2, three_coeff), 1.057894, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom(x2, eight_coeff), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, ClenshawGen){
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general(x1, two_coeff), 1.158114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general(x1, three_coeff), 1.183114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general(x2, two_coeff), 1.054882, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general(x2, three_coeff), 1.057894, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general(x2, eight_coeff), 0.291557, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

