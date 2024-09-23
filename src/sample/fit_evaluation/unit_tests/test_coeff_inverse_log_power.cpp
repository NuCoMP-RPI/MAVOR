#include <gtest/gtest.h>

#include "coeff_inverse_log_power.hpp"

double abs_tol = 1e-6;

double x1 = 10;
double x2 = 83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

// ==========================================
// Vector Tests

TEST(InverseLogPowerCoeffTest, NaiveVec){
    EXPECT_NEAR(naive_inverse_log_power_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_vec(x1, two_coeff), 1.217147, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_vec(x1, three_coeff), 1.264300, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_vec(x2, two_coeff), 1.113152, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_vec(x2, three_coeff), 1.125955, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_vec(x2, eight_coeff), 0.406954, abs_tol);
}

TEST(InverseLogPowerCoeffTest, HornerVec){
    EXPECT_NEAR(horner_inverse_log_power_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_vec(x1, two_coeff), 1.217147, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_vec(x1, three_coeff), 1.264300, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_vec(x2, two_coeff), 1.113152, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_vec(x2, three_coeff), 1.125955, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_vec(x2, eight_coeff), 0.406954, abs_tol);
}

TEST(InverseLogPowerCoeffTest, HornerGenVec){
    EXPECT_NEAR(horner_inverse_log_power_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_vec(x1, two_coeff), 1.217147, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_vec(x1, three_coeff), 1.264300, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_vec(x2, two_coeff), 1.113152, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_vec(x2, three_coeff), 1.125955, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_vec(x2, eight_coeff), 0.406954, abs_tol);
}

TEST(InverseLogPowerCoeffTest, ClenshawVec){
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_vec(x1, two_coeff), 1.217147, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_vec(x1, three_coeff), 1.264300, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_vec(x2, two_coeff), 1.113152, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_vec(x2, three_coeff), 1.125955, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_vec(x2, eight_coeff), 0.406954, abs_tol);
}

TEST(InverseLogPowerCoeffTest, ClenshawGenVec){
    EXPECT_NEAR(clenshaw_inverse_log_power_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_vec(x1, two_coeff), 1.217147, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_vec(x1, three_coeff), 1.264300, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_vec(x2, two_coeff), 1.113152, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_vec(x2, three_coeff), 1.125955, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_vec(x2, eight_coeff), 0.406954, abs_tol);
}

// ==========================================
// Iterator Tests

TEST(InverseLogPowerCoeffTest, NaiveIter){
    EXPECT_NEAR(naive_inverse_log_power_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_iter(x1, two_coeff.begin(), two_coeff.end()), 1.217147, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_iter(x1, three_coeff.begin(), three_coeff.end()), 1.264300, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_iter(x2, two_coeff.begin(), two_coeff.end()), 1.113152, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_iter(x2, three_coeff.begin(), three_coeff.end()), 1.125955, abs_tol);
    EXPECT_NEAR(naive_inverse_log_power_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.406954, abs_tol);
}

TEST(InverseLogPowerCoeffTest, HornerIter){
    EXPECT_NEAR(horner_inverse_log_power_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.217147, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 1.264300, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 1.113152, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 1.125955, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.406954, abs_tol);
}

TEST(InverseLogPowerCoeffTest, HornerGenIter){
    EXPECT_NEAR(horner_inverse_log_power_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.217147, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_iter(x1, three_coeff.begin(), three_coeff.end()), 1.264300, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_iter(x2, two_coeff.begin(), two_coeff.end()), 1.113152, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_iter(x2, three_coeff.begin(), three_coeff.end()), 1.125955, abs_tol);
    EXPECT_NEAR(horner_inverse_log_power_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.406954, abs_tol);
}

TEST(InverseLogPowerCoeffTest, ClenshawIter){
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.217147, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 1.264300, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 1.113152, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 1.125955, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.406954, abs_tol);
}

TEST(InverseLogPowerCoeffTest, ClenshawGenIter){
    EXPECT_NEAR(clenshaw_inverse_log_power_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.217147, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_iter(x1, three_coeff.begin(), three_coeff.end()), 1.264300, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_iter(x2, two_coeff.begin(), two_coeff.end()), 1.113152, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_iter(x2, three_coeff.begin(), three_coeff.end()), 1.125955, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_log_power_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.406954, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

