#include <filesystem>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <highfive/highfive.hpp>

#include "constants.hpp"

#include "file_read.hpp"

class TslFileDataTest : public ::testing::Test {
protected:
    std::string hdf5_test_file = "test_data.h5";

    void SetUp() override {
        // Based loosely on HinYH2
        HighFive::File file(hdf5_test_file, HighFive::File::Overwrite);
        file.createDataSet("lat", 1);
        file.createDataSet("lasym", 0);
        file.createDataSet("lln", 0);
        file.createDataSet("za", 105);
        file.createDataSet("mat", 5);

        file.createDataSet("temp", 333.6);
        file.createDataSet("t_eff", 741.6298);
        file.createDataSet("temp_ratio", 2.2231109112709833);
        file.createDataSet("a0", 0.999167);
        file.createDataSet("e_max", 4.999988);
        file.createDataSet("m0", 1.0);
        file.createDataSet("free_xs", 20.4363);
        file.createDataSet("bound_xs", 81.81336472516202);
        
        std::vector<double> alphas{0.5, 1.0, 1.5, 2.0};
        std::vector<double> betas{2.5, 3.0, 3.5, 4.0};

        file.createDataSet("alphas", alphas);
        file.createDataSet("betas", betas);

        file.createDataSet("alpha_interpolants", std::vector<int>{4});
        file.createDataSet("alpha_interpolants_boundaries", std::vector<int>{4});
        file.createDataSet("beta_interpolants", std::vector<int>{4});
        file.createDataSet("beta_interpolants_boundaries", std::vector<int>{4});
        
        file.createDataSet("tsl_vals", std::vector<std::vector<double>>{
            {1.25, 1.5, 1.75, 2.0},
            {2.5, 3.0, 3.5, 4.0},
            {3.75, 4.5, 5.25, 6.0},
            {5.0, 6.0, 7.0, 8.0}
        });
    }

    void TearDown() override {
        std::filesystem::remove(hdf5_test_file);
    }
};

double abs_tol = 1e-8;

TEST_F(TslFileDataTest, Constructor_HDF5){
    EXPECT_NO_THROW(TslFileData tsl_data(hdf5_test_file, "hdf5"));
}

TEST_F(TslFileDataTest, ReturnInterpSchemes){
    TslFileData tsl_data(hdf5_test_file);
    EXPECT_EQ(tsl_data.return_alpha_schemes(), 4);
    EXPECT_EQ(tsl_data.return_beta_schemes(), 4);
}

TEST_F(TslFileDataTest, ReturnAlphaBetas){
    TslFileData tsl_data(hdf5_test_file);

    std::vector<double> expected_alphas{0.5, 1.0, 1.5, 2.0};
    std::vector<double> expected_betas{2.5, 3.0, 3.5, 4.0};

    double scale_factor = ref_temp_k/tsl_data.temp;

    std::vector<double> expected_scaled_alphas{scale_factor*0.5, scale_factor*1.0, scale_factor*1.5, scale_factor*2.0};
    std::vector<double> expected_scaled_betas{scale_factor*2.5, scale_factor*3.0, scale_factor*3.5, scale_factor*4.0};

    std::vector<double> expected_full_betas{-4.0, -3.5, -3.0, -2.5, 2.5, 3.0, 3.5, 4.0};
    std::vector<double> expected_full_scaled_betas{scale_factor*-4.0, scale_factor*-3.5, scale_factor*-3.0, scale_factor*-2.5, scale_factor*2.5, scale_factor*3.0, scale_factor*3.5, scale_factor*4.0};

    EXPECT_THAT(tsl_data.return_alphas(), testing::Pointwise(testing::DoubleNear(abs_tol), expected_alphas));
    EXPECT_THAT(tsl_data.return_betas(), testing::Pointwise(testing::DoubleNear(abs_tol), expected_betas));

    EXPECT_THAT(tsl_data.return_scaled_alphas(), testing::Pointwise(testing::DoubleNear(abs_tol), expected_scaled_alphas));
    EXPECT_THAT(tsl_data.return_scaled_betas(), testing::Pointwise(testing::DoubleNear(abs_tol), expected_scaled_betas));

    EXPECT_THAT(tsl_data.return_full_betas(), testing::Pointwise(testing::DoubleNear(abs_tol), expected_full_betas));
    EXPECT_THAT(tsl_data.return_full_scaled_betas(), testing::Pointwise(testing::DoubleNear(abs_tol), expected_full_scaled_betas));
}

TEST_F(TslFileDataTest, ReturnTSLVal){
    TslFileData tsl_data(hdf5_test_file);

    // Check that the stored values match
    std::vector<std::vector<double>>expected_tsl{
            {1.25, 1.5, 1.75, 2.0},
            {2.5, 3.0, 3.5, 4.0},
            {3.75, 4.5, 5.25, 6.0},
            {5.0, 6.0, 7.0, 8.0}
        };

    const auto& tsl_vals = tsl_data.return_tsl_vals();
    
    for (int i = 0; i < tsl_vals.size(); i++) {
        EXPECT_THAT(tsl_vals[i], testing::Pointwise(testing::DoubleNear(abs_tol), expected_tsl[i]));
    }
}

TEST_F(TslFileDataTest, ReturnArbTSLVal){
    TslFileData tsl_data(hdf5_test_file);

    std::vector<std::vector<double>> true_tsl_vals = tsl_data.return_full_asym_tsl_vals();
    std::vector<double> alphas = tsl_data.return_scaled_alphas();
    std::vector<double> betas = tsl_data.return_full_scaled_betas();

    for (int i = 0; i < betas.size(); i++){
        for (int j = 0; j < alphas.size(); j++){
            EXPECT_NEAR(true_tsl_vals[i][j], tsl_data.return_arbitrary_TSL_val(alphas[j], betas[i]).first, abs_tol);
        }
    }
}