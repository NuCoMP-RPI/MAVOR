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
    result = findSampleInterpolationIndices(reg_vec_1.begin(), reg_vec_1.end(), reg_val_1);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {0, 1};
    result = findSampleInterpolationIndices(reg_vec_1.begin(), reg_vec_1.end(), reg_val_2);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {5, 6};
    result = findSampleInterpolationIndices(reg_vec_1.begin(), reg_vec_1.end(), reg_val_3);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {2, 3};
    result = findSampleInterpolationIndices(reg_vec_1.begin(), reg_vec_1.end(), reg_val_4);
    EXPECT_EQ(expected, result);
}

double test_func(double const & x, Iter begin, Iter end) {
    double f_x = x;
    double val = 0;
    for (auto it = end; it != begin; ) {
        --it;
        val = val * f_x + *it;
    }
    return val;
}

const EvaluationFunction test_sample_search_eval_func = {
    FittingType::Power, 
    EvaluationMethod::HornerCustom, 
    &test_func, 
};

double coeff_val_1 = 20;
double coeff_val_2 = 5;
double coeff_val_3 = 100;
double coeff_val_4 = 8.34;

double eval_point = 3.0;

int num_coeffs_1 = 2;
std::vector<double> coeff_vec_1 = {1, 2, 3, 4, 5, 6, 7, 8};
std::vector<double> eval_vec_1 = {7, 15, 23, 31}; // For reference only, evaluates coeff_vec 

double coeff_val_5 = 400;
double coeff_val_6 = 484;
double coeff_val_7 = 1000;
double coeff_val_8 = -10;

int num_coeffs_2 = 5;
std::vector<double> coeff_vec_2 = {1,1,1,1,1,
                                   2,2,2,2,2,
                                   3,3,3,3,3,
                                   4,4,4,4,4,
                                   5,5,5,5,5,
                                   6,6,6,6,6,
                                   7,7,7,7,7,};
std::vector<double> eval_vec_2 = {121, 242, 363, 484, 605, 726, 847}; // For reference only, evaluates coeff_vec 

TEST(SampleSearchTest, CoeffVector){
    // std::cout << std::endl;
    // findSampleInterpolationIndices(eval_vec_1.begin(), eval_vec_1.end(), coeff_val_1);
    // std::cout << std::endl;
    // findSampleCoeffInterpolationIndices(coeff_vec_1.begin(),
    //                                     coeff_vec_1.end(),
    //                                     coeff_val_1,
    //                                     num_coeffs_1,
    //                                     test_sample_search_eval_func,
    //                                     eval_point);
    // std::cout << std::endl;

    expected = InterpolationIndices {1, 2};
    result = findSampleCoeffInterpolationIndices(coeff_vec_1.begin(),
                                                 coeff_vec_1.end(),
                                                 coeff_val_1,
                                                 num_coeffs_1,
                                                 test_sample_search_eval_func,
                                                 eval_point);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {0, 1};
    result = findSampleCoeffInterpolationIndices(coeff_vec_1.begin(),
                                                 coeff_vec_1.end(),
                                                 coeff_val_2,
                                                 num_coeffs_1,
                                                 test_sample_search_eval_func,
                                                 eval_point);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {2, 3};
    result = findSampleCoeffInterpolationIndices(coeff_vec_1.begin(),
                                                 coeff_vec_1.end(),
                                                 coeff_val_3,
                                                 num_coeffs_1,
                                                 test_sample_search_eval_func,
                                                 eval_point);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {0, 1};
    result = findSampleCoeffInterpolationIndices(coeff_vec_1.begin(),
                                                 coeff_vec_1.end(),
                                                 coeff_val_4,
                                                 num_coeffs_1,
                                                 test_sample_search_eval_func,
                                                 eval_point);
    EXPECT_EQ(expected, result);



    expected = InterpolationIndices {2, 3};
    result = findSampleCoeffInterpolationIndices(coeff_vec_2.begin(),
                                                 coeff_vec_2.end(),
                                                 coeff_val_5,
                                                 num_coeffs_2,
                                                 test_sample_search_eval_func,
                                                 eval_point);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {2, 3};
    result = findSampleCoeffInterpolationIndices(coeff_vec_2.begin(),
                                                 coeff_vec_2.end(),
                                                 coeff_val_6,
                                                 num_coeffs_2,
                                                 test_sample_search_eval_func,
                                                 eval_point);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {5, 6};
    result = findSampleCoeffInterpolationIndices(coeff_vec_2.begin(),
                                                 coeff_vec_2.end(),
                                                 coeff_val_7,
                                                 num_coeffs_2,
                                                 test_sample_search_eval_func,
                                                 eval_point);
    EXPECT_EQ(expected, result);

    expected = InterpolationIndices {0, 1};
    result = findSampleCoeffInterpolationIndices(coeff_vec_2.begin(),
                                                 coeff_vec_2.end(),
                                                 coeff_val_8,
                                                 num_coeffs_2,
                                                 test_sample_search_eval_func,
                                                 eval_point);
    EXPECT_EQ(expected, result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
