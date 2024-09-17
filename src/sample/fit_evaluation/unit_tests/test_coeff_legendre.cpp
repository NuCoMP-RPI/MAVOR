#include <gtest/gtest.h>

#include "coeff_legendre.hpp"

double abs_tol = 1e-6;

double x1 = 1.0;
double x2 = -0.83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

// ==========================================
// Vector Tests

TEST(LegendreCoeffTest, NaiveVec){
    EXPECT_NEAR(naive_legendre_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_legendre_vec(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(naive_legendre_vec(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(naive_legendre_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_legendre_vec(x2, two_coeff), 0.585, abs_tol);
    EXPECT_NEAR(naive_legendre_vec(x2, three_coeff), 0.718338, abs_tol);
    EXPECT_NEAR(naive_legendre_vec(x2, eight_coeff), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, DirectRecurrenceVec){
    EXPECT_NEAR(direct_recurrence_legendre_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_vec(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_vec(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_vec(x2, two_coeff), 0.585, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_vec(x2, three_coeff), 0.718338, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_vec(x2, eight_coeff), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, DirectRecurrenceGenVec){
    EXPECT_NEAR(direct_recurrence_legendre_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_vec(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_vec(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_vec(x2, two_coeff), 0.585, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_vec(x2, three_coeff), 0.718338, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_vec(x2, eight_coeff), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, ClenshawVec){
    EXPECT_NEAR(clenshaw_legendre_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_vec(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_vec(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_vec(x2, two_coeff), 0.585, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_vec(x2, three_coeff), 0.718338, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_vec(x2, eight_coeff), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, ClenshawGenVec){
    EXPECT_NEAR(clenshaw_legendre_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_vec(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_vec(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_vec(x2, two_coeff), 0.585, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_vec(x2, three_coeff), 0.718338, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_vec(x2, eight_coeff), -0.9754, abs_tol);
}

// ==========================================
// Iterator Tests

TEST(LegendreCoeffTest, NaiveIter){
    EXPECT_NEAR(naive_legendre_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_legendre_iter(x1, two_coeff.begin(), two_coeff.end()), 1.5, abs_tol);
    EXPECT_NEAR(naive_legendre_iter(x1, three_coeff.begin(), three_coeff.end()), 1.75, abs_tol);
    EXPECT_NEAR(naive_legendre_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_legendre_iter(x2, two_coeff.begin(), two_coeff.end()), 0.585, abs_tol);
    EXPECT_NEAR(naive_legendre_iter(x2, three_coeff.begin(), three_coeff.end()), 0.718338, abs_tol);
    EXPECT_NEAR(naive_legendre_iter(x2, eight_coeff.begin(), eight_coeff.end()), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, DirectRecurrenceIter){
    EXPECT_NEAR(direct_recurrence_legendre_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.5, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 1.75, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 0.585, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 0.718338, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, DirectRecurrenceGenIter){
    EXPECT_NEAR(direct_recurrence_legendre_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.5, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_iter(x1, three_coeff.begin(), three_coeff.end()), 1.75, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_iter(x2, two_coeff.begin(), two_coeff.end()), 0.585, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_iter(x2, three_coeff.begin(), three_coeff.end()), 0.718338, abs_tol);
    EXPECT_NEAR(direct_recurrence_legendre_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, ClenshawIter){
    EXPECT_NEAR(clenshaw_legendre_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.5, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 1.75, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 0.585, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 0.718338, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), -0.9754, abs_tol);
}

TEST(LegendreCoeffTest, ClenshawGenIter){
    EXPECT_NEAR(clenshaw_legendre_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.5, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_iter(x1, three_coeff.begin(), three_coeff.end()), 1.75, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_iter(x2, two_coeff.begin(), two_coeff.end()), 0.585, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_iter(x2, three_coeff.begin(), three_coeff.end()), 0.718338, abs_tol);
    EXPECT_NEAR(clenshaw_legendre_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), -0.9754, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

