#include <gtest/gtest.h>

#include "coeff_exponential.hpp"

double abs_tol = 1e-6;

double x1 = 1.0;
double x2 = -0.83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

// ==========================================
// Vector Tests

TEST(ExponentialCoeffTest, NaiveVec){
    EXPECT_NEAR(naive_exponential_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_exponential_vec(x1, two_coeff), 2.359141, abs_tol);
    EXPECT_NEAR(naive_exponential_vec(x1, three_coeff), 4.206405, abs_tol);
    EXPECT_NEAR(naive_exponential_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_exponential_vec(x2, two_coeff), 1.218025, abs_tol);
    EXPECT_NEAR(naive_exponential_vec(x2, three_coeff), 1.265559, abs_tol);
    EXPECT_NEAR(naive_exponential_vec(x2, eight_coeff), 0.651757, abs_tol);
}

TEST(ExponentialCoeffTest, HornerVec){
    EXPECT_NEAR(horner_exponential_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_vec(x1, two_coeff), 2.359141, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_vec(x1, three_coeff), 4.206405, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_vec(x2, two_coeff), 1.218025, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_vec(x2, three_coeff), 1.265559, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_vec(x2, eight_coeff), 0.651757, abs_tol);
}

TEST(ExponentialCoeffTest, HornerGenVec){
    EXPECT_NEAR(horner_exponential_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_exponential_general_vec(x1, two_coeff), 2.359141, abs_tol);
    EXPECT_NEAR(horner_exponential_general_vec(x1, three_coeff), 4.206405, abs_tol);
    EXPECT_NEAR(horner_exponential_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_exponential_general_vec(x2, two_coeff), 1.218025, abs_tol);
    EXPECT_NEAR(horner_exponential_general_vec(x2, three_coeff), 1.265559, abs_tol);
    EXPECT_NEAR(horner_exponential_general_vec(x2, eight_coeff), 0.651757, abs_tol);
}

TEST(ExponentialCoeffTest, ClenshawVec){
    EXPECT_NEAR(clenshaw_exponential_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_vec(x1, two_coeff), 2.359141, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_vec(x1, three_coeff), 4.206405, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_vec(x2, two_coeff), 1.218025, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_vec(x2, three_coeff), 1.265559, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_vec(x2, eight_coeff), 0.651757, abs_tol);
}

TEST(ExponentialCoeffTest, ClenshawGenVec){
    EXPECT_NEAR(clenshaw_exponential_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_vec(x1, two_coeff), 2.359141, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_vec(x1, three_coeff), 4.206405, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_vec(x2, two_coeff), 1.218025, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_vec(x2, three_coeff), 1.265559, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_vec(x2, eight_coeff), 0.651757, abs_tol);
}

// ==========================================
// Iterator Tests

TEST(ExponentialCoeffTest, NaiveIter){
    EXPECT_NEAR(naive_exponential_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_exponential_iter(x1, two_coeff.begin(), two_coeff.end()), 2.359141, abs_tol);
    EXPECT_NEAR(naive_exponential_iter(x1, three_coeff.begin(), three_coeff.end()), 4.206405, abs_tol);
    EXPECT_NEAR(naive_exponential_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_exponential_iter(x2, two_coeff.begin(), two_coeff.end()), 1.218025, abs_tol);
    EXPECT_NEAR(naive_exponential_iter(x2, three_coeff.begin(), three_coeff.end()), 1.265559, abs_tol);
    EXPECT_NEAR(naive_exponential_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.651757, abs_tol);
}

TEST(ExponentialCoeffTest, HornerIter){
    EXPECT_NEAR(horner_exponential_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 2.359141, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 4.206405, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 1.218025, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 1.265559, abs_tol);
    EXPECT_NEAR(horner_exponential_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.651757, abs_tol);
}

TEST(ExponentialCoeffTest, HornerGenIter){
    EXPECT_NEAR(horner_exponential_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_exponential_general_iter(x1, two_coeff.begin(), two_coeff.end()), 2.359141, abs_tol);
    EXPECT_NEAR(horner_exponential_general_iter(x1, three_coeff.begin(), three_coeff.end()), 4.206405, abs_tol);
    EXPECT_NEAR(horner_exponential_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_exponential_general_iter(x2, two_coeff.begin(), two_coeff.end()), 1.218025, abs_tol);
    EXPECT_NEAR(horner_exponential_general_iter(x2, three_coeff.begin(), three_coeff.end()), 1.265559, abs_tol);
    EXPECT_NEAR(horner_exponential_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.651757, abs_tol);
}

TEST(ExponentialCoeffTest, ClenshawIter){
    EXPECT_NEAR(clenshaw_exponential_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 2.359141, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 4.206405, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 1.218025, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 1.265559, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.651757, abs_tol);
}

TEST(ExponentialCoeffTest, ClenshawGenIter){
    EXPECT_NEAR(clenshaw_exponential_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_iter(x1, two_coeff.begin(), two_coeff.end()), 2.359141, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_iter(x1, three_coeff.begin(), three_coeff.end()), 4.206405, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_iter(x2, two_coeff.begin(), two_coeff.end()), 1.218025, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_iter(x2, three_coeff.begin(), three_coeff.end()), 1.265559, abs_tol);
    EXPECT_NEAR(clenshaw_exponential_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 0.651757, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

