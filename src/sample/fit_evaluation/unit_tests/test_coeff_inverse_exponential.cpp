#include <gtest/gtest.h>

#include "coeff_inverse_exponential.hpp"

double abs_tol = 1e-6;

double x1 = 1.0;
double x2 = -0.83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

// ==========================================
// Vector Tests

TEST(InverseExponentialCoeffTest, NaiveVec){
    EXPECT_NEAR(naive_inverse_exponential_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_vec(x1, two_coeff), 1.18394, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_vec(x1, three_coeff), 1.217774, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_vec(x2, two_coeff), 2.146659, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_vec(x2, three_coeff), 3.461487, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_vec(x2, eight_coeff), 201.439439, abs_tol);
}

TEST(InverseExponentialCoeffTest, HornerVec){
    EXPECT_NEAR(horner_inverse_exponential_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_vec(x1, two_coeff), 1.18394, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_vec(x1, three_coeff), 1.217774, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_vec(x2, two_coeff), 2.146659, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_vec(x2, three_coeff), 3.461487, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_vec(x2, eight_coeff), 201.439439, abs_tol);
}

TEST(InverseExponentialCoeffTest, HornerGenVec){
    EXPECT_NEAR(horner_inverse_exponential_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_vec(x1, two_coeff), 1.18394, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_vec(x1, three_coeff), 1.217774, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_vec(x2, two_coeff), 2.146659, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_vec(x2, three_coeff), 3.461487, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_vec(x2, eight_coeff), 201.439439, abs_tol);
}

TEST(InverseExponentialCoeffTest, ClenshawVec){
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_vec(x1, two_coeff), 1.18394, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_vec(x1, three_coeff), 1.217774, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_vec(x2, two_coeff), 2.146659, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_vec(x2, three_coeff), 3.461487, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_vec(x2, eight_coeff), 201.439439, abs_tol);
}

TEST(InverseExponentialCoeffTest, ClenshawGenVec){
    EXPECT_NEAR(clenshaw_inverse_exponential_general_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_vec(x1, two_coeff), 1.18394, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_vec(x1, three_coeff), 1.217774, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_vec(x2, two_coeff), 2.146659, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_vec(x2, three_coeff), 3.461487, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_vec(x2, eight_coeff), 201.439439, abs_tol);
}

// ==========================================
// Iterator Tests

TEST(InverseExponentialCoeffTest, NaiveIter){
    EXPECT_NEAR(naive_inverse_exponential_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_iter(x1, two_coeff.begin(), two_coeff.end()), 1.18394, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_iter(x1, three_coeff.begin(), three_coeff.end()), 1.217774, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_iter(x2, two_coeff.begin(), two_coeff.end()), 2.146659, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_iter(x2, three_coeff.begin(), three_coeff.end()), 3.461487, abs_tol);
    EXPECT_NEAR(naive_inverse_exponential_iter(x2, eight_coeff.begin(), eight_coeff.end()), 201.439439, abs_tol);
}

TEST(InverseExponentialCoeffTest, HornerIter){
    EXPECT_NEAR(horner_inverse_exponential_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.18394, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 1.217774, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 2.146659, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 3.461487, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 201.439439, abs_tol);
}

TEST(InverseExponentialCoeffTest, HornerGenIter){
    EXPECT_NEAR(horner_inverse_exponential_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.18394, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_iter(x1, three_coeff.begin(), three_coeff.end()), 1.217774, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_iter(x2, two_coeff.begin(), two_coeff.end()), 2.146659, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_iter(x2, three_coeff.begin(), three_coeff.end()), 3.461487, abs_tol);
    EXPECT_NEAR(horner_inverse_exponential_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 201.439439, abs_tol);
}

TEST(InverseExponentialCoeffTest, ClenshawIter){
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_iter(x1, two_coeff.begin(), two_coeff.end()), 1.18394, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_iter(x1, three_coeff.begin(), three_coeff.end()), 1.217774, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_iter(x2, two_coeff.begin(), two_coeff.end()), 2.146659, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_iter(x2, three_coeff.begin(), three_coeff.end()), 3.461487, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_custom_iter(x2, eight_coeff.begin(), eight_coeff.end()), 201.439439, abs_tol);
}

TEST(InverseExponentialCoeffTest, ClenshawGenIter){
    EXPECT_NEAR(clenshaw_inverse_exponential_general_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_iter(x1, two_coeff.begin(), two_coeff.end()), 1.18394, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_iter(x1, three_coeff.begin(), three_coeff.end()), 1.217774, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_iter(x2, two_coeff.begin(), two_coeff.end()), 2.146659, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_iter(x2, three_coeff.begin(), three_coeff.end()), 3.461487, abs_tol);
    EXPECT_NEAR(clenshaw_inverse_exponential_general_iter(x2, eight_coeff.begin(), eight_coeff.end()), 201.439439, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

