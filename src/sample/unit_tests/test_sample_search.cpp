#include <gtest/gtest.h>

#include "sample_search.hpp"

double reg_val_1 = 5.0;
double reg_val_2 = -1;
double reg_val_3 = 100;
double reg_val_4 = 2.34;

std::vector<double> reg_vec_1 = {0, 1, 2, 3, 4, 5, 6};

InterpolationIndices expected;
InterpolationIndices result;

TEST(SampleSearchTest, RegularVector){
    expected = InterpolationIndices {4, 5};
    result = findSampleInterpolationIndices(reg_vec_1.begin(), reg_vec_1.end()-1, reg_val_1);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {0, 1};
    result = findSampleInterpolationIndices(reg_vec_1.begin(), reg_vec_1.end()-1, reg_val_2);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {5, 6};
    result = findSampleInterpolationIndices(reg_vec_1.begin(), reg_vec_1.end()-1, reg_val_3);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {2, 3};
    result = findSampleInterpolationIndices(reg_vec_1.begin(), reg_vec_1.end()-1, reg_val_4);
    EXPECT_EQ(expected, result);
}

std::vector<double> test_func(double const &x, int const &n)
{
    std::vector<double> f(n + 1);
    f[0] = 1;
    double f1_x = x;
    if (n > 0) {f[1] = f1_x;}
    for (int i = 2; i <= n; ++i){
        f[i] = f1_x * f[i-1];
    }
    return f;
}

const EvaluationFunction test_sample_search_eval_func = {
    BasisFunction::Power,
    &test_func, 
};

double coeff_val_1 = 20;
double coeff_val_2 = 5;
double coeff_val_3 = 100;
double coeff_val_4 = 8.34;

double eval_point = 3.0;

int num_coeffs_1 = 2;
std::vector<double> basis_points_1 = test_sample_search_eval_func.eval_basis_func_pointer(eval_point, num_coeffs_1 - 1);
std::vector<double> coeff_vec_1 = {1, 2, 3, 4, 5, 6, 7, 8};
std::vector<double> eval_coeff_vec_1 = {7, 15, 23, 31}; // For reference only, evaluates coeff_vec 

double coeff_val_5 = 400;
double coeff_val_6 = 484;
double coeff_val_7 = 1000;
double coeff_val_8 = -10;

int num_coeffs_2 = 5;
std::vector<double> basis_points_2 = test_sample_search_eval_func.eval_basis_func_pointer(eval_point, num_coeffs_2 - 1);
std::vector<double> coeff_vec_2 = {1,1,1,1,1,
                                   2,2,2,2,2,
                                   3,3,3,3,3,
                                   4,4,4,4,4,
                                   5,5,5,5,5,
                                   6,6,6,6,6,
                                   7,7,7,7,7};
std::vector<double> eval_vec_2 = {121, 242, 363, 484, 605, 726, 847}; // For reference only, evaluates coeff_vec 

TEST(SampleSearchTest, CoeffVectorNum2){
    expected = InterpolationIndices {1, 2};
    result = findSampleCoeffInterpolationIndices(coeff_vec_1.begin(),
                                                 coeff_vec_1.end() - num_coeffs_1,
                                                 coeff_val_1,
                                                 basis_points_1);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {0, 1};
    result = findSampleCoeffInterpolationIndices(coeff_vec_1.begin(),
                                                 coeff_vec_1.end() - num_coeffs_1,
                                                 coeff_val_2,
                                                 basis_points_1);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {2, 3};
    result = findSampleCoeffInterpolationIndices(coeff_vec_1.begin(),
                                                 coeff_vec_1.end() - num_coeffs_1,
                                                 coeff_val_3,
                                                 basis_points_1);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {0, 1};
    result = findSampleCoeffInterpolationIndices(coeff_vec_1.begin(),
                                                 coeff_vec_1.end() - num_coeffs_1,
                                                 coeff_val_4,
                                                 basis_points_1);
    EXPECT_EQ(expected, result);
}

TEST(SampleSearchTest, CoeffVectorNum5){
    expected = InterpolationIndices {2, 3};
    result = findSampleCoeffInterpolationIndices(coeff_vec_2.begin(),
                                                 coeff_vec_2.end() - num_coeffs_2,
                                                 coeff_val_5,
                                                 basis_points_2);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {2, 3};
    result = findSampleCoeffInterpolationIndices(coeff_vec_2.begin(),
                                                 coeff_vec_2.end() - num_coeffs_2,
                                                 coeff_val_6,
                                                 basis_points_2);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {5, 6};
    result = findSampleCoeffInterpolationIndices(coeff_vec_2.begin(),
                                                 coeff_vec_2.end() - num_coeffs_2,
                                                 coeff_val_7,
                                                 basis_points_2);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {0, 1};
    result = findSampleCoeffInterpolationIndices(coeff_vec_2.begin(),
                                                 coeff_vec_2.end() - num_coeffs_2,
                                                 coeff_val_8,
                                                 basis_points_2);
    EXPECT_EQ(expected, result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
