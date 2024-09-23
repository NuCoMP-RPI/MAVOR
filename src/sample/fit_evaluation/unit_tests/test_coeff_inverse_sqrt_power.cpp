#include <gtest/gtest.h>

#include "coeff_inverse_sqrt_power.hpp"

double abs_tol = 1e-6;

double x1 = 10;
double x2 = 83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

// ==========================================
// Vector Tests

TEST(InverseSqrtPowerCoeffTest, NaiveVec){
    EXPECT_NEAR(naive_inverse_sqrt_power_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_vec(x1, two_coeff), 1.158114, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_vec(x1, three_coeff), 1.183114, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_vec(x2, two_coeff), 1.054882, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_vec(x2, three_coeff), 1.057894, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_vec(x2, eight_coeff), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, HornerVec){
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_vec(x1, two_coeff), 1.158114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_vec(x1, three_coeff), 1.183114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_vec(x2, two_coeff), 1.054882, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_vec(x2, three_coeff), 1.057894, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_vec(x2, eight_coeff), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, HornerGenVec){
    EXPECT_NEAR(horner_inverse_sqrt_power_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_vec(x1, two_coeff), 1.158114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_vec(x1, three_coeff), 1.183114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_vec(x2, two_coeff), 1.054882, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_vec(x2, three_coeff), 1.057894, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_vec(x2, eight_coeff), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, ClenshawVec){
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_vec(x1, two_coeff), 1.158114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_vec(x1, three_coeff), 1.183114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_vec(x2, two_coeff), 1.054882, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_vec(x2, three_coeff), 1.057894, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_vec(x2, eight_coeff), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, ClenshawGenVec){
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_vec(x1, two_coeff), 1.158114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_vec(x1, three_coeff), 1.183114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_vec(x2, two_coeff), 1.054882, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_vec(x2, three_coeff), 1.057894, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_vec(x2, eight_coeff), 0.291557, abs_tol);
}

// ==========================================
// Iterator Tests

TEST(InverseSqrtPowerCoeffTest, NaiveIter){
    EXPECT_NEAR(naive_inverse_sqrt_power_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_iter(x1, two_coeff.begin(), two_coeff.end()), 1.158114, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_iter(x1, three_coeff.begin(), three_coeff.end()), 1.183114, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_iter(x2, two_coeff.begin(), two_coeff.end()), 1.054882, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_iter(x2, three_coeff.begin(), three_coeff.end()), 1.057894, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_power_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, HornerIter){
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.158114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 1.183114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 1.054882, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 1.057894, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, HornerGenIter){
    EXPECT_NEAR(horner_inverse_sqrt_power_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.158114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_iter(x1, three_coeff.begin(), three_coeff.end()), 1.183114, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_iter(x2, two_coeff.begin(), two_coeff.end()), 1.054882, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_iter(x2, three_coeff.begin(), three_coeff.end()), 1.057894, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_power_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, ClenshawIter){
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.158114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 1.183114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 1.054882, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 1.057894, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.291557, abs_tol);
}

TEST(InverseSqrtPowerCoeffTest, ClenshawGenIter){
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.158114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_iter(x1, three_coeff.begin(), three_coeff.end()), 1.183114, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_iter(x2, two_coeff.begin(), two_coeff.end()), 1.054882, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_iter(x2, three_coeff.begin(), three_coeff.end()), 1.057894, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_power_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.291557, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

