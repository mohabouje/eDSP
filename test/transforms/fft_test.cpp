//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include <catch.hpp>
#include "frequency/fft.h"
#include "frequency/ifft.h"
#include "math/complex.h"
#include "../test_db.h"
#include "../test_config.h"

using namespace eDSP::frequency;
SCENARIO("Testing FFT") {
    auto original = test::db::ref_vector;
    auto inverse = original;
    std::vector<std::complex<double>> buffer(std::size(original));
    FFT fft{};
    IFFT ifft{};

    GIVEN("A signal ") {
        WHEN("We apply the FFT") {
            fft.compute_r2c(std::begin(original), std::end(original), std::begin(buffer));
            THEN("It should be the same as the estimated fft") {
                for (size_t i = 0, size = buffer.size(); i < size; i++) {
                    const Approx abs = Approx(std::abs(buffer[i])).epsilon(TEST_TOLERANCE);
                    REQUIRE(abs == std::abs(test::db::fft_ref_vector[i]));
                }
            }
        }

        AND_WHEN("We apply the inverse operation") {
            fft.compute_r2c(std::begin(original), std::end(original), std::begin(buffer));
            ifft.compute_c2r(std::begin(buffer), std::end(buffer), std::begin(inverse));
            THEN("We should get the same output") {
                for (size_t i = 0, size = inverse.size(); i < size; i++) {
                    const Approx target = Approx(inverse[i]).epsilon(TEST_TOLERANCE);
                    REQUIRE(target == original[i]);
                }
            }
        }
    }
}