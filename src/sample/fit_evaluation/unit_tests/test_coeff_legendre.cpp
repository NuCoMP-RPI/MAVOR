#include <gtest/gtest.h>

#include "coeff_legendre.hpp"

double abs_tol = 1e-6;

double x1 = 1.0;
double x2 = -0.83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

TEST(LegendreCoeffTest, Naive){
    EXPECT_NEAR(naive_legendre(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_legendre(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(naive_legendre(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(naive_legendre(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_legendre(x2, two_coeff), 0.585, abs_tol);
    EXPECT_NEAR(naive_legendre(x2, three_coeff), 0.718338, abs_tol);
    EXPECT_NEAR(naive_legendre(x2, eight_coeff), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, DirectRecurrence){
    EXPECT_NEAR(direct_recurrence_legendre_custom(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom(x2, two_coeff), 0.585, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom(x2, three_coeff), 0.718338, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom(x2, eight_coeff), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, DirectRecurrenceGen){
    EXPECT_NEAR(direct_recurrence_legendre_general(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general(x2, two_coeff), 0.585, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general(x2, three_coeff), 0.718338, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general(x2, eight_coeff), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, Clenshaw){
    EXPECT_NEAR(clenshaw_legendre_custom(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom(x2, two_coeff), 0.585, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom(x2, three_coeff), 0.718338, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom(x2, eight_coeff), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, ClenshawGen){
    EXPECT_NEAR(clenshaw_legendre_general(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general(x2, two_coeff), 0.585, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general(x2, three_coeff), 0.718338, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general(x2, eight_coeff), -0.9754, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

