//
// Created by Mohammed Boujemaoui on 10/10/2017.
//

#include "../test_db.h"
#include "../test_config.h"
#include "math/stats.h"
#include <catch.hpp>

using namespace edsp::math;
SCENARIO("Testing the basic usage of the statistic functions") {

    GIVEN("A hamming window with a given size") {
        const auto& test = test::db::ref_vector;

        // Testing mean function
        WHEN("We want to estimate the mean of the signal") {
            const double mean = stats::mean(std::begin(test), std::end(test));
            const Approx target = Approx(mean).epsilon(TEST_TOLERANCE);
            REQUIRE(target == test::db::mean_ref_vector);
        }

        std::find()

        // Testing mode function
        WHEN("We want to estimate the mode of the signal") {
            const double mode = stats::mode(test);
            const Approx target = Approx(mode).epsilon(TEST_TOLERANCE);
            REQUIRE(target == test::db::mode_ref_vector);
        }

        // Testing variance function
        WHEN("We want to estimate the variance of the signal") {
            const double var = stats::variance(std::begin(test), std::end(test));
            const Approx target = Approx(var).epsilon(TEST_TOLERANCE);
            REQUIRE(target == test::db::var_ref_vector);
        }

        // Testing standard desviation function
        WHEN("We want to estimate the standard desviation of the signal") {
            const double _std = stats::standar_desviation(std::begin(test), std::end(test));
            const Approx target = Approx(_std).epsilon(TEST_TOLERANCE);
            REQUIRE(target == test::db::std_desv_ref_vector);
        }

        // Testing mean error
        WHEN("We want to estimate the mean error of the signal") {
            const double mean = stats::mean_error(std::begin(test), std::end(test));
        }


    }





}

