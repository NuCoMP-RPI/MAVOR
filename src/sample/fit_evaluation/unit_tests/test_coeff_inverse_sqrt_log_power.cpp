#include <gtest/gtest.h>

#include "coeff_inverse_sqrt_log_power.hpp"

double abs_tol = 1e-6;

double x1 = 10;
double x2 = 83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

// ==========================================
// Vector Tests

TEST(InverseSqrtLogPowerCoeffTest, NaiveVec){
    EXPECT_NEAR(naive_inverse_sqrt_log_power_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_vec(x1, two_coeff), 1.329505, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_vec(x1, three_coeff), 1.438079, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_vec(x2, two_coeff), 1.237857, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_vec(x2, three_coeff), 1.294433, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_vec(x2, eight_coeff), 0.709645, abs_tol);
}

TEST(InverseSqrtLogPowerCoeffTest, HornerVec){
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_vec(x1, two_coeff), 1.329505, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_vec(x1, three_coeff), 1.438079, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_vec(x2, two_coeff), 1.237857, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_vec(x2, three_coeff), 1.294433, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_vec(x2, eight_coeff), 0.709645, abs_tol);
}

TEST(InverseSqrtLogPowerCoeffTest, HornerGenVec){
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_vec(x1, two_coeff), 1.329505, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_vec(x1, three_coeff), 1.438079, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_vec(x2, two_coeff), 1.237857, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_vec(x2, three_coeff), 1.294433, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_vec(x2, eight_coeff), 0.709645, abs_tol);
}

TEST(InverseSqrtLogPowerCoeffTest, ClenshawVec){
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_vec(x1, two_coeff), 1.329505, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_vec(x1, three_coeff), 1.438079, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_vec(x2, two_coeff), 1.237857, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_vec(x2, three_coeff), 1.294433, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_vec(x2, eight_coeff), 0.709645, abs_tol);
}

TEST(InverseSqrtLogPowerCoeffTest, ClenshawGenVec){
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_vec(x1, two_coeff), 1.329505, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_vec(x1, three_coeff), 1.438079, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_vec(x2, two_coeff), 1.237857, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_vec(x2, three_coeff), 1.294433, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_vec(x2, eight_coeff), 0.709645, abs_tol);
}

// ==========================================
// Iterator Tests

TEST(InverseSqrtLogPowerCoeffTest, NaiveIter){
    EXPECT_NEAR(naive_inverse_sqrt_log_power_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_iter(x1, two_coeff.begin(), two_coeff.end()), 1.329505, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_iter(x1, three_coeff.begin(), three_coeff.end()), 1.438079, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_iter(x2, two_coeff.begin(), two_coeff.end()), 1.237857, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_iter(x2, three_coeff.begin(), three_coeff.end()), 1.294433, abs_tol);
    EXPECT_NEAR(naive_inverse_sqrt_log_power_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.709645, abs_tol);
}

TEST(InverseSqrtLogPowerCoeffTest, HornerIter){
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.329505, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 1.438079, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 1.237857, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 1.294433, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.709645, abs_tol);
}

TEST(InverseSqrtLogPowerCoeffTest, HornerGenIter){
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.329505, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_iter(x1, three_coeff.begin(), three_coeff.end()), 1.438079, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_iter(x2, two_coeff.begin(), two_coeff.end()), 1.237857, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_iter(x2, three_coeff.begin(), three_coeff.end()), 1.294433, abs_tol);
    EXPECT_NEAR(horner_inverse_sqrt_log_power_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.709645, abs_tol);
}

TEST(InverseSqrtLogPowerCoeffTest, ClenshawIter){
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.329505, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 1.438079, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 1.237857, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 1.294433, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.709645, abs_tol);
}

TEST(InverseSqrtLogPowerCoeffTest, ClenshawGenIter){
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.329505, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_iter(x1, three_coeff.begin(), three_coeff.end()), 1.438079, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_iter(x2, two_coeff.begin(), two_coeff.end()), 1.237857, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_iter(x2, three_coeff.begin(), three_coeff.end()), 1.294433, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_sqrt_log_power_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.709645, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

