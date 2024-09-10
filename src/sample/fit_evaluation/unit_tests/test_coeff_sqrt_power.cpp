#include <gtest/gtest.h>

#include "coeff_sqrt_power.hpp"

double abs_tol = 1e-6;

double x1 = 10;
double x2 = 83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

TEST(SqrtPowerCoeffTest, Naive){
    EXPECT_NEAR(naive_sqrt_power(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_sqrt_power(x1, two_coeff), 2.581139, abs_tol);
    EXPECT_NEAR(naive_sqrt_power(x1, three_coeff), 5.081139, abs_tol);
    EXPECT_NEAR(naive_sqrt_power(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_sqrt_power(x2, two_coeff), 5.555217, abs_tol);
    EXPECT_NEAR(naive_sqrt_power(x2, three_coeff), 26.305217, abs_tol);
    EXPECT_NEAR(naive_sqrt_power(x2, eight_coeff), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, Horner){
    EXPECT_NEAR(horner_sqrt_power_custom(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom(x1, two_coeff), 2.581139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom(x1, three_coeff), 5.081139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom(x2, two_coeff), 5.555217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom(x2, three_coeff), 26.305217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_custom(x2, eight_coeff), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, HornerGen){
    EXPECT_NEAR(horner_sqrt_power_general(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general(x1, two_coeff), 2.581139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general(x1, three_coeff), 5.081139, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general(x2, two_coeff), 5.555217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general(x2, three_coeff), 26.305217, abs_tol);
    EXPECT_NEAR(horner_sqrt_power_general(x2, eight_coeff), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, Clenshaw){
    EXPECT_NEAR(clenshaw_sqrt_power_custom(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom(x1, two_coeff), 2.581139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom(x1, three_coeff), 5.081139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom(x2, two_coeff), 5.555217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom(x2, three_coeff), 26.305217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_custom(x2, eight_coeff), 1162138.734698, abs_tol);
}

TEST(SqrtPowerCoeffTest, ClenshawGen){
    EXPECT_NEAR(clenshaw_sqrt_power_general(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general(x1, two_coeff), 2.581139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general(x1, three_coeff), 5.081139, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general(x2, two_coeff), 5.555217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general(x2, three_coeff), 26.305217, abs_tol);
    EXPECT_NEAR(clenshaw_sqrt_power_general(x2, eight_coeff), 1162138.734698, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

