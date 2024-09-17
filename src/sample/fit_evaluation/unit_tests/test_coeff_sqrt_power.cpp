#include <gtest/gtest.h>

#include "coeff_sqrt_power.hpp"

double abs_tol = 1e-6;

double x1 = 10;
double x2 = 83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

// ==========================================
// Vector Tests

TEST(SqrtPowerCoeffTest, NaiveVec){
    EXPECT_NEAR(naive_sqrt_power_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_vec(x1, two_coeff), 2.581139, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_vec(x1, three_coeff), 5.081139, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_vec(x2, two_coeff), 5.555217, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_vec(x2, three_coeff), 26.305217, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_vec(x2, eight_coeff), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, HornerVec){
    EXPECT_NEAR(horner_sqrt_power_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_vec(x1, two_coeff), 2.581139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_vec(x1, three_coeff), 5.081139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_vec(x2, two_coeff), 5.555217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_vec(x2, three_coeff), 26.305217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_vec(x2, eight_coeff), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, HornerGenVec){
    EXPECT_NEAR(horner_sqrt_power_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_vec(x1, two_coeff), 2.581139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_vec(x1, three_coeff), 5.081139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_vec(x2, two_coeff), 5.555217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_vec(x2, three_coeff), 26.305217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_vec(x2, eight_coeff), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, ClenshawVec){
    EXPECT_NEAR(clenshaw_sqrt_power_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_vec(x1, two_coeff), 2.581139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_vec(x1, three_coeff), 5.081139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_vec(x2, two_coeff), 5.555217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_vec(x2, three_coeff), 26.305217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_vec(x2, eight_coeff), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, ClenshawGenVec){
    EXPECT_NEAR(clenshaw_sqrt_power_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_vec(x1, two_coeff), 2.581139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_vec(x1, three_coeff), 5.081139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_vec(x2, two_coeff), 5.555217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_vec(x2, three_coeff), 26.305217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_vec(x2, eight_coeff), 1162138.734698, abs_tol);
}

// ==========================================
// Iterator Tests

TEST(SqrtPowerCoeffTest, NaiveIter){
    EXPECT_NEAR(naive_sqrt_power_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_iter(x1, two_coeff.begin(), two_coeff.end()), 2.581139, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_iter(x1, three_coeff.begin(), three_coeff.end()), 5.081139, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_iter(x2, two_coeff.begin(), two_coeff.end()), 5.555217, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_iter(x2, three_coeff.begin(), three_coeff.end()), 26.305217, abs_tol);
    EXPECT_NEAR(naive_sqrt_power_iter(x2, eight_coeff.begin(), eight_coeff.end()), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, HornerIter){
    EXPECT_NEAR(horner_sqrt_power_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 2.581139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 5.081139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 5.555217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 26.305217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, HornerGenIter){
    EXPECT_NEAR(horner_sqrt_power_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_iter(x1, two_coeff.begin(), two_coeff.end()), 2.581139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_iter(x1, three_coeff.begin(), three_coeff.end()), 5.081139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_iter(x2, two_coeff.begin(), two_coeff.end()), 5.555217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_iter(x2, three_coeff.begin(), three_coeff.end()), 26.305217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, ClenshawIter){
    EXPECT_NEAR(clenshaw_sqrt_power_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 2.581139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 5.081139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 5.555217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 26.305217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, ClenshawGenIter){
    EXPECT_NEAR(clenshaw_sqrt_power_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_iter(x1, two_coeff.begin(), two_coeff.end()), 2.581139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_iter(x1, three_coeff.begin(), three_coeff.end()), 5.081139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_iter(x2, two_coeff.begin(), two_coeff.end()), 5.555217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_iter(x2, three_coeff.begin(), three_coeff.end()), 26.305217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 1162138.734698, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

