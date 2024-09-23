#include <gtest/gtest.h>

#include "coeff_sqrt_log_power.hpp"

double abs_tol = 1e-6;

double x1 = 10;
double x2 = 83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

// ==========================================
// Vector Tests

TEST(SqrtLogPowerCoeffTest, NaiveVec){
    EXPECT_NEAR(naive_sqrt_log_power_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_vec(x1, two_coeff), 1.758714, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_vec(x1, three_coeff), 2.334360, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_vec(x2, two_coeff), 2.051052, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_vec(x2, three_coeff), 3.155762, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_vec(x2, eight_coeff), 120.959345, abs_tol);
}

TEST(SqrtLogPowerCoeffTest, HornerVec){
    EXPECT_NEAR(horner_sqrt_log_power_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_vec(x1, two_coeff), 1.758714, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_vec(x1, three_coeff), 2.334360, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_vec(x2, two_coeff), 2.051052, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_vec(x2, three_coeff), 3.155762, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_vec(x2, eight_coeff), 120.959345, abs_tol);
}

TEST(SqrtLogPowerCoeffTest, HornerGenVec){
    EXPECT_NEAR(horner_sqrt_log_power_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_vec(x1, two_coeff), 1.758714, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_vec(x1, three_coeff), 2.334360, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_vec(x2, two_coeff), 2.051052, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_vec(x2, three_coeff), 3.155762, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_vec(x2, eight_coeff), 120.959345, abs_tol);
}

TEST(SqrtLogPowerCoeffTest, ClenshawVec){
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_vec(x1, two_coeff), 1.758714, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_vec(x1, three_coeff), 2.334360, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_vec(x2, two_coeff), 2.051052, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_vec(x2, three_coeff), 3.155762, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_vec(x2, eight_coeff), 120.959345, abs_tol);
}

TEST(SqrtLogPowerCoeffTest, ClenshawGenVec){
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_vec(x1, two_coeff), 1.758714, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_vec(x1, three_coeff), 2.334360, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_vec(x2, two_coeff), 2.051052, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_vec(x2, three_coeff), 3.155762, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_vec(x2, eight_coeff), 120.959345, abs_tol);
}

// ==========================================
// Iterator Tests

TEST(SqrtLogPowerCoeffTest, NaiveIter){
    EXPECT_NEAR(naive_sqrt_log_power_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_iter(x1, two_coeff.begin(), two_coeff.end()), 1.758714, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_iter(x1, three_coeff.begin(), three_coeff.end()), 2.334360, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_iter(x2, two_coeff.begin(), two_coeff.end()), 2.051052, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_iter(x2, three_coeff.begin(), three_coeff.end()), 3.155762, abs_tol);
    EXPECT_NEAR(naive_sqrt_log_power_iter(x2, eight_coeff.begin(), eight_coeff.end()), 120.959345, abs_tol);
}

TEST(SqrtLogPowerCoeffTest, HornerIter){
    EXPECT_NEAR(horner_sqrt_log_power_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.758714, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 2.334360, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 2.051052, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 3.155762, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 120.959345, abs_tol);
}

TEST(SqrtLogPowerCoeffTest, HornerGenIter){
    EXPECT_NEAR(horner_sqrt_log_power_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.758714, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_iter(x1, three_coeff.begin(), three_coeff.end()), 2.334360, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_iter(x2, two_coeff.begin(), two_coeff.end()), 2.051052, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_iter(x2, three_coeff.begin(), three_coeff.end()), 3.155762, abs_tol);
    EXPECT_NEAR(horner_sqrt_log_power_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 120.959345, abs_tol);
}

TEST(SqrtLogPowerCoeffTest, ClenshawIter){
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.758714, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 2.334360, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 2.051052, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 3.155762, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 120.959345, abs_tol);
}

TEST(SqrtLogPowerCoeffTest, ClenshawGenIter){
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.758714, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_iter(x1, three_coeff.begin(), three_coeff.end()), 2.334360, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_iter(x2, two_coeff.begin(), two_coeff.end()), 2.051052, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_iter(x2, three_coeff.begin(), three_coeff.end()), 3.155762, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_log_power_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 120.959345, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

