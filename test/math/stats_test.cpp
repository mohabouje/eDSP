//
// Created by Mohammed Boujemaoui on 10/10/2017.
//

#include "../test_db.h"
#include "math/stats.h"
#include <catch.hpp>

using namespace eDSP::Math;
SCENARIO("Testing the basic usage of the statistic functions") {

    GIVEN("A hamming window with a given size") {
        const std::vector<double> ref = test::db::ref_vector;

        // Testing mean function
        WHEN("We want to estimate the mean of the signal") {
            const double mean = Stat::mean(ref);
            //REQUIRE(mean == test::db::mean_ref_vector);
        }

        // Testing mode function
        WHEN("We want to estimate the mode of the signal") {
            const double mode = Stat::mode(ref);
            //REQUIRE(mode == test::db::mode_ref_vector);
        }

        // Testing variance function
        WHEN("We want to estimate the variance of the signal") {
            const double var = Stat::variance(ref);
            //REQUIRE(var == test::db::var_ref_vector);
        }

        // Testing standard desviation function
        WHEN("We want to estimate the standard desviation of the signal") {
            const double std = Stat::standar_desviation(ref);
            //REQUIRE(std == test::db::std_desv_ref_vector);
        }

        // Testing mean error
        WHEN("We want to estimate the mean error of the signal") {
            const double mean = Stat::mean_error(ref);
        }


    }





}

