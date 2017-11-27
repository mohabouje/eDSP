//
// Created by Mohammed Boujemaoui on 10/10/2017.
//

#include "math/container.hpp"
#include "../test_db.h"
#include <catch.hpp>

using namespace eDSP::Math;
SCENARIO("Testing math features for standard containers") {

    GIVEN("A std::vector with a given size") {
        std::vector<double> test = test::db::ref_vector;
        const size_t size = test.size();

        // Testing set function
        WHEN("We set all the values to a given value") {
            constexpr double value = 1.;
            Container::set(test, value);
            THEN("Every single value should be the same inside the array") {
                for (double i : test) {
                    REQUIRE(i == value);
                }
            }
        }

        // Testing one function
        WHEN("We set up the vector like a one array") {
            test = Container::ones<double>(size);
            THEN("Every single value should be the same inside the array") {
                for (double i : test) {
                    REQUIRE(i == static_cast<double>(1));
                }
            }

            // Testing function has negative
            AND_THEN("No value should be negative") {
                REQUIRE(!Container::hasNegative(test));
            }

            // Testing function has zeros
            AND_THEN("No value should be zero") {
                REQUIRE(!Container::hasZero(test));
            }
        }

        // Testing zero function
        WHEN("We set up the vector like a zero array") {
            test = Container::zeros<double>(size);
            THEN("Every single value should be the same inside the array") {
                for (double i : test) {
                    REQUIRE(i == static_cast<double>(0));
                }
            }

            // Testing function has negative
            AND_THEN("No value should be negative") {
                REQUIRE(!Container::hasNegative(test));
            }

            // Testing function has zeros
            AND_THEN("Should have zero values") {
                REQUIRE(Container::hasZero(test));
            }
        }

    }

    GIVEN("A std::vector with a ones array of a given size") {

        // Testing function sum
        WHEN("We want to apply a sum") {
            const double total = Container::sum(test::db::ref_vector);
            THEN("The sum should be the correct one") {
                REQUIRE(total == test::db::sum_ref_vector);
            }
        }

        // Testing function sum squares
        WHEN("We want to apply a sum squares") {
            const double total = Container::sum_squares(test::db::ref_vector);
            THEN("The sum should be the correct one") {
                //REQUIRE( test::util::isEqual(total), test::db::sum_square_ref_vector);
            }
        }

        // Testing max function
        WHEN("We want to calculate the max") {
            const double max = Container::max(test::db::ref_vector);
            THEN("The sum should be the correct one") {
                REQUIRE(max == test::db::max_ref_vector);
            }
        }

        // Testing min function
        WHEN("We want to calculate the min") {
            const double max = Container::min(test::db::ref_vector);
            THEN("The sum should be the correct one") {
                REQUIRE(max == test::db::min_ref_vector);
            }
        }
    }

    GIVEN("A std::vector with fractional values") {
        constexpr size_t size = 100;
        std::vector<double> test(size);
        Container::set(test, 1.5);

        // Testing ceil function
        WHEN("We apply a ceil operation") {
            Container::ceil(test);
            THEN("Every single value should be the ceil value of the original one") {
                for (double i : test) {
                    REQUIRE(i == 2.0);
                }
            }

        }

        // Testing floor function
        WHEN("We apply a floor operation") {
            Container::floor(test);
            THEN("Every single value should be the round value of the original one") {
                for (double i : test) {
                    REQUIRE(i == 1.0);
                }
            }

        }

        // Testing round function
        WHEN("We apply a round operation") {
            Container::round(test);
            THEN("Every single value should be the round value of the original one") {
                for (double i : test) {
                    REQUIRE(i == 2.0);
                }
            }

        }
    }
}
