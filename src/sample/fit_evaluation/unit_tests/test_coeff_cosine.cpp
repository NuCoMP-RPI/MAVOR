#include <gtest/gtest.h>

#include "coeff_cosine.hpp"

double abs_tol = 1e-6;

double x1 = 1.0;
double x2 = -0.83;
std::vector<double> one_coeff = {1.0};
std::vector<double> two_coeff = {1.0, 0.5};
std::vector<double> three_coeff = {1.0, 0.5, 0.25};
std::vector<double> eight_coeff = {0.18661, 0.95043, 0.02022, 0.22670, 0.52323, 0.16626, 0.89749, 0.12185};

// ==========================================
// Vector Tests

TEST(CosineCoeffTest, NaiveVec){
    EXPECT_NEAR(naive_cosine_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_cosine_vec(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(naive_cosine_vec(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(naive_cosine_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(naive_cosine_vec(x2, two_coeff), 1.240877, abs_tol);
    EXPECT_NEAR(naive_cosine_vec(x2, three_coeff), 1.10692, abs_tol);
    EXPECT_NEAR(naive_cosine_vec(x2, eight_coeff), 1.21761, abs_tol);
}

TEST(CosineCoeffTest, ImprovedVec){
    EXPECT_NEAR(improved_cosine_vec(x1, one_coeff), 1, abs_tol);
    EXPECT_NEAR(improved_cosine_vec(x1, two_coeff), 1.5, abs_tol);
    EXPECT_NEAR(improved_cosine_vec(x1, three_coeff), 1.75, abs_tol);
    EXPECT_NEAR(improved_cosine_vec(x2, one_coeff), 1, abs_tol);
    EXPECT_NEAR(improved_cosine_vec(x2, two_coeff), 1.240877, abs_tol);
    EXPECT_NEAR(improved_cosine_vec(x2, three_coeff), 1.10692, abs_tol);
    EXPECT_NEAR(improved_cosine_vec(x2, eight_coeff), 1.21761, abs_tol);
}

// ==========================================
// Iterator Tests

TEST(CosineCoeffTest, NaiveIter){
    EXPECT_NEAR(naive_cosine_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_cosine_iter(x1, two_coeff.begin(), two_coeff.end()), 1.5, abs_tol);
    EXPECT_NEAR(naive_cosine_iter(x1, three_coeff.begin(), three_coeff.end()), 1.75, abs_tol);
    EXPECT_NEAR(naive_cosine_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(naive_cosine_iter(x2, two_coeff.begin(), two_coeff.end()), 1.240877, abs_tol);
    EXPECT_NEAR(naive_cosine_iter(x2, three_coeff.begin(), three_coeff.end()), 1.10692, abs_tol);
    EXPECT_NEAR(naive_cosine_iter(x2, eight_coeff.begin(), eight_coeff.end()), 1.21761, abs_tol);
}

TEST(CosineCoeffTest, ImprovedIter){
    EXPECT_NEAR(improved_cosine_iter(x1, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(improved_cosine_iter(x1, two_coeff.begin(), two_coeff.end()), 1.5, abs_tol);
    EXPECT_NEAR(improved_cosine_iter(x1, three_coeff.begin(), three_coeff.end()), 1.75, abs_tol);
    EXPECT_NEAR(improved_cosine_iter(x2, one_coeff.begin(), one_coeff.end()), 1, abs_tol);
    EXPECT_NEAR(improved_cosine_iter(x2, two_coeff.begin(), two_coeff.end()), 1.240877, abs_tol);
    EXPECT_NEAR(improved_cosine_iter(x2, three_coeff.begin(), three_coeff.end()), 1.10692, abs_tol);
    EXPECT_NEAR(improved_cosine_iter(x2, eight_coeff.begin(), eight_coeff.end()), 1.21761, abs_tol);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

